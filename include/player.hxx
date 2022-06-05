#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <iostream>
#include "../include/vehicle.hxx"

// forward declaration
enum V_COLOR : short;


// Player class
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