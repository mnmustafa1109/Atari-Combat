#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include <iostream>

#include "../include/bullet.hxx"
#include "../include/game.hxx"
#include "../include/input.hxx"
#include "../include/main.hxx"
#include "../include/movement.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/vehicle.hxx"

Movement* Movement::instance = nullptr;
ResourceMan* ResourceMan::instance = nullptr;

void render(GLFWwindow* window) {
    std::string key;
    Vehicle val;

    ResourceMan* resourceMan = ResourceMan::getInstance();
    Map& map = resourceMan->getMap("snowy", SNOWY);

    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    std::map<std::string, Bullet*>& bullets = resourceMan->getBullets();

    // draw background
    map.draw();

    for (auto const& [key, val] : vehicles) {
        val->draw();
    }
    for (auto const& [key, val] : bullets) {
        if (val->getRender() && val != NULL) {
            val->move();
        }
    }
    for (auto const& [key, val] : bullets) {
        if (val->getRender() && val != NULL) {
            val->draw();
        }
    }
    for (auto const& [key, val] : bullets) {
        if (val->getRender() == false && val != NULL) {
            delete val;
            bullets.erase(key);
        }
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse
    // moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
}

void game(GLFWwindow* window) {
    // glfw: initialize and configure
    ResourceMan* resourceMan = ResourceMan::getInstance();
    resourceMan->getShader("rectshader", "../shaders/rectangle.vs",
                           "../shaders/rectangle.fs");
    resourceMan->getTexture("redtank", "../data/textures/red_tank.png");
    resourceMan->getTexture("greentank", "../data/textures/green_tank.png");
    resourceMan->getTexture("bluetank", "../data/textures/blue_tank.png");
    resourceMan->getTexture("bullet", "../data/textures/bullet.png");
    resourceMan->getVehicle("p1", RED, 0.5, 0.0, 1.0);
    resourceMan->getVehicle("p2", GREEN, 0.0, 0.0, 1.0);
    resourceMan->getTexture("desert", "../data/textures/desert.jpg");
    resourceMan->getTexture("snowy", "../data/textures/snowy.jpg");
    resourceMan->getTexture("forest", "../data/textures/forest.jpeg");
    resourceMan->getTexture("house1", "../data/textures/h1.jpg");
    resourceMan->getTexture("house2", "../data/textures/h2.jpg");
    resourceMan->getTexture("house3", "../data/textures/h3.jpg");
    resourceMan->getTexture("house4", "../data/textures/h4.jpg");
    resourceMan->getTexture("house5", "../data/textures/h5.jpg");
    resourceMan->getTexture("house6", "../data/textures/h6.jpg");
    resourceMan->getTexture("house7", "../data/textures/h7.jpg");

        

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        Movement::getInstance()->setDeltaTime(
            currentFrame - Movement::getInstance()->getLastFrame());
        Movement::getInstance()->setLastFrame(currentFrame);

        // input
        // -----
        // output frame rate
        processInput(window);
        render(window);
        glfwPollEvents();
    }
}
