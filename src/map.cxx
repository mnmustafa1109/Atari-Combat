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

Map::Map(M_TYPE type) {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    float x = 2.67f;
    float y = 2.67f;
    border =
        &(resourceMan->getShape("border", RECTANGLE, -0.02f, 0.0f, 1.0f, 2.88f,
                                2.16f, 0.0f, &resourceMan->getTexture("border"),
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
    std::vector<float> xs = {1.1, -1.1};
    std::vector<float> ys = {0.8, -0.8};
    x = uuid::gen_random_i(0, 1);
    y = uuid::gen_random_i(0, 1);
    resourceMan->getVehicle("v1", BLUE, xs[x], ys[y],uuid::gen_random_f(0.0f,360.0f));
    xs.erase(xs.begin() + x);
    ys.erase(ys.begin() + y);
    resourceMan->getVehicle("v2", RED, xs[0], ys[0],uuid::gen_random_f(0.0f,360.0f));
    xs.clear ();
    ys.clear ();

    this->scale = 1.0;
}

void Map::draw_objects() {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    std::map<std::string, Obstacle*>& obstacles = resourceMan->getObstacles();
    std::map<std::string, Vehicle*>& vehicles = resourceMan->getVehicles();
    for (auto& vehicle : vehicles) {
        vehicle.second->draw();
    }
    for (auto& obstacle : obstacles) {
        obstacle.second->draw();
    }
    border->draw();
}