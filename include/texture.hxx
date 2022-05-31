#ifndef TEXTURE_HXX
#define TEXTURE_HXX

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

enum TYPE { COLOR , TEXTURE , BOTH };

class Texture {
    unsigned int texture;
    unsigned int width;
    unsigned int height;
    public:
    Texture();
    Texture(const std::string);
    ~Texture();
    unsigned int getTexture();
    void bindTexture();
};

#endif  // !TEXTURE_HXX
