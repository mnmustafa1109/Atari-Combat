#ifndef MAP_HXX
#define MAP_HXX
// include vectors
#include <vector>
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/obstacle.hxx"


enum M_TYPE { DESERT, SNOWY, FOREST };

class Map : public Shape {
    M_TYPE type;
    Shape* border;
    Map();

   public:
    void draw_objects();
    Map(M_TYPE type);
};

#endif  // !MAP_HXX