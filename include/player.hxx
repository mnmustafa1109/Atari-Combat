#ifndef PLAYER_HXX
#define PLAYER_HXX
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/map.hxx"
#include "../include/movement.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/vehicle.hxx"

enum V_COLOR : short;

class Player {
    int id;
    std::string name;
    int score;
    int loss;
    int highscore;
    V_COLOR color;

   public:
    Player();
    Player(int id, std::string name, int highscore, V_COLOR color);
    int getId();
    std::string getName();
    int getScore();
    int getHighscore();
    void setScore(int score);
    void setHighscore(int highscore);
    void inc_loss();
    int getLoss();
    V_COLOR getColor();
};
#endif  // !HOME_HXX