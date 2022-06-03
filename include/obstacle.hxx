#ifndef OBSTACLE_HXX
#define OBSTACLE_HXX

#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"

enum H_TYPE { HOUSE1 , HOUSE2 , HOUSE3, HOUSE4, HOUSE5, HOUSE6, HOUSE7 };

class Obstacle : public Shape {
    H_TYPE type;
    
    Obstacle();

   public:
    Obstacle(H_TYPE type, float x , float y , float angle , float scale);
};

#endif  // !MAP_HXX