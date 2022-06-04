#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <vector>

#include "../include/bullet.hxx"
#include "../include/game.hxx"
#include "../include/input.hxx"
#include "../include/irrKlang/irrKlang.h"
#include "../include/main.hxx"
#include "../include/map.hxx"
#include "../include/movement.hxx"
#include "../include/player.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/uuid.hxx"
#include "../include/vehicle.hxx"

Movement* Movement::instance = nullptr;
ResourceMan* ResourceMan::instance = nullptr;

class Map;

Game::Game()
    : resourceMan(ResourceMan::getInstance()),
      bullets(resourceMan->getBullets()),
      vehicles(resourceMan->getVehicles()),
      players(resourceMan->getPlayers()) {}

Game::Game(GLFWwindow* window)
    : resourceMan(ResourceMan::getInstance()),
      bullets(resourceMan->getBullets()),
      vehicles(resourceMan->getVehicles()),
      players(resourceMan->getPlayers()) {
    this->window = window;
    this->level = 0;
    resourceMan = ResourceMan::getInstance();
    irrklang::ISoundDeviceList* deviceList = irrklang::createSoundDeviceList();
    printf("Devices available:\n\n");
    for (int i = 0; i < deviceList->getDeviceCount(); ++i)
        printf("%d: %s\n", i, deviceList->getDeviceDescription(i));
    resourceMan->setInitSoundEngine();
    this->load();
    bullets = resourceMan->getBullets();
    vehicles = resourceMan->getVehicles();
    resourceMan->getPlayer(0, "anon", 100,GREEN);
    resourceMan->getPlayer(1, "mustafa", 1000,BLUE);
    this->game();
}

void Game::render() {
    // draw background
    map->draw();

    map->draw_objects();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse
    // moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
}

void Game::load() {
    resourceMan->getShader("rectshader", "../shaders/rectangle.vs",
                           "../shaders/rectangle.fs");
    resourceMan->getTexture("redtank", "../data/textures/red_tank.png");
    resourceMan->getTexture("greentank", "../data/textures/green_tank.png");
    resourceMan->getTexture("bluetank", "../data/textures/blue_tank.png");
    resourceMan->getTexture("bullet", "../data/textures/bullet.png");
    resourceMan->getTexture("desert", "../data/background/desert.jpg");
    resourceMan->getTexture("snowy", "../data/background/snowy.jpg");
    resourceMan->getTexture("forest", "../data/background/forest.jpeg");
    resourceMan->getTexture("house1", "../data/textures/h1.jpg");
    resourceMan->getTexture("house2", "../data/textures/h2.jpg");
    resourceMan->getTexture("house3", "../data/textures/h3.jpg");
    resourceMan->getTexture("house4", "../data/textures/h4.jpg");
    resourceMan->getTexture("house5", "../data/textures/h5.jpg");
    resourceMan->getTexture("house6", "../data/textures/h6.jpg");
    resourceMan->getTexture("border", "../data/background/border.png");
    map_types.push_back(M_TYPE::DESERT);
    map_types.push_back(M_TYPE::SNOWY);
    map_types.push_back(M_TYPE::FOREST);
}

void Game::time_logic() {  // per-frame time logic
    // --------------------
    float currentFrame = glfwGetTime();
    Movement::getInstance()->setDeltaTime(
        currentFrame - Movement::getInstance()->getLastFrame());
    Movement::getInstance()->setLastFrame(currentFrame);
}

void Game::game_logic() {
    for (auto& vehicle : vehicles) {
        if (vehicle.second->get_destroyed()) {
            std::cout << "level " << this->level << std::endl;
            this->level++;
            vehicle.second->get_player()->inc_loss();
            if (this->level < 3) {
                std::cout << "player " << players[0]->getName() << " lost "
                          << players[0]->getLoss() << " times" << std::endl;
                std::cout << "player " << players[1]->getName() << " lost "
                          << players[1]->getLoss() << " times" << std::endl;
                resourceMan->getBullets().clear();
                std::cout << "Bullets cleared" << std::endl;
                resourceMan->getVehicles().clear();
                std::cout << "Vehicles cleared" << std::endl;
                resourceMan->getObstacles().clear();
                std::cout << "Obstacles cleared" << std::endl;
                resourceMan->getMaps().clear();
                std::cout << "Maps cleared" << std::endl;
                int m_type;
                m_type = uuid::gen_random_i(0, map_types.size() - 1);
                map = &resourceMan->getMap(map_name(map_types[m_type]),
                                           map_types[m_type]);
                map_types.erase(map_types.begin() + m_type);
                std::cout << "Map loaded" << std::endl;
                break;
            } else {
                for (auto& player : players) {
                    if (player.second->getScore() >
                        player.second->getHighscore()) {
                        player.second->setHighscore(player.second->getScore());
                        std::cout << "player " << player.second->getName()
                                  << " new highscore "
                                  << player.second->getHighscore() << std::endl;
                    }
                }
                glfwSetWindowShouldClose(window, true);
                return;
            }
        }
    }
    for (auto& bullet : bullets) {
        if (bullet.second->getRender() && bullet.second != NULL) {
            bullet.second->move();
        } else {
            delete bullet.second;
            bullets.erase(bullet.first);
            break;
        }
    }
}

void Game::game() {
    // glfw: initialize and configure

    resourceMan->playSound("ingame", true);

    int m_type = uuid::gen_random_i(0, 2);
    map = &resourceMan->getMap(map_name(map_types[m_type]), map_types[m_type]);
    map_types.erase(map_types.begin() + m_type);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic and events
        time_logic();
        game_logic();

        // input
        // -----
        processInput(window);

        // render
        render();
        glfwPollEvents();
    }
    resourceMan->delSoundEngine();
}
