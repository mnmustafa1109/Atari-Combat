#ifndef POWERUPS_HXX
#define POWERUPS_HXX
#include <chrono>
#include <iostream>

#include "../include/player.hxx"
#include "../include/shape.hxx"
#include "../include/vehicle.hxx"


// power up types 
enum P_TYPE : short { SHIELD, SPEED, ATTACK, HEALTH };

// forward declaration
class Player;
class Vehicle;

// power up class
class PowerUps : public Shape {
    P_TYPE type;
    bool is_render;
    bool is_active;
    Vehicle* vehicle;
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> pick;
    std::string uuid;

   public:
    PowerUps();
    PowerUps(std::string uuid);
    void setRender(bool render);
    bool getRender();
    void check_time();
    void set_active(bool active, Vehicle* vehicle);
    bool get_active();
    void check_pick();
    std::string get_p_name();
    std::string get_uuid();
};

#endif  // !VEHICLE_HXX