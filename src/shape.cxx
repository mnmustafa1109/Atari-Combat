#include "../include/glad.h"

#include "../include/glfw/glfw3.h"

#include <cmath>
#include <iostream>
#include "../include/glm/glm.hpp"
#include "../include/movement.hxx"
#include "../include/shape.hxx"

// do not use this function if you want to render the shapes and avoid
// segmentation faults
Shape::Shape() {}

// initialize a shape pass it the x and y coordinates of the shape the widht and
// height of the shape the angle and the shader and texture it needed to render
// the shape also pass the type of the shape like for e.g if its a rectangle or
// a circle
Shape::Shape(SHAPE shape,
             float x,
             float y,
             float z,
             float width,
             float height,
             float angle,
             Texture* texture,
             Shader* shader) {
    // call the create function using this approach for modularity
    create(shape, x, y, z, width, height, angle, texture, shader);
}

// create a shape pass it the x and y coordinates of the shape the widht and
// height of the shape the angle and the shader and texture it needed to render
// the shape also pass the type of the shape like for e.g if its a rectangle or
// a circle
void Shape::create(SHAPE shape,
                   float x,
                   float y,
                   float z,
                   float width,
                   float height,
                   float angle,
                   Texture* texture,
                   Shader* shader) {
    this->shape = shape;
    this->x = x;
    this->y = y;
    this->z = z;
    this->width = width;
    this->height = height;
    this->angle = angle;
    this->scale = 1.0f;
    // if its a rectangle or a square
    if (shape == RECTANGLE || shape == SQUARE) {
        this->texture = texture;
        this->shader = shader;
        // rectangle having zero zero as center
        float vertices[] = {
            // positions          // colors           // texture coords
            x + width / 2, y + height / 2, z, 1.0f, 1.0f,
            x - width / 2, y + height / 2, z, 0.0f, 1.0f,
            x - width / 2, y - height / 2, z, 0.0f, 0.0f,
            x + width / 2, y - height / 2, z, 1.0f, 0.0f,
        };
        // order of vertices to render the triangle
        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
        };

        // product the shape
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                              (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

// delete the shape and all associated data and buffers
Shape::~Shape() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    texture = nullptr;
    shader = nullptr;
}

// render the shape by drawing it to the screen, pass an optional color if you
// want to have some cool tint on it
void Shape::draw(glm::vec3 color) {
    // get its current position size scale and angle and calculate its model
    // matrix and assign it to the shader uniform
    Movement::getInstance()->move(this->x, this->y, this->z, this->angle,
                                  this->scale);
    // assignemnt of shades uniform
    shader->Matrix4fv("projection", Movement::getInstance()->getProjection());
    shader->Matrix4fv("view", Movement::getInstance()->getView());
    shader->Matrix4fv("model", Movement::getInstance()->getModel());
    shader->setv4f("ourColor", color[0], color[1], color[2], 1.0f);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // un use shader
    if (shape == RECTANGLE || shape == SQUARE) {
        shader->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getTexture());
        shader->set("texture1", 0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    Movement::getInstance()->clear();
}

// pass some x y or radians angle and scale to change the shape
// it will increment the angle by the angle passed or the positons
// scale is a to be added features
void Shape::move(float x, float y, float z, float angle, float scale) {
    this->x += x;
    this->y += y;
    this->z += z;
    this->angle += angle;
    // this->scale += scale;
    // this ->width *= this->scale;
    // this ->height *= this->scale;
    // reset the angle ti be withing 0 to 360
    if (this->angle > 360) {
        this->angle -= 360;
    }
    if (this->angle < 0) {
        this->angle += 360;
    }
}

// reinitialize the shape to be drawn to the origin
// other atrritbuts like texture and shader will remain the same
void Shape::init_pose() {
    this->x = 0;
    this->y = 0;
    this->z = 1;
    this->scale = 0.9;
    this->angle = 0;
}

float Shape::getX() {
    return this->x;
}

float Shape::getY() {
    return this->y;
}

float Shape::getZ() {
    return this->z;
}

float Shape::getAngle() {
    return this->angle;
}

float Shape::getWidth() {
    return this->width;
}

float Shape::getHeight() {
    return this->height;
}

// collision detection system in 2d for class of shape
// doesnt work fine if the width and height are not adjusted with scale
bool Shape::isColliding(Shape* shape) {
    float x1 = this->x - this->width / 2;
    float x2 = this->x + this->width / 2;
    float y1 = this->y - this->height / 2;
    float y2 = this->y + this->height / 2;
    float x3 = shape->getX() - shape->getWidth() / 2;
    float x4 = shape->getX() + shape->getWidth() / 2;
    float y3 = shape->getY() - shape->getHeight() / 2;
    float y4 = shape->getY() + shape->getHeight() / 2;
    if (x1 < x4 && x2 > x3 && y1 < y4 && y2 > y3) {
        return true;
    }
    return false;
}