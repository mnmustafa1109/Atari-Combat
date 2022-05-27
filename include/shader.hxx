#ifndef SHADER_HXX
#define SHADER_HXX
#include <glad/glad.h>  // include glad to get the required OpenGL headers
#include <iostream>
class Shader {
   public:
    // the program ID
    unsigned int ID;
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
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
};
#endif