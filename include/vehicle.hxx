#ifndef VEHICLE_HXX
#define VEHICLE_HXX
#include <chrono>
#include <iostream>
#include "../include/game.hxx"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/movement.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"

enum V_COLOR : short { RED, GREEN, BLUE };

class Vehicle : public Shape {
    V_COLOR color;
    float speed;
    float health;
    std::string name;
    int bullet_count;
    bool destroyed;
    float attack;
    bool hit;
    std::chrono::time_point<std::chrono::system_clock> last_shoot;
    std::chrono::time_point<std::chrono::system_clock> last_hit;

   public:
    Vehicle();
    Vehicle(std::string name, V_COLOR color, float x, float y, float angle);
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
    std::string get_name();
    void start_last_hit();
    void draw();
};

#endif  // !VEHICLE_HXX