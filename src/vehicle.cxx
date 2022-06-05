#include "../include/vehicle.hxx"
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <iostream>

#include <string>
#include "../include/bullet.hxx"
#include "../include/game.hxx"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/input.hxx"
#include "../include/irrKlang/irrKlang.h"
#include "../include/movement.hxx"
#include "../include/player.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/uuid.hxx"

Vehicle::Vehicle() {}

Vehicle::Vehicle(std::string name, float x, float y, float angle, int id) {
    this->bullet_count = 0;
    this->speed = 0.012f;
    this->health = 100.0;
    this->name = name;
    this->destroyed = false;
    this->hit = false;
    this->attack = 10.0f;
    this->shield = 0;
    ResourceMan* resourceMan = ResourceMan::getInstance();
    player = &resourceMan->getPlayer(id);
    this->color = this->player->getColor();
    Shader& rectshader = resourceMan->getShader("rectshader");

    if (color == RED) {
        Texture& redtank = resourceMan->getTexture("redtank");
        create(RECTANGLE, 0.0, 0.0, 1.0, 0.126, 0.15003, 0.0, &redtank,
               &rectshader);

    } else if (color == GREEN) {
        Texture& greentank = resourceMan->getTexture("greentank");

        create(RECTANGLE, 0.0, 0.0, 1.0, 0.126, 0.15003, 0.0, &greentank,
               &rectshader);
    } else if (color == BLUE) {
        Texture& bluetank = resourceMan->getTexture("bluetank");

        create(RECTANGLE, 0.0, 0.0, 1.0, 0.126, 0.15003, 0.0, &bluetank,
               &rectshader);
    }
    this->scale = 1.0;
    Shape::move(x, y, 0.0, angle, 0.0);
}

std::vector<PowerUps*>& Vehicle::get_powerups() {
    return powerups;
}

void Vehicle::move(float x, float y, float rotation) {
    // add using trignometric rule

    ResourceMan* resourceMan = ResourceMan::getInstance();
    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    std::map<std::string, Obstacle*>& obstacles = resourceMan->getObstacles();
    std::map<std::string, PowerUps*>& powerups = resourceMan->getPowerups();

    float tempx = this->x;
    float tempy = this->y;
    this->x -= y * speed * sin(glm::radians(this->angle));
    this->y += y * speed * cos(glm::radians(this->angle));
    this->angle += rotation;

    for (auto& vehicle : vehicles) {
        if (vehicle.second->name != this->name) {
            if (isColliding(vehicle.second)) {
                this->x = tempx;
                this->y = tempy;
            }
        }
    }

    for (auto& powerup : powerups) {
        if (powerup.second->getRender()) {
            if (isColliding(powerup.second)) {
                resourceMan->playSound("pick");
                this->powerups.push_back(powerup.second);
                std::cout << powerup.second->get_p_name() << " picked up by "
                          << this->player->getName() << std::endl;
                if (powerup.second->get_p_name() == "HEALTH") {
                    if (this->health < 100.0) {
                        this->health += 10.0;
                    }
                } else if (powerup.second->get_p_name() == "SPEED") {
                    this->speed *= 1.3;
                } else if (powerup.second->get_p_name() == "SHIELD") {
                    this->shield ++;
                } else if (powerup.second->get_p_name() == "ATTACK") {
                    this->attack += 10.0;
                }
                powerup.second->set_active(true, this);
            }
        }
    }

    for (auto& obstacle : obstacles) {
        if (isColliding(obstacle.second)) {
            // this->y = tempy;
            if ((tempy < ((obstacle.second->getY() +
                           obstacle.second->getHeight() / 2))) &&
                (tempy > ((obstacle.second->getY() -
                           obstacle.second->getHeight() / 2)))) {
                // this->x = tempx;
                if ((tempx > ((obstacle.second->getX() +
                               obstacle.second->getWidth() / 2)))) {
                    this->x = obstacle.second->getX() +
                              obstacle.second->getWidth() / 2 +
                              this->getWidth() / 2;
                }
                if ((tempx < ((obstacle.second->getX() -
                               obstacle.second->getWidth() / 2)))) {
                    this->x = obstacle.second->getX() -
                              obstacle.second->getWidth() / 2 -
                              this->getWidth() / 2;
                }
            }
            if ((tempx < ((obstacle.second->getX() +
                           obstacle.second->getWidth() / 2))) &&
                (tempx > ((obstacle.second->getX() -
                           obstacle.second->getWidth() / 2)))) {
                if ((tempy > ((obstacle.second->getY() +
                               obstacle.second->getHeight() / 2)))) {
                    this->y = obstacle.second->getY() +
                              obstacle.second->getHeight() / 2 +
                              this->getHeight() / 2;
                }
                if ((tempy < ((obstacle.second->getY() -
                               obstacle.second->getHeight() / 2)))) {
                    this->y = obstacle.second->getY() -
                              obstacle.second->getHeight() / 2 -
                              this->getHeight() / 2;
                }
            }
        }
    }

    if (this->x < -1.28f) {
        this->x = -1.28f;
    }
    if (this->x > 1.28f) {
        this->x = 1.28f;
    }
    if (this->y < -0.92f) {
        this->y = -0.92f;
    }
    if (this->y > 0.92f) {
        this->y = 0.92f;
    }
    Shape::move(0.0, 0.0, 0.0, 0.0, 0.0);
}

void ::Vehicle::start_last_hit() {
    last_hit = std::chrono::system_clock::now();
}

void Vehicle::draw() {
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> elapsed_seconds;
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - last_hit;
    if (elapsed_seconds.count() > 0.5) {
        this->hit = false;
    }
    if (hit) {
        glm::vec3 red = {1.0f, 0.3f, 0.3f};
        Shape::draw(red);
    } else {
        Shape::draw();
    }
}

void Vehicle::set_speed(float speed) {
    this->speed = speed;
}

float Vehicle::get_speed() {
    return this->speed;
}

void Vehicle::shoot() {
    ResourceMan* resourceMan = ResourceMan::getInstance();

    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> elapsed_seconds;
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - last_shoot;
    if (elapsed_seconds.count() > 0.16) {
        resourceMan->playSound("shot");
        if (bullet_count > 20) {
            return;
        } else {
            last_shoot = std::chrono::system_clock::now();
            // wait for 1 second
            ResourceMan* resourceMan = ResourceMan::getInstance();

            Bullet& b1 = resourceMan->getBullet(this, STANDARD, 0.0, 0.0, 0.0);
            b1.shoot(x, y, angle, this);
        }
    }
}

void Vehicle::dec_bullet() {
    bullet_count--;
}

void Vehicle::inc_bullet() {
    bullet_count++;
}

void Vehicle::inc_health(float x) {
    health += x;
}

void Vehicle::dec_health(float x) {
    health -= x;
}

float Vehicle::get_health() {
    return health;
}

bool Vehicle::get_destroyed() {
    if (health <= 0) {
        destroyed = true;
    }
    return destroyed;
}

float Vehicle::get_attack() {
    return attack;
}

void Vehicle::set_attack(float attack) {
    this->attack = attack;
}

std::string Vehicle::get_name() {
    return name;
}

bool Vehicle::get_hit() {
    return hit;
}

void Vehicle::set_hit(bool x) {
    hit = x;
}

Player* Vehicle::get_player() {
    return player;
}

void Vehicle::set_sheild(int x) {
    shield = x;
}

int Vehicle::get_sheild() {
    return shield;
}

std::string Vehicle::get_h_color() {
    if (color == RED) {
        return "red_heart";
    } else if (color == BLUE) {
        return "blue_heart";
    } else if (color == GREEN) {
        return "green_heart";
    }
    return "";
}

std::string Vehicle::get_t_color() {
    if (color == RED) {
        return "red_tank";
    } else if (color == BLUE) {
        return "blue_tank";
    } else if (color == GREEN) {
        return "green_tank";
    }
    return "";
}



V_COLOR Vehicle::get_color() {
    return color;
}