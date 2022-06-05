#include "../include/bullet.hxx"
#include <chrono>
#include <iostream>
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
#include "../include/vehicle.hxx"

Bullet::Bullet() {}

Bullet::Bullet(std::string name, B_TYPE type, float x, float y, float angle) {
    this->type = type;
    this->speed = 0.027f;
    this->health = 100.0;
    this->name = name;
    this->render = true;
    this->hit_no = 0;
    ResourceMan* resourceMan = ResourceMan::getInstance();

    Shader& rectshader = resourceMan->getShader("rectshader");
    if (type == STANDARD) {
        Texture& bullet = resourceMan->getTexture("bullet");
        create(RECTANGLE, 0.0, 0.0, 1.0, 0.01581, 0.08, 0.0, &bullet,
               &rectshader);
    }
    this->scale = 1.0;
    Shape::move(x, y, 0.0, angle, 0.0);
}

int Bullet::move() {
    // add using trignometric rule

    ResourceMan* resourceMan = ResourceMan::getInstance();
    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    std::map<std::string, Bullet*>& bullets = resourceMan->getBullets();
    std::map<std::string, Obstacle*>& obstacles = resourceMan->getObstacles();
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> elapsed_seconds;
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    float tempx = this->x;
    float tempy = this->y;
    this->x -= speed * sin(glm::radians(this->angle));
    this->y += speed * cos(glm::radians(this->angle));
    bool colision = false;
    if (this->getRender() == true) {
        if (elapsed_seconds.count() > 5) {
            this->render = false;
            this->vehicle->dec_bullet();
            colision = true;
        }
        // for (auto bullet : bullets) {
        //     if (bullet.second->name != this->name) {
        //         if (bullet.second->getRender() == true &&
        //             this->getRender() == true) {
        //             if (isColliding(bullet.second)) {
        //                 this->render = false;
        //                 bullet.second->setRender(false);
        //                 bullet.second->vehicle->dec_bullet();
        //                 this->vehicle->dec_bullet();
        //                 colision = true;
        //             }
        //         }
        //     }
        // }
        for (auto obstacle : obstacles) {
            if (isColliding(obstacle.second)) {
                // bounce off obstacle
                speed = -speed;
                colision = true;
                if ((tempy < ((obstacle.second->getY() +
                               obstacle.second->getHeight() / 2))) &&
                    (tempy > ((obstacle.second->getY() -
                               obstacle.second->getHeight() / 2)))) {
                    // print angle
                    std::cout << "x angle: " << this->angle << std::endl;

                    this->angle = 180 - this->angle;
                }
                if ((tempx < ((obstacle.second->getX() +
                               obstacle.second->getWidth() / 2))) &&
                    (tempx > ((obstacle.second->getX() -
                               obstacle.second->getWidth() / 2)))) {
                    // print angle
                    std::cout << "y angle: " << this->angle << std::endl;
                    this->angle = 360 - this->angle;
                }
            }
        }
    }
    if (this->getRender() == true) {
        for (auto vehicle : vehicles) {
            if (elapsed_seconds.count() <= 0.140 &&
                vehicle.second->get_name() == this->vehicle->get_name()) {
            } else if (isColliding(vehicle.second)) {
                this->render = false;
                this->vehicle->dec_bullet();
                vehicle.second->dec_health(this->vehicle->get_attack());
                std::cout << "Player "
                          << vehicle.second->get_player()->getName()
                          << " Health :" << vehicle.second->get_health()
                          << std::endl;
                colision = true;
                resourceMan->playSound("destroy");
                vehicle.second->set_hit(true);
                vehicle.second->start_last_hit();
                this->vehicle->get_player()->setScore(10);
                vehicle.second->get_player()->setScore(-10);
                std::cout << "Player "
                          << vehicle.second->get_player()->getName()
                          << " Score :"
                          << vehicle.second->get_player()->getScore()
                          << std::endl;
                return 1;
            }
        }
    }
    if (colision == true) {
        hit_no++;
        this->x = tempx;
        this->y = tempy;
        if (hit_no > 3) {
            this->render = false;
            this->vehicle->dec_bullet();
            resourceMan->playSound("dissapear");
        } else {
            resourceMan->playSound("hit");
        }
        return 1;
    }
    colision = false;
    // bounce off walls
    if (this->x < -1.35f) {
        this->angle = 180 - this->angle;
        colision = true;
        this->x = -1.35f;
    } else if (this->x > 1.35f) {
        this->x = 1.35f;
        this->angle = 180 - this->angle;
        colision = true;
    } else if (this->y < -1.0f) {
        this->y = -1.0f;
        this->angle = -this->angle;
        colision = true;
    } else if (this->y > 1.0f) {
        this->y = 1.0f;
        this->angle = -this->angle;
        colision = true;
    }

    if (colision == true) {
        if (hit_no > 3) {
            this->render = false;
            this->vehicle->dec_bullet();
            resourceMan->playSound("dissapear");
        } else {
            resourceMan->playSound("hit");
            hit_no++;
            speed = -speed;
        }
        return 1;
    }

    Shape::move(0.0, 0.0, 0.0, 0.0, 0.0);
    return 0;
}

void Bullet::shoot(float x, float y, float angle, Vehicle* vehicle) {
    start = std::chrono::system_clock::now();
    this->x = x;
    this->y = y;
    this->z = z;
    this->angle = angle;
    this->vehicle = vehicle;
}

bool Bullet::getRender() {
    return this->render;
}

void Bullet::setRender(bool render) {
    this->render = render;
}
