#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../include/game.hxx"
#include "../include/input.hxx"
#include "../include/resourceman.hxx"

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, Game* game) {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    Vehicle& p1 = resourceMan->getVehicle("v1");
    Vehicle& p2 = resourceMan->getVehicle("v2");
    // escape key closes window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    // movement of both players
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
    // if game is paused due to game over wait until enter is pressed
    // then load the new level
    if (game->get_game_over()) {
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            resourceMan->playSound("enter");
            game->level_load();
        }
    }
}

// key call back for the input.. unlike process input which is called every
// frame
void key_callback(GLFWwindow* window,
                  int key,
                  int scancode,
                  int action,
                  int mods) {
    ResourceMan* resourceMan = ResourceMan::getInstance();
    Vehicle& p1 = resourceMan->getVehicle("v1");
    Vehicle& p2 = resourceMan->getVehicle("v2");
    // shooting keys for the player 1
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        p1.shoot();
    }
    // shooting keys for the player 2
    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        p2.shoot();
    }
}