#ifndef INPUT_HXX
#define INPUT_HXX 

#include "../include/glad.h"

#include "../include/glfw/glfw3.h"
#include "../include/game.hxx"

#include <iostream>


void processInput(GLFWwindow* window,Game* game);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif // !INPUT_HXX