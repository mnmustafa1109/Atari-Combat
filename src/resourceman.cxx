#include "../include/resourceman.hxx"
#include <string>
#include "../include/bullet.hxx"
#include "../include/irrKlang/irrKlang.h"
#include "../include/map.hxx"
#include "../include/obstacle.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/uuid.hxx"
#include "../include/vehicle.hxx"

void ResourceMan::setInitSoundEngine() {
    this->SoundEngine = irrklang::createIrrKlangDevice();
}

void ResourceMan::playSound(std::string name, bool loop ) {
    name = "../data/audio/" + name + ".wav";
    this->SoundEngine->play2D(name.c_str(), loop);
}

ResourceMan* ResourceMan::getInstance() {
    if (instance == nullptr) {
        instance = new ResourceMan();
    }
    return instance;
}

Texture& ResourceMan::getTexture(std::string name, std::string path) {
    if (textures.find(name) == textures.end()) {
        textures[name] = new Texture(path);
    }
    return *textures[name];
}

Shader& ResourceMan::getShader(std::string name,
                               std::string vertexPath,
                               std::string fragmentPath) {
    if (shaders.find(name) == shaders.end()) {
        shaders[name] = new Shader(vertexPath, fragmentPath);
    }
    return *shaders[name];
}
Shape& ResourceMan::getShape(std::string name,
                             SHAPE shape,
                             float x,
                             float y,
                             float z,
                             float width,
                             float height,
                             float rotation,
                             Texture* texture,
                             Shader* shader) {
    if (shapes.find(name) == shapes.end()) {
        shapes[name] =
            new Shape(shape, x, y, z, width, height, rotation, texture, shader);
    }
    return *shapes[name];
}
Vehicle& ResourceMan::getVehicle(std::string name,
                                 V_COLOR vehicle,
                                 float x,
                                 float y,
                                 float angle) {
    if (vehicles.find(name) == vehicles.end()) {
        vehicles[name] = new Vehicle(name, vehicle, x, y, angle);
    }
    return *vehicles[name];
}

Texture& ResourceMan::getTexture(std::string name) {
    if (textures.find(name) == textures.end()) {
        std::cout << "Texture " << name << " not found." << std::endl;
    }
    return *textures[name];
}

Shader& ResourceMan::getShader(std::string name) {
    if (shaders.find(name) == shaders.end()) {
        std::cout << "Shader " << name << " not found." << std::endl;
    }
    return *shaders[name];
}

Shape& ResourceMan::getShape(std::string name) {
    if (shapes.find(name) == shapes.end()) {
        std::cout << "Shape " << name << " not found." << std::endl;
    }
    return *shapes[name];
}
Vehicle& ResourceMan::getVehicle(std::string name) {
    if (vehicles.find(name) == vehicles.end()) {
        std::cout << "Vehicle " << name << " not found." << std::endl;
    }
    return *vehicles[name];
}

std::map<std::string, Vehicle*>& ResourceMan::getVehicles() {
    return vehicles;
}

Bullet& ResourceMan::getBullet(Vehicle* v,
                               B_TYPE bullet,
                               float x,
                               float y,
                               float angle) {
    std::string b_name = uuid::generate_uuid_v4();
    while (1) {
        if (bullets.find(b_name) == bullets.end()) {
            bullets[b_name] = new Bullet(b_name, bullet, x, y, angle);
            std::cout << "Bullet " << b_name << " created." << std::endl;
            v->inc_bullet();
            return *bullets[b_name];
        }
        b_name = uuid::generate_uuid_v4();
    }

    return *bullets[b_name];
}

Bullet& ResourceMan::getBullet(std::string name) {
    if (bullets.find(name) == bullets.end()) {
        std::cout << "Bullet " << name << " not found." << std::endl;
    }
    return *bullets[name];
}

std::map<std::string, Bullet*>& ResourceMan::getBullets() {
    return bullets;
}

Map& ResourceMan::getMap(std::string name, M_TYPE type) {
    if (maps.find(name) == maps.end()) {
        maps[name] = new Map(type);
    }
    std::cout << "Map " << name << " created." << std::endl;
    return *maps[name];
}

std::map<std::string, Map*>& ResourceMan::getMaps() {
    return maps;
}
// return an obstacle if its created or esle create it
Obstacle& ResourceMan::getObstacle(std::string name,
                                   H_TYPE obstacle,
                                   float x,
                                   float y,
                                   float angle,
                                   float scale) {
    if (obstacles.find(name) == obstacles.end()) {
        obstacles[name] = new Obstacle(obstacle, x, y, angle, scale);
    }
    return *obstacles[name];
}

std::map<std::string, Obstacle*>& ResourceMan::getObstacles() {
    return obstacles;
}

ResourceMan::~ResourceMan() {
    for (auto& i : textures) {
        delete i.second;
    }
    for (auto& i : shaders) {
        delete i.second;
    }
    for (auto& i : shapes) {
        delete i.second;
    }
    for (auto& i : vehicles) {
        delete i.second;
    }
    for (auto& i : bullets) {
        delete i.second;
    }
    for (auto& i : maps) {
        delete i.second;
    }
    for (auto& i : obstacles) {
        delete i.second;
    }
    textures.clear();
    shaders.clear();
    shapes.clear();
    vehicles.clear();
    bullets.clear();
    maps.clear();
    obstacles.clear();
}
