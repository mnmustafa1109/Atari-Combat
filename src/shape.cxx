#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include "../include/glm/glm.hpp"
#include "../include/movement.hxx"
#include "../include/shape.hxx"

Shape::Shape() {
    this -> angle = 0.0f;
}

Shape::Shape(SHAPE shape,
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
    this-> scale= 1.0f;
    this->width = width;
    this->height = height;
    this->angle = angle;
    if (shape == RECTANGLE || shape == SQUARE) {
        this->texture = texture;
        this->shader = shader;
        // rectangle having zero zero as center
        float vertices[] = {
            // positions          // colors           // texture coords
            x + width / 2, y + height / 2, z, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            x - width / 2, y + height / 2, z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            x - width / 2, y - height / 2, z, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            x + width / 2, y - height / 2, z, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        };
        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
        };

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
    }
}

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
    if (shape == RECTANGLE || shape == SQUARE) {
        this->texture = texture;
        this->shader = shader;
        // rectangle having zero zero as center
        float vertices[] = {
            // positions          // colors           // texture coords
            x + width / 2, y + height / 2, z, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            x - width / 2, y + height / 2, z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            x - width / 2, y - height / 2, z, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            x + width / 2, y - height / 2, z, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        };
        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
        };

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
    }
}

Shape::~Shape() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    texture = nullptr;
    shader = nullptr;
}

void Shape::draw() {
    Movement::getInstance()->move(this->x, this->y, this->z, this->angle, this ->scale);
    shader->Matrix4fv("projection", Movement::getInstance()->getProjection());
    shader->Matrix4fv("view", Movement::getInstance()->getView());
    shader->Matrix4fv("model", Movement::getInstance()->getModel());
    if (shape == RECTANGLE || shape == SQUARE) {
        shader->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getTexture());
        shader->set("texture1", 0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    Movement::getInstance()->clear();
}

void Shape::move(float x,
                 float y,
                 float z,
                 float angle,
                 float scale) {
    this->x += x;
    this->y += y;
    this->z += z;
    this->angle += angle;
    // this->scale += scale;
    // this ->width *= this->scale;
    // this ->height *= this->scale;

    
    if (this->angle > 360) {
        this->angle -= 360;
    }
    if (this->angle < 0) {
        this->angle += 360;
    }
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