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
    Map& map = resourceMan->getMap("snowy", SNOWY);
    


    

    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    std::map<std::string, Bullet*>& bullets = resourceMan->getBullets();

    std::string key;
    Vehicle val;

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
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw background
        map.draw();

        for (auto const& [key, val] : vehicles) {
            val->draw();
        }
        for (auto const& [key, val] : bullets) {
            if (val->getRender()) {
                val->move();
            }
        }
        for (auto const& [key, val] : bullets) {
            if (val->getRender()) {
                val->draw();
            } else {
                bullets.erase(key);
            }
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
