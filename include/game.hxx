#ifndef GAME_HXX
#define GAME_HXX
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/bullet.hxx"
#include "../include/irrKlang/irrKlang.h"
#include "../include/map.hxx"
#include "../include/resourceman.hxx"
#include "../include/vehicle.hxx"

class Vehicle;
class Bullet;
class ResourceMan;
class Map;

class Game {
    GLFWwindow* window;
    ResourceMan* resourceMan;
    std::vector<M_TYPE> map_types;
    std::map<std::string, Bullet*>& bullets;
    std::map<std::string, Vehicle*>& vehicles;
    std::map<int, Player*>& players;
    Map* map;
    int level;
    Game();

   public:
    Game(GLFWwindow* window);
    void load();
    void game();
    void render();
    void time_logic();
    void game_logic();
};
#endif  // !HOME_HXX