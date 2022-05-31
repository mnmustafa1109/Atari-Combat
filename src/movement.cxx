#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include <iostream>

#include "../include/game.hxx"
#include "../include/input.hxx"
#include "../include/main.hxx"
#include "../include/movement.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"

Movement::Movement() {
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection =
        glm::perspective(glm::radians(90.0f),
                         (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    deltaTime = 0.0f;
    lastFrame = 0.0f;
}

Movement* Movement::getInstance() {
    if (instance == nullptr) {
        instance = new Movement();
    }
    return instance;
}

glm::mat4 Movement::getModel() {
    return model;
}
glm::mat4 Movement::getView() {
    return view;
}
glm::mat4 Movement::getProjection() {
    return projection;
}

float Movement::getDeltaTime() const {
    return deltaTime;
}

float Movement::getLastFrame() const {
    return lastFrame;
}

void Movement::setLastFrame(float lastFrame) {
    this->lastFrame = lastFrame;
}

void Movement::setDeltaTime(float deltaTime) {
    this->deltaTime = deltaTime;
}

void Movement::move(float x, float y, float z, float angle, float scale) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, z));
    model =
        glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scale));
}

void Movement::clear() {
    model = glm::mat4(1.0f);
}
