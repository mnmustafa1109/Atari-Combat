#ifndef VEHICLE_HXX
#define VEHICLE_HXX
#include <chrono>
#include <iostream>
#include <vector>
#include "../include/game.hxx"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/movement.hxx"
#include "../include/player.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"

enum V_COLOR : short { RED, GREEN, BLUE };

class Player;
class PowerUps;

class Vehicle : public Shape {
    V_COLOR color;
    float speed;
    float health;
    std::string name;
    int bullet_count;
    bool destroyed;
    float attack;
    int shield;
    bool hit;
    std::chrono::time_point<std::chrono::system_clock> last_shoot;
    std::chrono::time_point<std::chrono::system_clock> last_hit;
    Player* player;
    std::vector<PowerUps*> powerups;

   public:
    void set_speed(float speed);
    float get_speed();
    Vehicle();
    Vehicle(std::string name, float x, float y, float angle, int id);
    void move(float x, float y, float rotation);
    void shoot();
    void dec_bullet();
    void inc_bullet();
    void inc_health(float x);
    void dec_health(float x);
    float get_health();
    void set_hit(bool x);
    bool get_hit();
    bool get_destroyed();
    float get_attack();
    void set_sheild(int x);
    int get_sheild();
    void set_attack(float x);
    std::string get_name();
    void start_last_hit();
    void draw();
    Player* get_player();
    std::string get_h_color();
    std::string get_t_color();
    std::vector<PowerUps*>& get_powerups();
    V_COLOR get_color();
};

#endif  // !VEHICLE_HXX