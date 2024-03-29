#ifndef GAME_HXX
#define GAME_HXX
#include "../include/glad.h"

#include "../include/glfw/glfw3.h"
#include <iostream>
#include "../include/bullet.hxx"
#include "../include/map.hxx"
#include "../include/powerups.hxx"
#include "../include/resourceman.hxx"
#include "../include/vehicle.hxx"

// forward declaration
class Vehicle;
class Bullet;
class ResourceMan;
class Map;
class PowerUps;

class Game {
    GLFWwindow* window;
    ResourceMan* resourceMan;
    std::vector<M_TYPE> map_types;
    std::map<std::string, Bullet*>& bullets;
    std::map<std::string, Vehicle*>& vehicles;
    std::map<int, Player*>& players;
    std::map<std::string, PowerUps*>& powerups;
    void menu(int i);
    Map* map;
    int level;
    Game();
    bool is_game_over;
    bool replay;

   public:
    Game(GLFWwindow* window);
    void load();
    void game();
    void render();
    void time_logic();
    void game_logic();
    void level_load();
    bool get_game_over() { return is_game_over; };
    void set_game_over(bool is_game_over) { this->is_game_over = is_game_over; }
    bool get_replay() { return replay; }
    void set_replay(bool replay) { this->replay = replay; }
    int get_level() { return level; }
};

#endif  // !HOME_HXX