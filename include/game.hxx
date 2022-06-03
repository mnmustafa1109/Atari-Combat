#ifndef HOME_HXX
#define HOME_HXX
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "../include/irrKlang/irrKlang.h"
#include "../include/resourceman.hxx"
#include "../include/map.hxx"

#include <iostream>

class ResourceMan;
class Map;

class Game {
    GLFWwindow* window;
    irrklang::ISoundEngine* SoundEngine;
    ResourceMan* resourceMan;
    Map* map;
    int level;
    Game();

   public:
    Game(GLFWwindow* window);
    void load();
    void game();
    void render();
    void time_logic();
};
#endif  // !HOME_HXX