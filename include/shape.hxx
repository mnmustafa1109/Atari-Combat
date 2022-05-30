#ifndef SHAPE_HXX
#define SHAPE_HXX

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "../include/shader.hxx"
#include "../include/texture.hxx"

#include <iostream>

enum SHAPE { CIRCLE, RECTANGLE, TRIANGLE, SQUARE };

class Shape {
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

    Shape();

   public:
    Shape(SHAPE shape,
          float x,
          float y,
          float z,
          float width,
          float height,
          Texture* texture,
          Shader* shader);
    ~Shape();
    void draw();
};

#endif  // !SHAPE_HXX
