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

Game::Game(){

}

Game::Game(GLFWwindow* window){
    this->window = window;
    this->load();
    this->game();
}


void Game::render() {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    Map& map = resourceMan->getMap("forest", FOREST);

    std::map<std::string, Bullet*>& bullets = resourceMan->getBullets();

    // draw background
    map.draw();

    for (auto& bullet : bullets) {
        if (bullet.second->getRender() && bullet.second != NULL) {
            bullet.second->draw();
        }
    }
    map.draw_objects();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse
    // moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
}

void Game::load() {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    resourceMan->getShader("rectshader", "../shaders/rectangle.vs",
                           "../shaders/rectangle.fs");
    resourceMan->getTexture("redtank", "../data/textures/red_tank.png");
    resourceMan->getTexture("greentank", "../data/textures/green_tank.png");
    resourceMan->getTexture("bluetank", "../data/textures/blue_tank.png");
    resourceMan->getTexture("bullet", "../data/textures/bullet.png");
    resourceMan->getTexture("desert", "../data/textures/desert.jpg");
    resourceMan->getTexture("snowy", "../data/textures/snowy.jpg");
    resourceMan->getTexture("forest", "../data/textures/forest.jpeg");
    resourceMan->getTexture("house1", "../data/textures/h1.jpg");
    resourceMan->getTexture("house2", "../data/textures/h2.jpg");
    resourceMan->getTexture("house3", "../data/textures/h3.jpg");
    resourceMan->getTexture("house4", "../data/textures/h4.jpg");
    resourceMan->getTexture("house5", "../data/textures/h5.jpg");
    resourceMan->getTexture("house6", "../data/textures/h6.jpg");
    resourceMan->getTexture("border", "../data/textures/border.png");
    resourceMan->getMap("snowy", SNOWY);
    resourceMan->getMap("desert", DESERT);
    resourceMan->getMap("forest", FOREST);
}

void Game::game() {
    // glfw: initialize and configure

    load();
    ResourceMan* resourceMan = ResourceMan::getInstance();
    std::map<std::string, Bullet*>& bullets = resourceMan->getBullets();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        Movement::getInstance()->setDeltaTime(
            currentFrame - Movement::getInstance()->getLastFrame());
        Movement::getInstance()->setLastFrame(currentFrame);
        for (auto& bullet : bullets) {
            if (bullet.second->getRender() && bullet.second != NULL) {
                bullet.second->move();
            }
        }
        for (auto& bullet : bullets) {
            if (bullet.second->getRender() == false && bullet.second != NULL) {
                // delete bullet.second;
                // bullets.erase(bullet.first);
            }
        }

        // input
        // -----
        processInput(window);

        // render
        render();
        glfwPollEvents();
    }
}
