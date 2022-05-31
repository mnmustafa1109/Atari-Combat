#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/texture.hxx"

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