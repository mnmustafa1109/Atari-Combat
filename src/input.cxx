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
    Vehicle& p1 = resourceMan->getVehicle("v1");
    Vehicle& p2 = resourceMan->getVehicle("v2");
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        p1.move(0.0, 1.0, 0.0);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        p1.move(0.00, -1.0, 0.0);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        p1.move(0.00, 0.00, 3.0);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        p1.move(0.00, 0.00, -3.0);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        p2.move(0.0, 1.0, 0.0);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        p2.move(0.00, -1.0, 0.0);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        p2.move(0.00, 0.00, 3.0);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        p2.move(0.00, 0.00, -3.0);
}

void key_callback(GLFWwindow* window,
                  int key,
                  int scancode,
                  int action,
                  int mods) {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    Vehicle& p1 = resourceMan->getVehicle("v1");
    Vehicle& p2 = resourceMan->getVehicle("v2");
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            p1.shoot();
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        p2.shoot();
}