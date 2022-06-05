#include "../include/powerups.hxx"
#include <chrono>
#include <iostream>

#include <string>
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/texture.hxx"
#include "../include/uuid.hxx"
#include "../include/vehicle.hxx"

// return the power up type in string format
std::string PowerUps::get_p_name() {
    if (type == SHIELD) {
        return "SHIELD";
    } else if (type == SPEED) {
        return "SPEED";
    } else if (type == ATTACK) {
        return "ATTACK";
    } else if (type == HEALTH) {
        return "HEALTH";
    }
    return "";
}

// set the power up as active to the vehicle
void PowerUps::set_active(bool active, Vehicle* vehicle) {
    pick = std::chrono::system_clock::now();
    is_render = false;
    is_active = active;
    this->vehicle = vehicle;
}

// check the active status of the power up
bool PowerUps::get_active() {
    return is_active;
}

// do not call this function directly
PowerUps::PowerUps(){};

// pass the uuid of the powerup,
PowerUps::PowerUps(std::string uuid) {
    start = std::chrono::system_clock::now();
    type = uuid::getRandomPowerUpType();
    // initialize the powerup
    is_render = true;
    is_active = false;
    ResourceMan* resourceMan = ResourceMan::getInstance();

    float w = 0.12f;
    float h = 0.12f;
    float x;
    float y;
    // select a postion of the power up on the map
    int i = uuid::gen_random_i(0, resourceMan->getPowerpose().size() - 1);
    pos p = resourceMan->getPowerpose()[i];
    resourceMan->getPowerpose().erase(resourceMan->getPowerpose().begin() + i);
    if (resourceMan->getPowerpose().size() == 1) {
        resourceMan->initPowerpose();
    }
    // load the corresponding texture for the power up
    Shader& rectshader = resourceMan->getShader("rectshader");
    if (type == SHIELD) {
        Texture& shield = resourceMan->getTexture("shield");
        create(RECTANGLE, 0, 0, 1.0, w, h, 0.0, &shield, &rectshader);
    } else if (type == SPEED) {
        Texture& speed = resourceMan->getTexture("speed");
        create(RECTANGLE, 0, 0, 1.0, w, h, 0.0, &speed, &rectshader);
    } else if (type == ATTACK) {
        Texture& attack = resourceMan->getTexture("attack");
        create(RECTANGLE, 0, 0, 1.0, w, h, 0.0, &attack, &rectshader);
    } else if (type == HEALTH) {
        Texture& health = resourceMan->getTexture("health");
        create(RECTANGLE, 0, 0, 1.0, w, h, 0.0, &health, &rectshader);
    }
    this->scale = 1.0;
    this->angle = 0.0;
    // move the power up to the selected position
    Shape::move(p.x, p.y, 0.0, angle, 0.0);
    std::cout << "PowerUps background and border created" << std::endl;
}

void PowerUps::setRender(bool render) {
    is_render = render;
}

bool PowerUps::getRender() {
    return is_render;
}

// check from how much time the power up is appeared on the screen and if it is
// there for too long then dont render it
void PowerUps::check_time() {
    std::chrono::time_point<std::chrono::system_clock> end =
        std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    if (elapsed_seconds.count() > 5.0) {
        is_render = false;
    }
}
std::string PowerUps::get_uuid() {
    return uuid;
}

// check from how many time the power up is active and if it is active for too
// long then deactivate it
void PowerUps::check_pick() {
    std::chrono::time_point<std::chrono::system_clock> end =
        std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - pick;
    // check the active status of the power up
    if (elapsed_seconds.count() > 3.0) {
        is_active = false;
        std::vector<PowerUps*>& p = vehicle->get_powerups();
        for (int i = 0; i < p.size(); i++) {
            // undo the power up from its vehicle
            if ((p[i]->get_uuid()) == (this->get_uuid())) {
                p.erase(p.begin() + i);
                std::cout << this->get_p_name() << " remmoved from "
                          << vehicle->get_player()->getName() << "'s powerups"
                          << std::endl;
                // reverting the changes depending on the power up
                if (type == SPEED) {
                    vehicle->set_speed(vehicle->get_speed() * 0.76923077);
                } else if (type == ATTACK) {
                    vehicle->set_attack(vehicle->get_attack() - 10);
                } else if (type == SHIELD) {
                    vehicle->set_sheild(vehicle->get_sheild() - 1);
                }
                break;
            }
        }
    }
}