#include "../include/map.hxx"
#include <vector>
#include "../include/game.hxx"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/movement.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/uuid.hxx"

Map::Map(){};

std::string map_name(M_TYPE type) {
    switch (type) {
        case DESERT:
            return "desert";
        case SNOWY:
            return "snowy";
        case FOREST:
            return "forest";
        default:
            return "forest";
    }
}

Map::Map(M_TYPE type) {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    float x = 2.67f;
    float y = 2.67f;
    border =
        &(resourceMan->getShape("border", RECTANGLE, -0.02f, 0.0f, 1.0f, 2.88f,
                                2.16f, 0.0f, &resourceMan->getTexture("border"),
                                &resourceMan->getShader("rectshader")));
    overlay = &(resourceMan->getShape("overlay", RECTANGLE, -0.02f, 0.0f, 1.0f,
                                      2.88f, 2.16f, 0.0f,
                                      &resourceMan->getTexture("overlay"),
                                      &resourceMan->getShader("rectshader")));
    Shader& rectshader = resourceMan->getShader("rectshader");
    if (type == DESERT) {
        Texture& desert = resourceMan->getTexture("desert");
        create(RECTANGLE, 0.0, 0.0, 1.0, x, y, 0.0, &desert, &rectshader);
    } else if (type == SNOWY) {
        Texture& snowy = resourceMan->getTexture("snowy");
        create(RECTANGLE, 0.0, 0.0, 1.0, x, y, 0.0, &snowy, &rectshader);
    } else if (type == FOREST) {
        Texture& forest = resourceMan->getTexture("forest");
        create(RECTANGLE, 0.0, 0.0, 1.0, x, y, 0.0, &forest, &rectshader);
    }
    std::cout << "Map background and border created" << std::endl;
    float angle, scale;
    bool isHouse = uuid::gen_random_i(0, 1);
    if (isHouse) {
        x = uuid::gen_random_f(0.2f, 0.5f);
        y = uuid::gen_random_f(0.2f, 0.5f);
        angle = 0.0f;
        scale = uuid::gen_random_f(0.05f, 0.15f);
        resourceMan->getObstacle("h1", uuid::getRandomHouseType(), x, y, angle,
                                 scale);
    }
    isHouse = uuid::gen_random_i(0, 1);
    if (isHouse) {
        x = uuid::gen_random_f(-0.5f, -0.2f);
        y = uuid::gen_random_f(0.2f, 0.5f);
        angle = 0.0f;
        scale = uuid::gen_random_f(0.05f, 0.15f);
        resourceMan->getObstacle("h2", uuid::getRandomHouseType(), x, y, angle,
                                 scale);
    }
    isHouse = uuid::gen_random_i(0, 1);
    if (isHouse) {
        x = uuid::gen_random_f(-0.5f, -0.2f);
        y = uuid::gen_random_f(-0.5f, -0.2f);
        angle = 0.0f;
        scale = uuid::gen_random_f(0.05f, 0.15f);
        resourceMan->getObstacle("h3", uuid::getRandomHouseType(), x, y, angle,
                                 scale);
    }
    isHouse = uuid::gen_random_i(0, 1);
    if (isHouse) {
        x = uuid::gen_random_f(0.2f, 0.5f);
        y = uuid::gen_random_f(-0.5f, -0.2f);
        angle = 0.0f;
        scale = uuid::gen_random_f(0.05f, 0.15f);
        resourceMan->getObstacle("h4", uuid::getRandomHouseType(), x, y, angle,
                                 scale);
    }
    std::cout << "Map houses created" << std::endl;
    std::vector<float> xs = {1.1, -1.1};
    std::vector<float> ys = {0.8, -0.8};
    x = uuid::gen_random_i(0, 20) % 2;
    y = uuid::gen_random_i(0, 20) % 2;
    resourceMan->getVehicle("v1", xs[x], ys[y],
                            uuid::gen_random_f(0.0f, 360.0f), 0);
    xs.erase(xs.begin() + x);
    ys.erase(ys.begin() + y);
    resourceMan->getVehicle("v2", xs[0], ys[0],
                            uuid::gen_random_f(0.0f, 360.0f), 1);
    xs.clear();
    ys.clear();
    std::cout << "Map vehicles created" << std::endl;
    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    heart1 = &(resourceMan->getShape(
        "heart1", RECTANGLE, -1.91f, 1.37f, 0.0f, 0.32022f, 0.30024f, 0.0f,
        &resourceMan->getTexture(vehicles["v1"]->get_h_color()),
        &resourceMan->getShader("rectshader")));
    heart2 = &(resourceMan->getShape(
        "heart2", RECTANGLE, 1.91f, 1.37f, 0.0f, 0.32022f, 0.30024f, 0.0f,
        &resourceMan->getTexture(vehicles["v2"]->get_h_color()),
        &resourceMan->getShader("rectshader")));
    this->scale = 1.0;
}

void Map::draw_objects(bool is_game_over) {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    std::map<std::string, Obstacle*>& obstacles = resourceMan->getObstacles();
    std::map<std::string, Bullet*>& bullets = resourceMan->getBullets();

    // draw vehicles
    for (auto& vehicle : vehicles) {
        vehicle.second->draw();
    }
    // Draw obstacles
    for (auto& obstacle : obstacles) {
        obstacle.second->draw();
    }
    // Draw bullets
    for (auto& bullet : bullets) {
        if (bullet.second->getRender() && bullet.second != NULL) {
            bullet.second->draw();
        }
    }
    // draw powerups
    for (auto& powerup : resourceMan->getPowerups()) {
        if (powerup.second->getRender() && powerup.second != NULL) {
            powerup.second->draw();
        }
    }
    // draw border
    border->draw();
    // drawing hearts of the players on top
    for (auto& vehicle : vehicles) {
        int health = (vehicle.second->get_health()) / 10;
        for (int i = 0; i < health; i++) {
            if (vehicle.second->get_name() == "v1") {
                heart1->move(0.3, 0.0, 0.0, 0.0, 0.0);
                heart1->draw();
            } else {
                heart2->move(-0.3, 0.0, 0.0, 0.0, 0.0);
                heart2->draw();
            }
        }
        if (vehicle.second->get_name() == "v1") {
            heart1->move(health * (-0.3), 0.0, 0.0, 0.0, 0.0);
        } else {
            heart2->move(health * (0.3), 0.0, 0.0, 0.0, 0.0);
        }
        std::vector<PowerUps*>& powerups = vehicle.second->get_powerups();
        int v1, v2;
        v1 = v2 = 1;
        for (int i = 0; i < powerups.size(); i++) {
            if (powerups[i]->get_active()) {
                if (powerups[i]->get_p_name() == "SHIELD" ||
                    powerups[i]->get_p_name() == "SPEED" ||
                    powerups[i]->get_p_name() == "ATTACK") {
                    powerups[i]->init_pose();
                    if (vehicle.second->get_name() == "v1") {
                        v1++;
                        powerups[i]->Shape::move((v1 * 0.1) - 1.59, -1.01, 0.0,
                                                 0.0, 0.0);
                        powerups[i]->Shape::draw();
                    } else {
                        v2++;
                        powerups[i]->Shape::move(-(v2 * 0.1) + 1.59, -1.01, 0.0,
                                                 0.0, 0.0);
                        powerups[i]->Shape::draw();
                    }
                }
            }
        }
    }

    // drawing game over screen
    if (is_game_over) {
        overlay->draw();
    }
}
