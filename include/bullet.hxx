#ifndef BULLET_HXX
#define BULLET_HXX
#include <iostream>
#include <chrono>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/game.hxx"
#include "../include/movement.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/vehicle.hxx"

enum B_TYPE {
    STANDARD
};


class Bullet:public Shape {
    B_TYPE type;
    float speed ;
    float health;
    Vehicle* vehicle;
    std::chrono::time_point<std::chrono::system_clock> start;
    bool render;

    std::string name;
    public:
        Bullet();
        Bullet(std::string name,B_TYPE type,float x , float y, float angle);
        int move( );
        void shoot (float x, float y, float angle,Vehicle* vehicle);
        std::chrono::time_point<std::chrono::system_clock> getStart();
        bool getRender();
        void setRender(bool render);
};


#endif // !BULLET_HXX