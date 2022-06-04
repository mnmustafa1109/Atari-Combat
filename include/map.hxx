#ifndef MAP_HXX
#define MAP_HXX
// include vectors
#include <vector>
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/obstacle.hxx"


enum M_TYPE { DESERT, SNOWY, FOREST };

std::string map_name(M_TYPE type);

class Map : public Shape {
    M_TYPE type;
    Shape* border;
    Shape* heart1;
    Shape* heart2;
    Map();

   public:
    void draw_objects();
    Map(M_TYPE type);
};

#endif  // !MAP_HXX