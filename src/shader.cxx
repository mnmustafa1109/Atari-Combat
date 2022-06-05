#include "../include/shader.hxx"
#include <GLAD/glad.h>   // include glad to get the required OpenGL headers
#include <GLFW/glfw3.h>  // include glfw3.h to get the required GLFW functions
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

Shader::Shader(const std::string vertexPath, const std::string fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    } else {
        std::cout << vertexPath << " compiled successfully" << std::endl;
    }

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    } else {
        std::cout << fragmentPath << " compiled successfully" << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    } else {
        std::cout << "Program linked successfully" << std::endl;
    }
    // delete shaders; they’re linked into our program and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// us thw shader program
void Shader::use() {
    glUseProgram(ID);
}

// setting an bool unform value in the shader
void Shader::set(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// setting an int unform value in the shader
void Shader::set(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

// setting an float unform value in the shader
void Shader::set(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

// setting an vec4 unform value in the shader like text cordinate
void Shader::setv4f(const std::string& name,
                    float v0,
                    float v1,
                    float v2,
                    float v3) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2, v3);
}

// setting an vec3 unform value in the shader like light position or color
void Shader::setv3f(const std::string& name,
                    float v0,
                    float v1,
                    float v2) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2);
}

// setting an vec4 unform value of glm vector in the shader
void Shader::Matrix4fv(const std::string& name, const glm::mat4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(matrix));
}

// delete the shader program
Shader::~Shader() {
    glDeleteProgram(ID);
}

// constructor for the shader class dont call it directly pweeeeese uwu 
Shader::Shader() {
    ID = 0;
}