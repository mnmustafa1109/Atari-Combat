#include "../include/glad.h"

#include "../include/glfw/glfw3.h"

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <string>
#include <vector>

#include "../include/game.hxx"
#include "../include/input.hxx"
#include "../include/main.hxx"
#include "../include/map.hxx"
#include "../include/movement.hxx"
#include "../include/player.hxx"
#include "../include/resourceman.hxx"
#include "../include/uuid.hxx"
#include "../include/vehicle.hxx"

Movement* Movement::instance = nullptr;
ResourceMan* ResourceMan::instance = nullptr;

// forward declaration
class Map;

// pass a string and check if every character is a digit
bool check_digit(std::string number) {
    // parse through every character of the string
    for (int i = 0; i < number.length(); i++) {
        if (isdigit(number[i]) == false && number[i] != '-') {
            return false;
        }
    }
    return true;
}

// pass one max and one min and ask number and make sure it is between them by
// asserting dominance
int ask_in_range(int min, int max) {
    int input;
    std::string number;
    do {
        std::cin >> number;
        if (check_digit(number) == false) {
            std::cout << "Invalid input, please enter a number" << std::endl;
            continue;
        }
        input = std::stoi(number);
        if (input < min || input > max) {
            std::cout << "Invalid input, please try again" << std::endl;
            std::cout << "Enter a number between " << min << " and " << max
                      << std::endl;
            std::cout << "Enter a number: ";
        }
    } while (input < min || input > max || check_digit(number) == false);
    return input;
}

// pass and integer and return the corresponding v color enum type
V_COLOR get_type(int i) {
    switch (i) {
        case 1:
            return RED;
            break;
        case 2:
            return GREEN;
            break;
        case 3:
            return BLUE;
            break;
        default:
            return RED;
            break;
    }
    return RED;
}

// pass the player id and ask its personal information
void Game::menu(int i) {
    std::string player_name = "Player";
    std::cout << "Enter Player Name: ";
    std::cin >> player_name;
    std::cout << "Enter Player Color: " << std::endl;
    std::cout << "1. Red" << std::endl;
    std::cout << "2. Green" << std::endl;
    std::cout << "3. Blue" << std::endl;
    int c = ask_in_range(1, 3);

    resourceMan->getPlayer(i, player_name, 100, get_type(c));
}

Game::Game()
    // saving the references of the map of the player etc in the game
    // so that we can access them in the game
    : resourceMan(ResourceMan::getInstance()),
      bullets(resourceMan->getBullets()),
      vehicles(resourceMan->getVehicles()),
      players(resourceMan->getPlayers()),
      powerups(resourceMan->getPowerups()) {}

Game::Game(GLFWwindow* window)
    // saving the references of the map of the player etc in the game
    // so that we can access them in the game
    : resourceMan(ResourceMan::getInstance()),
      bullets(resourceMan->getBullets()),
      vehicles(resourceMan->getVehicles()),
      players(resourceMan->getPlayers()),
      powerups(resourceMan->getPowerups()) {
    // initializing the game
    this->window = window;
    this->level = 0;
    resourceMan = ResourceMan::getInstance();
    irrklang::ISoundDeviceList* deviceList = irrklang::createSoundDeviceList();
    printf("Devices available:\n\n");
    for (int i = 0; i < deviceList->getDeviceCount(); ++i)
        printf("%d: %s\n", i, deviceList->getDeviceDescription(i));

    resourceMan->initPowerpose();

    // asking both user its perosnaal information
    menu(0);
    menu(1);
    resourceMan->setInitSoundEngine();
    this->load();
    // starting the game
    resourceMan->playSound("ingame", true);

    this->game();
}

// render the game and its corresponding element
void Game::render() {
    // save the font in m for later use
    Font* m = &(resourceMan->getFont("main"));

    // map drawing
    // drawing two times cause fonts broke something somehow
    map->draw();
    map->draw();
    // drawing the player and other objects in the map
    map->draw_objects(is_game_over);
    // drawing the top name bar and scores
    m->RenderText(players[0]->getName(), -0.92f, 0.8f, 0.0005f,
                  glm::vec3(1.0f, 1.0f, 1.0f));
    m->RenderText(players[1]->getName(), 0.92f, 0.8f, 0.0005f,
                  glm::vec3(1.0, 1.0f, 1.0f), true);
    m->RenderText(std::to_string(players[0]->getLoss()), 0.049f, 0.8899f,
                  0.0007f, glm::vec3(1.0f, 1.0f, 1.0f));
    m->RenderText(std::to_string(players[1]->getLoss()), -0.049f, 0.8899f,
                  0.0007f, glm::vec3(1.0f, 1.0f, 1.0f), true);

    if (is_game_over) {
        // if game ended then display who wins by calculatin total wins
        // and displaying the winner and asking enter to quite
        for (auto& vehicle : vehicles) {
            if (level > 2) {
                if (players[0]->getLoss() < players[1]->getLoss()) {
                    m->RenderText(players[0]->getName() + " Wins", -0.6f, -0.1f,
                                  0.0015f, glm::vec3(1.0f, 1.0f, 1.0f));
                } else {
                    m->RenderText(players[1]->getName() + " Wins", -0.6f, -0.1f,
                                  0.0015f, glm::vec3(1.0f, 1.0f, 1.0f));
                }
                m->RenderText("Press Enter to restart", -0.6f, -0.2f, 0.0005f,
                              glm::vec3(1.0f, 1.0f, 1.0f));
                m->RenderText("Press x to quite", -0.6f, -0.3f, 0.0005f,
                              glm::vec3(1.0f, 1.0f, 1.0f));

                // if game ended then display who wins
                // and ask enter to continue
            } else if (!vehicle.second->get_destroyed()) {
                m->RenderText(
                    vehicle.second->get_player()->getName() + " has won", -0.6f,
                    0.0f, 0.001f, glm::vec3(1.0f, 1.0f, 1.0f));
                m->RenderText("Press Enter for next level", -0.6f, -0.1f,
                              0.0005f, glm::vec3(1.0f, 1.0f, 1.0f));
                break;
            }
        }
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse
    // moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
}

// loading all the textures and shaders
// and initializing the map and loading the audio into memory
void Game::load() {
    // loading the shaders
    resourceMan->getShader("rectshader", "../shaders/rectangle.vs",
                           "../shaders/rectangle.fs");
    resourceMan->getShader("textshader", "../shaders/text.vs",
                           "../shaders/text.fs");
    // loading the textures
    resourceMan->getTexture("redtank", "../data/textures/red_tank.png", false);
    resourceMan->getTexture("greentank", "../data/textures/green_tank.png",
                            false);
    resourceMan->getTexture("bluetank", "../data/textures/blue_tank.png",
                            false);
    resourceMan->getTexture("bullet", "../data/textures/bullet.png", false);
    resourceMan->getTexture("desert", "../data/background/desert.jpg", false);
    resourceMan->getTexture("snowy", "../data/background/snowy.jpg", false);
    resourceMan->getTexture("forest", "../data/background/forest.jpeg", false);
    resourceMan->getTexture("house1", "../data/textures/h1.jpg", false);
    resourceMan->getTexture("house2", "../data/textures/h2.jpg", false);
    resourceMan->getTexture("house3", "../data/textures/h3.jpg", false);
    resourceMan->getTexture("house4", "../data/textures/h4.jpg", false);
    resourceMan->getTexture("house5", "../data/textures/h5.jpg", false);
    resourceMan->getTexture("house6", "../data/textures/h6.jpg", false);
    resourceMan->getTexture("border", "../data/background/border.png", false);
    resourceMan->getTexture("red_heart", "../data/textures/red_heart.png",
                            true);
    resourceMan->getTexture("green_heart", "../data/textures/green_heart.png",
                            true);
    resourceMan->getTexture("blue_heart", "../data/textures/blue_heart.png",
                            true);
    resourceMan->getTexture("overlay", "../data/textures/overlay.png", false);
    resourceMan->getTexture("shield", "../data/textures/p_power.png", true);
    resourceMan->getTexture("speed", "../data/textures/s_power.png", true);
    resourceMan->getTexture("attack", "../data/textures/a_power.png", true);
    resourceMan->getTexture("health", "../data/textures/h_power.png", true);
    // loading the audio
    resourceMan->addSound("hit");
    resourceMan->addSound("shot");
    resourceMan->addSound("damage");
    resourceMan->addSound("ingame");
    resourceMan->addSound("queue");
    resourceMan->addSound("dissapear");
    resourceMan->addSound("destroy");
    resourceMan->addSound("enter");
    resourceMan->addSound("win");
    resourceMan->addSound("appear");
    resourceMan->addSound("pick");
    // loading the map
    map_types.push_back(M_TYPE::DESERT);
    map_types.push_back(M_TYPE::SNOWY);
    map_types.push_back(M_TYPE::FOREST);
    // loading the fonts
    resourceMan->getFont("arial", "arial.ttf");
    resourceMan->getFont("main", "main.ttf");
    // setting game over to be false at the beginning
    is_game_over = false;
    replay = false;
}

void Game::time_logic() {  // per-frame time logic
    // --------------------
    // compute frame time:
    float currentFrame = glfwGetTime();
    // delta time
    Movement::getInstance()->setDeltaTime(
        currentFrame - Movement::getInstance()->getLastFrame());
    Movement::getInstance()->setLastFrame(currentFrame);
}

void Game::level_load() {
    // reloading the map and the vehicles
    std::cout << "player " << players[0]->getName() << " lost "
              << players[0]->getLoss() << " times" << std::endl;
    std::cout << "player " << players[1]->getName() << " lost "
              << players[1]->getLoss() << " times" << std::endl;
    // clearing every other mao in resource manager for new game
    resourceMan->getBullets().clear();
    std::cout << "Bullets cleared" << std::endl;
    resourceMan->getVehicles().clear();
    std::cout << "Vehicles cleared" << std::endl;
    resourceMan->getObstacles().clear();
    std::cout << "Obstacles cleared" << std::endl;
    resourceMan->getMaps().clear();
    std::cout << "Maps cleared" << std::endl;
    resourceMan->getShapes().clear();
    if (this->level < 3) {
        int m_type;
        m_type = uuid::gen_random_i(0, map_types.size() - 1);
        map = &resourceMan->getMap(map_name(map_types[m_type]),
                                   map_types[m_type]);
        map_types.erase(map_types.begin() + m_type);
        std::cout << "Map loaded" << std::endl;
        is_game_over = false;

    } else {
        // if all the levels are done then game is over
        // and update highscores of players
        for (auto& player : players) {
            if (player.second->getScore() > player.second->getHighscore()) {
                player.second->setHighscore(player.second->getScore());
                std::cout << "player " << player.second->getName()
                          << " new highscore " << player.second->getHighscore()
                          << std::endl;
            }
        }
        // closing the window
        if (replay) {
            resourceMan->getPlayers().clear();
            std::cout << "Players cleared" << std::endl;
            menu(0);
            menu(1);
            load();
            level = 0;
            replay = false;
            is_game_over = false;
            game();
        }
    }
}

void Game::game_logic() {
    if (!is_game_over) {
        // check whih car is destroyed and update the score
        // and also check if the game is over
        for (auto& vehicle : vehicles) {
            if (vehicle.second->get_destroyed()) {
                resourceMan->playSound("win");

                std::cout << "level " << this->level << std::endl;
                this->level++;
                vehicle.second->get_player()->inc_loss();
                is_game_over = true;
                break;
            }
        }
        // move the bullets and if they collide with something then
        // erase it from the map and the resource manager
        for (auto& bullet : bullets) {
            if (bullet.second->getRender() && bullet.second != NULL) {
                bullet.second->move();
            } else {
                delete bullet.second;
                bullets.erase(bullet.first);
                break;
            }
        }
        // loop though all powerups
        for (auto& powerup : powerups) {
            // check if any power up needs to be dissapear
            if (powerup.second->getRender() && powerup.second != NULL) {
                powerup.second->check_time();
                // check if any power up is active and need to be removed
            } else if (powerup.second->get_active()) {
                powerup.second->check_pick();
                // if power up have been use wipe it out from the face of this
                // universe
            } else if (!powerup.second->getRender() && powerup.second != NULL &&
                       !powerup.second->get_active()) {
                delete powerup.second;
                powerups.erase(powerup.first);
                break;
            }
        }
        // 1 in 300 chance of spawning a power up every frame
        int i = uuid::gen_random_i(0, 300);
        if (i == 1) {
            // geenrate a random power up
            resourceMan->getPowerup();
        }
    }
}

void Game::game() {
    // glfw: initialize and configure
    int m_type = uuid::gen_random_i(0, 2);
    map = &resourceMan->getMap(map_name(map_types[m_type]), map_types[m_type]);
    std::cout << "Map loaded" << std::endl;
    map_types.erase(map_types.begin() + m_type);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic and events
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        time_logic();
        game_logic();
        resourceMan->updateSound();

        // input
        // -----
        processInput(window, this);
        // render
        render();
        // glfw: swap buffers and poll IO events (keys pressed/released,
        glfwPollEvents();
    }
    // resourceMan->delSoundEngine();
}
