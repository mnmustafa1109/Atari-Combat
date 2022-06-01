#include "../include/vehicle.hxx"
#include <unistd.h>
#include <chrono>
#include <iostream>
#include <algorithm>


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
    ResourceMan* resourceMan = ResourceMan::getInstance();

    Shader& rectshader = resourceMan->getShader("rectshader");
    if (color == RED) {
        Texture& redtank = resourceMan->getTexture("redtank");
        create(RECTANGLE, 0.0, 0.0, 1.0, 0.14, 0.1667, 0.0, &redtank,
               &rectshader);

    } else if (color == GREEN) {
        Texture& greentank = resourceMan->getTexture("greentank");

        create(RECTANGLE, 0.0, 0.0, 1.0, 0.14, 0.1667, 0.0, &greentank,
               &rectshader);
    } else if (color == BLUE) {
        Texture& bluetank = resourceMan->getTexture("bluetank");

        create(RECTANGLE, 0.0, 0.0, 1.0, 0.14, 0.1667, 0.0, &bluetank,
               &rectshader);
    }
    this->scale = 1.0;
    Shape::move(x, y, 0.0, angle, 0.0);
}

void Vehicle::move(float x, float y, float rotation) {
    // add using trignometric rule

    ResourceMan* resourceMan = ResourceMan::getInstance();
    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();

    std::string key;
    Vehicle val;
    for (auto const& [key, val] : vehicles) {
        if (key != this->name) {
            if (isColliding(val)) {
                speed = -0.01f;
                std::cout << "collision" << std::endl;
            }
        }
    }

    this->x -= y * speed * sin(glm::radians(this->angle));
    this->y += y * speed * cos(glm::radians(this->angle));
    this->angle += rotation;
    if (this->x < -1.35f) {
        this->x = 1.35f;
    }
    if (this->x > 1.35f) {
        this->x = -1.35f;
    }
    if (this->y < -1.0f) {
        this->y = 1.0f;
    }
    if (this->y > 1.0f) {
        this->y = -1.0f;
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

            last_shoot =  std::chrono::system_clock::now();
            // wait for 1 second
            ResourceMan* resourceMan = ResourceMan::getInstance();
            
            Bullet& b1 =
                resourceMan->getBullet(this, STANDARD, 0.0, 0.0, 0.0);
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

// void Vehicle::inc_health() {
//     bulleet_count++;
// }

// void Vehicle::dec_health() {
//     health -= 10;
// }
