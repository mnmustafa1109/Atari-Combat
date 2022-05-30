#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../include/shape.hxx"

Shape::Shape() {}

Shape::Shape(SHAPE shape,
             float x,
             float y,
             float z,
             float width,
             float height,
             Texture* texture,
             Shader* shader) {
    this->shape = shape;
    this->x = x;
    this->y = y;
    this->z = z;
    this->width = width;
    this->height = height;
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
    if (shape == RECTANGLE || shape == SQUARE) {
        shader->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getTexture());
        shader->set("texture1", 0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
