#ifndef MAP_HXX
#define MAP_HXX

#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"

enum M_TYPE { DESERT, SNOWY, FOREST };

class Map : public Shape {
    M_TYPE type;
    
    Map();

   public:
    Map(M_TYPE type);
};

#endif  // !MAP_HXX