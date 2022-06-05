#include "../include/bullet.hxx"
#include <chrono>
#include <iostream>
#include "../include/game.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/vehicle.hxx"

// Constructor ... SHOULD NOT call it directly
Bullet::Bullet() {}

// pass the uuid name , bullet type , angle of rotation and the position of the
// vehicle
Bullet::Bullet(std::string name, B_TYPE type, float x, float y, float angle) {
    this->type = type;
    this->speed = 0.03f;
    this->damage = 10.0;
    this->name = name;
    this->render = true;
    this->hit_no = 0;
    ResourceMan* resourceMan = ResourceMan::getInstance();
    // bullets are rendered as rectangle and the png make it rounded
    Shader& rectshader = resourceMan->getShader("rectshader");
    // only standard bullet implmemented
    if (type == STANDARD) {
        Texture& bullet = resourceMan->getTexture("bullet");
        create(RECTANGLE, 0.0, 0.0, 1.0, 0.01581, 0.08, 0.0, &bullet,
               &rectshader);
        // if the attacking vehicle have the attack powerup
    } else if (type == BIG) {
        Texture& bullet = resourceMan->getTexture("bullet");
        create(RECTANGLE, 0.0, 0.0, 1.0, 0.034553, 0.159, 0.0, &bullet,
               &rectshader);
    }
    this->scale = 1.0;
    Shape::move(x, y, 0.0, angle, 0.0);
}

int Bullet::move() {
    // initializing every data from resource manager for obstacle collision
    ResourceMan* resourceMan = ResourceMan::getInstance();
    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    std::map<std::string, Bullet*>& bullets = resourceMan->getBullets();
    std::map<std::string, Obstacle*>& obstacles = resourceMan->getObstacles();
    // calculating the elapsed time from the time it was shoot
    // need this calculation to avoid hitting the bullet from itself
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> elapsed_seconds;
    end = std::chrono::system_clock::now();
    // calculating the elapsed time
    elapsed_seconds = end - start;
    // store the current position of the bullet temp
    // restore it if it collide with something something
    float tempx = this->x;
    float tempy = this->y;
    // moving the bullet using trgnometric rule
    this->x -= speed * sin(glm::radians(this->angle));
    this->y += speed * cos(glm::radians(this->angle));
    bool colision = false;
    // if the bullet is still moving or need to move
    if (this->getRender() == true) {
        // if ellapsed time greater than five bullet dissapear
        if (elapsed_seconds.count() > 5) {
            this->render = false;
            this->vehicle->dec_bullet();
            colision = true;
        }
        // see if hit with any obstacle
        for (auto obstacle : obstacles) {
            if (isColliding(obstacle.second)) {
                // bounce off obstacle
                speed = -speed;
                colision = true;
                if ((tempy < ((obstacle.second->getY() +
                               obstacle.second->getHeight() / 2))) &&
                    (tempy > ((obstacle.second->getY() -
                               obstacle.second->getHeight() / 2)))) {
                    // print angle for debug
                    // x for if it hit horrizontally
                    std::cout << "x angle: " << this->angle << std::endl;

                    this->angle = 180 - this->angle;
                }
                if ((tempx < ((obstacle.second->getX() +
                               obstacle.second->getWidth() / 2))) &&
                    (tempx > ((obstacle.second->getX() -
                               obstacle.second->getWidth() / 2)))) {
                    // print angle
                    // y for if it hit vertically
                    std::cout << "y angle: " << this->angle << std::endl;
                    this->angle = 360 - this->angle;
                }
            }
        }
    }
    if (this->getRender() == true) {
        // check if it hit with any vehicle
        // loop through all the vehicles
        for (auto vehicle : vehicles) {
            // if its the vehicle itself and the elapsed time is too low then
            // dont damage the vehicle
            if (elapsed_seconds.count() <= 0.12 &&
                vehicle.second->get_name() == this->vehicle->get_name()) {
            } else if (isColliding(vehicle.second)) {
                this->render = false;
                this->vehicle->dec_bullet();
                // if the bullet hit the vehicle but have shield
                if (vehicle.second->get_sheild() > 0) {
                    resourceMan->playSound("dissapear");

                } else {
                    // decrease the health of the vehicle
                    vehicle.second->dec_health(this->damage);
                    std::cout << "Player "
                              << vehicle.second->get_player()->getName()
                              << " Health :" << vehicle.second->get_health()
                              << std::endl;
                    colision = true;
                    resourceMan->playSound("destroy");
                    // set the vehicle to be destroyed and hit
                    // to make the vehicle red if needed
                    vehicle.second->set_hit(true);
                    vehicle.second->start_last_hit();
                    this->vehicle->get_player()->setScore(10);
                    vehicle.second->get_player()->setScore(-10);
                    std::cout << "Player "
                              << vehicle.second->get_player()->getName()
                              << " Score :"
                              << vehicle.second->get_player()->getScore()
                              << std::endl;
                }
                return 1;
            }
        }
    }
    // if collision true then stop the bullet from moving
    if (colision == true) {
        hit_no++;
        // restore the position of the bullet
        this->x = tempx;
        this->y = tempy;
        // if its the last time it hitted  then destroy the bullet
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
    // if collision true and bounced from walls
    // make some cool noises
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
    // run that so that the angle adjust itself as it have an angle correction
    // algo
    Shape::move(0.0, 0.0, 0.0, 0.0, 0.0);
    return 0;
}

// render the bullet and make its attribute inherit from the vehicle who shoot
void Bullet::shoot(float x, float y, float angle, Vehicle* vehicle) {
    start = std::chrono::system_clock::now();
    this->x = x;
    this->y = y;
    this->z = z;
    this->angle = angle;
    this->vehicle = vehicle;
    this->damage = vehicle->get_attack();
}

// get if the bullet needs to be render on screen or not
bool Bullet::getRender() {
    return this->render;
}

// set the bullet to be render on screen or not
void Bullet::setRender(bool render) {
    this->render = render;
}
