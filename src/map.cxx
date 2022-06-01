#include "../include/map.hxx"
#include "../include/game.hxx"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/movement.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"

Map::Map(){};

Map::Map(M_TYPE type) {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    float x = 2.67f;
    float y = 2.67f;
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
    this->scale = 1.0;
}