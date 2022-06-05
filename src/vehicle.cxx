#include "../include/vehicle.hxx"
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <iostream>

#include <string>
#include "../include/bullet.hxx"
#include "../include/input.hxx"
#include "../include/movement.hxx"
#include "../include/player.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/texture.hxx"

// should not be called directly
Vehicle::Vehicle() {}

// pass the vehicle name v1 or v2 , its starting position and its starting
// rotation along with the id of its corresponding player
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
    // set the player id
    player = &resourceMan->getPlayer(id);
    // get the player color and set it to the v color
    this->color = this->player->getColor();
    Shader& rectshader = resourceMan->getShader("rectshader");

    // load the texture for the vehicle depending on their color
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

// return the current vector of the powrups that the vehicle have
std::vector<PowerUps*>& Vehicle::get_powerups() {
    return powerups;
}

// move the vehicle... called by the processInput function
void Vehicle::move(float x, float y, float rotation) {
    // load every resources from the resource manager to check colllision
    // detection
    ResourceMan* resourceMan = ResourceMan::getInstance();
    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    std::map<std::string, Obstacle*>& obstacles = resourceMan->getObstacles();
    std::map<std::string, PowerUps*>& powerups = resourceMan->getPowerups();
    // temporary variables to store the old position of the vehicle
    float tempx = this->x;
    float tempy = this->y;
    // claculating the new position of the vehicle using trigonometry
    this->x -= y * speed * sin(glm::radians(this->angle));
    this->y += y * speed * cos(glm::radians(this->angle));
    this->angle += rotation;

    // if the vehicle collide with the other vehicles
    for (auto& vehicle : vehicles) {
        if (vehicle.second->name != this->name) {
            // restore its position if its collide
            if (isColliding(vehicle.second)) {
                this->x = tempx;
                this->y = tempy;
            }
        }
    }

    // if the vehicle collide with any powrups
    for (auto& powerup : powerups) {
        if (powerup.second->getRender()) {
            if (isColliding(powerup.second)) {
                resourceMan->playSound("pick");
                this->powerups.push_back(powerup.second);
                std::cout << powerup.second->get_p_name() << " picked up by "
                          << this->player->getName() << std::endl;
                // do the corresponding task depending on the powrrup
                if (powerup.second->get_p_name() == "HEALTH") {
                    if (this->health < 100.0) {
                        this->health += 10.0;
                    }
                } else if (powerup.second->get_p_name() == "SPEED") {
                    this->speed *= 1.3;
                } else if (powerup.second->get_p_name() == "SHIELD") {
                    this->shield++;
                } else if (powerup.second->get_p_name() == "ATTACK") {
                    this->attack += 10.0;
                }
                powerup.second->set_active(true, this);
            }
        }
    }
    // if the vehicle collide with any obstacles
    for (auto& obstacle : obstacles) {
        if (isColliding(obstacle.second)) {
            // restore its position if its collide
            this->y = tempy;
            this->x = tempx;
        }
    }
    // chec collision with walls
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
    // call this function to update the vehicle's angle
    Shape::move(0.0, 0.0, 0.0, 0.0, 0.0);
}

// start the timer if its hit by some ballz
void ::Vehicle::start_last_hit() {
    last_hit = std::chrono::system_clock::now();
}

// draw the vehicle overriden from shape
void Vehicle::draw() {
    // calculate the last time shot and render it red if its v recently
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

// call this function from processevet callback if clicked on the vehicle
void Vehicle::shoot() {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    // start the timer for the last shot
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> elapsed_seconds;
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - last_shoot;
    // prevent it from shooting too fast
    if (elapsed_seconds.count() > 0.3) {
        resourceMan->playSound("shot");

        // dont let it shoot if there are too much bullets
        if (bullet_count > 20) {
            return;
        } else {
            last_shoot = std::chrono::system_clock::now();
            ResourceMan* resourceMan = ResourceMan::getInstance();
            Bullet* b1;
            // create a bullet with the type depending on the vehicle attack
            // powerups
            if (attack == 10) {
                b1 = &resourceMan->getBullet(this, STANDARD, 0.0, 0.0, 0.0);
            } else if (attack > 10) {
                b1 = &resourceMan->getBullet(this, BIG, 0.0, 0.0, 0.0);
            }
            b1->shoot(x, y, angle, this);
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

// return the color of the vehicle hearts to be displayed in string format
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

// return the color of the vehicle to be displayed in string format
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