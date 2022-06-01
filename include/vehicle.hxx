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

enum V_COLOR {
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
    std::chrono::time_point<std::chrono::system_clock> last_shoot;
    public:
        Vehicle();
        Vehicle(std::string name,V_COLOR color,float x , float y , float angle);
        void move(float x, float y,float rotation);
        void shoot();
        void dec_bullet();
        void inc_bullet();
};

#endif // !VEHICLE_HXX