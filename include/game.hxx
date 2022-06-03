#ifndef HOME_HXX
#define HOME_HXX
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Game {
    GLFWwindow* window;

    Game();
    public:
    Game(GLFWwindow* window);
    void load();
    void game();
    void render();

};
#endif  // !HOME_HXX