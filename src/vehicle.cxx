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
#include "../include/movement.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/uuid.hxx"

Vehicle::Vehicle() {}

Vehicle::Vehicle(std::string name,
                 V_COLOR color,
                 float x,
                 float y,
                 float angle) {
    this->color = color;
    this->bullet_count = 0;
    this->speed = 0.01f;
    this->health = 100.0;
    this->name = name;
    this->destroyed = false;
    this->attack = 10.0f;
    ResourceMan* resourceMan = ResourceMan::getInstance();

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

void Vehicle::move(float x, float y, float rotation) {
    // add using trignometric rule

    ResourceMan* resourceMan = ResourceMan::getInstance();
    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    std::map<std::string, Obstacle*>& obstacles = resourceMan->getObstacles();

    float tempx = this->x;
    float tempy = this->y;
    float tempa = this->angle;
    bool collision = false;
    this->x -= y * speed * sin(glm::radians(this->angle));
    this->y += y * speed * cos(glm::radians(this->angle));
    this->angle += rotation;

    for (auto& vehicle : vehicles) {
        if (vehicle.second->name != this->name) {
            if (isColliding(vehicle.second)) {
                this->x = tempx;
                this->y = tempy;
                this->angle = tempa;
                collision = true;
            }
        }
    }

    for (auto& vehicle : obstacles) {
        if (isColliding(vehicle.second)) {
            this->x = tempx;
            this->y = tempy;
            this->angle = tempa;
            collision = true;
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
    speed = 0.01f;
}

void Vehicle::shoot() {
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> elapsed_seconds;
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - last_shoot;

    if (elapsed_seconds.count() > 0.7) {
        if (bullet_count > 10) {
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

std::string Vehicle::get_name() {
    return name;
}
