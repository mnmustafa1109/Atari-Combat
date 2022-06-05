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

// INITIALIZE the movement model view and projection
// use to view our scene and also initialize the timing
Movement::Movement() {
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection =
        glm::perspective(glm::radians(90.0f),
                         (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // initialize delta frame
    deltaTime = 0.0f;
    lastFrame = 0.0f;
}

// get the single instance of the movement model view and projection as its a
// singleton
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

// update the movement model of the currently to be rendered object
// pass the axis scale and angle of the object
void Movement::move(float x, float y, float z, float angle, float scale) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, z));
    model =
        glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scale));
}

// c;ear the model for future use
void Movement::clear() {
    model = glm::mat4(1.0f);
}
