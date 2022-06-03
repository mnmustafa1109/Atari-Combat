#ifndef VEHICLE_HXX
#define VEHICLE_HXX
#include <iostream>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/game.hxx"
#include "../include/movement.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include <chrono>

enum V_COLOR:short {
    RED,
    GREEN,
    BLUE
};


class Vehicle:public Shape {
    V_COLOR color;
    float speed ;
    float health;
    std::string name;
    int bullet_count;
    bool destroyed;
    float attack;
    std::chrono::time_point<std::chrono::system_clock> last_shoot;
    public:
        Vehicle();
        Vehicle(std::string name,V_COLOR color,float x , float y , float angle);
        void move(float x, float y,float rotation);
        void shoot();
        void dec_bullet();
        void inc_bullet();
        void inc_health(float x);
        void dec_health(float x);
        float get_health();
        bool get_destroyed();
        float get_attack();
        std::string get_name();
};

#endif // !VEHICLE_HXX