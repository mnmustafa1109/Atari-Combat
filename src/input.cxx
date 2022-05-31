#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../include/input.hxx"
#include "../include/resourceman.hxx"

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    Shape& red =
        resourceMan->getShape("red");
    Shape& green =
        resourceMan->getShape("green");
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        red.move(0.0, 1.0, 0.0, 0.0, 0.0, &green);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        red.move(0.00, -1.0, 0.0, 0.0, 0.0, &green);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        red.move(0.00, 0.00, 0.0, 3.0, 0.0, &green);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        red.move(0.00, 0.00, 0.0, -3.0, 0.0, &green);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        green.move(0.0, 1.0, 0.0, 0.0, 0.0, &red);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        green.move(0.00, -1.0, 0.0, 0.0, 0.0, &red);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        green.move(0.00, 0.00, 0.0, 3.0, 0.0, &red);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        green.move(0.00, 0.00, 0.0, -3.0, 0.0, &red);
}