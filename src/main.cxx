#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include "../include/stb_image.h"

#include "../include/shader.hxx"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // check how many vertex attributes are supported
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
              << std::endl;

    // build and compile our shader program
    // ------------------------------------
    // we skipped compile log checks this time for readability (if you do
    // encounter issues, add the compile-checks! see previous code samples)

    Shader shaderProgram1 =
        Shader("../shaders/shader1.vs", "../shaders/shader1.fs");
    Shader shaderProgram2 =
        Shader("../shaders/shader2.vs", "../shaders/shader2.fs");
    Shader shaderProgram3 =
        Shader("../shaders/shader3.vs", "../shaders/shader3.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float firstTriangle[] = {
        0.0f,   -0.8f, 0.0f, 0.0f, 1.0f, 1.0f,  // bottom right
        -0.9f,  -0.8f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom left
        -0.45f, 0.2f,  0.0f, 1.0f, 0.0f, 1.0f   // top
    };
    float secondTriangle[] = {
        0.0f,  -0.8f, 0.0f,  // left
        0.9f,  -0.8f, 0.0f,  // right
        0.45f, 0.2f,  0.0f   // top
    };
    float rectangle[] = {
        0.9f,   0.9f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        0.9f,   0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
        -0.45f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
        -0.45f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f};  // top left
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    unsigned int textures[2];
    glGenTextures(2, textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    // set the textures[0] wrapping/filtering options (on currently bound
    // textures[0])
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the textures[0]
    int width, height, nrChannels;
    unsigned char* data = stbi_load("../data/textures/brickes.jpg", &width,
                                    &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load textures[0]" << std::endl;
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    // set the textures[1] wrapping/filtering options (on currently bound
    // textures[1])
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the textures[1]
    data = stbi_load("../data/textures/flags.png", &width, &height,
                     &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load textures[1]" << std::endl;
    }
    stbi_image_free(data);


    unsigned int VBOs[3], VAOs[3], EBO;
    glGenVertexArrays(3, VAOs);  // we can also generate multiple VAOs or
                                 // buffers at the same time
    glGenBuffers(3, VBOs);
    glGenBuffers(1, &EBO);

    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)0);  // Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(3 * sizeof(float)));  // Color attributes
                                                        // stay the same
    glEnableVertexAttribArray(1);
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a
    // different VAO the next few lines second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);  // note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);  // and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, 0,
        (void*)0);  // because the vertex data is tightly packed we can also
                    // specify 0 as the vertex attribute's stride to let OpenGL
                    // figure it out
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // not really necessary as well, but beware of
    // calls that could affect VAOs while this one is bound (like binding
    // element buffer objects, or enabling/disabling vertex attributes)

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    shaderProgram3.use();
    shaderProgram3.set("texture1", 0);
    shaderProgram3.set("texture2", 1); // or with shader clas

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // now when we draw the triangle we first use the vertex and orange
        // fragment shader from the first program
        shaderProgram1.use();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // this call should output an orange triangle
        // then we draw the second triangle using the data from the second VAO
        // when we draw the second triangle we want to use a different shader
        // program so we switch to the shader program with our yellow fragment
        // shader.
        shaderProgram2.use();
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        shaderProgram2.setv4f("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // this call should output a yellow triangle
        // then we draw the rectangle using the data from our second VAO

        shaderProgram3.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glBindVertexArray(VAOs[2]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(3, VAOs);
    glDeleteBuffers(3, VBOs);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    glViewport(0, 0, width, height);
}