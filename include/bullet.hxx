#ifndef BULLET_HXX
#define BULLET_HXX
#include <iostream>
#include <chrono>
#include "../include/shape.hxx"
#include "../include/vehicle.hxx"


// forward declaration
enum V_COLOR:short;
class Vehicle;

// Bullet type
enum B_TYPE:short {
    STANDARD,BIG
};


// Bullet class
class Bullet:public Shape {
    B_TYPE type;
    float speed ;
    float damage;
    Vehicle* vehicle;
    int hit_no;
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