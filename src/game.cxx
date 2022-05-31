#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include <iostream>

#include "../include/game.hxx"
#include "../include/main.hxx"
#include "../include/movement.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/input.hxx"
#include "../include/resourceman.hxx"

Movement* Movement::instance = nullptr;
ResourceMan* ResourceMan::instance = nullptr;






void game(GLFWwindow* window) {
    // glfw: initialize and configure
    ResourceMan* resourceMan = ResourceMan::getInstance();
    Shader& rectshader = resourceMan->getShader("rectshader","../shaders/rectangle.vs", "../shaders/rectangle.fs");
    Texture& redtank = resourceMan->getTexture("redtank", "../data/textures/red_tank.png");
    Texture& greentank = resourceMan->getTexture("greentank", "../data/textures/green_tank.png");
    Shape& red = resourceMan->getShape("red", SHAPE::RECTANGLE, 0.0, 0.0,  1.0, 0.14, 0.1667,0.0, &redtank, &rectshader);
    red.move(1.4, 1.4, 0.0, 0.0, 0.0, &red);
    red.draw();
    Shape& green = resourceMan->getShape("green", SHAPE::RECTANGLE, 0.0, 0.0,  1.0, 0.14, 0.1667,0.0, &greentank, &rectshader);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        Movement::getInstance()->setDeltaTime(
            currentFrame - Movement::getInstance()->getLastFrame());
        Movement::getInstance()->setLastFrame(currentFrame);

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        red.draw();
        green.draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}