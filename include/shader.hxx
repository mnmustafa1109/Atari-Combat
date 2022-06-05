#ifndef SHADER_HXX
#define SHADER_HXX
#include "../include/glm/glm.hpp"

#include <iostream>


// class for shader
class Shader {
   public:
    // the program ID
    unsigned int ID;
    // constructor reads and builds the shader
    Shader();
    ~Shader();
    Shader(const std::string vertexPath, const std::string fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void set(const std::string& name, bool value) const;
    void set(const std::string& name, int value) const;
    void set(const std::string& name, float value) const;
    void setv4f(const std::string& name,
                float v0,
                float v1,
                float v2,
                float v3) const;
    void setv3f(const std::string& name, float v0, float v1, float v2) const;
    void Matrix4fv(const std::string& name, const glm::mat4& matrix) const;
};
#endif