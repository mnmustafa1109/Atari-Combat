#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include <iostream>

#include "../include/game.hxx"
#include "../include/input.hxx"
#include "../include/main.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"

void game(GLFWwindow* window) {
    Shader rectshader("../shaders/rectangle.vs", "../shaders/rectangle.fs");
    Texture redtank("../data/textures/red_tank.png");
    Shape red(SHAPE::RECTANGLE, 0.0f, 0.0f, 1.0f, 0.84f, 1.0f, &redtank,
              &rectshader);
    Texture greentank("../data/textures/green_tank.png");
    Shape green(SHAPE::RECTANGLE, 0.0f, 0.0f, 1.0f, 0.84f, 1.0f, &greentank,
                &rectshader);

    // create transformations
    glm::mat4 model;
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection =
        glm::perspective(glm::radians(90.0f),
                         (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        rectshader.Matrix4fv("projection", projection);
        rectshader.Matrix4fv("view", view);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime(),
                            glm::vec3(0.0f, 0.0f, 1.0f));
        rectshader.Matrix4fv("model", model);
        red.draw();
        model = glm::mat4(1.0f);
        rectshader.Matrix4fv("model", model);
        green.draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}