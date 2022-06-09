#include "../include/glad.h"

#include "../include/glfw/glfw3.h"
#include "../include/stb_image.h"

#include <iostream>
#include "../include/texture.hxx"

// pass the texture path and the bool if you need it to be flipped
Texture::Texture(const std::string path, bool flip) {
    // if flipped is true set stbi property to flip the image
    if (flip) {
        stbi_set_flip_vertically_on_load(true);
    } else {
        stbi_set_flip_vertically_on_load(false);
    }
    // load the image
    unsigned char* data =
        stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    // if loading is successfull
    if (data) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // depending if an image is transparent or not
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, data);
        }
        // generating the mip map for the texture
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        std::cout << "Texture " << path << " loaded." << std::endl;
    } else {
        // if loading is not successfull
        std::cout << "Texture failed to load at path: " << path << std::endl;
    }
    stbi_image_free(data);
}

// bind the texture to perform operations on it or to render it
void Texture::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

// delete the texture
Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

// do not use this function if you want to render the texture
Texture::Texture() {}

// get the unsigned int of the texture or GLuint
unsigned int Texture::getTexture() {
    return texture;
}
