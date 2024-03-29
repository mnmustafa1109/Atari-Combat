#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"

Obstacle::Obstacle() {}

Obstacle::Obstacle(H_TYPE type, float x, float y, float angle, float scale) {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    // load the shader
    Shader& rectshader = resourceMan->getShader("rectshader");
    // check the house type and load its corresponding texture and also assign
    // its widht and height and scale it to the size of the house
    if (type == HOUSE1) {
        height = 3.85f;
        width = 4.16f;
        width *= scale;
        height *= scale;
        Texture& house1 = resourceMan->getTexture("house1");
        create(RECTANGLE, 0.0, 0.0, 1.0, width, height, angle, &house1,
               &rectshader);
    } else if (type == HOUSE2) {
        width = 3.04f;
        height = 1.80f;
        width *= scale;
        height *= scale;
        Texture& house2 = resourceMan->getTexture("house2");
        create(RECTANGLE, 0.0, 0.0, 1.0, width, height, angle, &house2,
               &rectshader);
    } else if (type == HOUSE3) {
        width = 2.08f;
        height = 1.81f;
        width *= scale;
        height *= scale;
        Texture& house3 = resourceMan->getTexture("house3");
        create(RECTANGLE, 0.0, 0.0, 1.0, width, height, angle, &house3,
               &rectshader);
    } else if (type == HOUSE4) {
        width = 4.84f;
        height = 2.92f;
        width *= scale;
        height *= scale;
        Texture& house4 = resourceMan->getTexture("house4");
        create(RECTANGLE, 0.0, 0.0, 1.0, width, height, angle, &house4,
               &rectshader);
    } else if (type == HOUSE5) {
        width = 3.76f;
        height = 5.68f;
        width *= scale;
        height *= scale;
        Texture& house5 = resourceMan->getTexture("house5");
        create(RECTANGLE, 0.0, 0.0, 1.0, width, height, angle, &house5,
               &rectshader);
    } else if (type == HOUSE6) {
        width = 3.56f;
        height = 5.71f;
        width *= scale;
        height *= scale;
        Texture& house6 = resourceMan->getTexture("house6");
        create(RECTANGLE, 0.0, 0.0, 1.0, width, height, angle, &house6,
               &rectshader);
    }
    this->scale = 1.0;
    // move the house to the x and y coordinates and change its angle
    Shape::move(x, y, 0.0, angle, 0.0);
}