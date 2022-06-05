#ifndef MAP_HXX
#define MAP_HXX
// include vectors
#include "../include/shape.hxx"

// mAP types
enum M_TYPE { DESERT, SNOWY, FOREST };

// function that take a type and convert it to string
std::string map_name(M_TYPE type);

// map class
class Map : public Shape {
    M_TYPE type;
    Shape* border;
    Shape* heart1;
    Shape* heart2;
    Shape* overlay;
    Map();

   public:
    void draw_objects(bool is_game_over);
    Map(M_TYPE type);
};

#endif  // !MAP_HXX