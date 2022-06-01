#ifndef SHAPE_HXX
#define SHAPE_HXX

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "../include/shader.hxx"
#include "../include/texture.hxx"

#include <iostream>

enum SHAPE { CIRCLE, RECTANGLE, TRIANGLE, SQUARE };

class Shape {
   protected:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    Texture* texture;
    Shader* shader;
    SHAPE shape;
    float x;
    float y;
    float z;
    float width;
    float height;
    float angle;
    float scale;

   public:
    Shape();
    Shape(SHAPE shape,
          float x,
          float y,
          float z,
          float width,
          float height,
          float angle,
          Texture* texture,
          Shader* shader);
    void create(SHAPE shape,
                float x,
                float y,
                float z,
                float width,
                float height,
                float angle,
                Texture* texture,
                Shader* shader);
    ~Shape();
    void draw();
    void move(float x, float y, float z, float angle, float scale);
    bool isColliding(Shape* shape);
    float getX();
    float getY();
    float getZ();
    float getWidth();
    float getHeight();
    float getAngle();
};

#endif  // !SHAPE_HXX
