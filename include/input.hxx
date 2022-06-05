#ifndef INPUT_HXX
#define INPUT_HXX 

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "../include/game.hxx"

#include <iostream>


void processInput(GLFWwindow* window,Game* game);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif // !INPUT_HXX