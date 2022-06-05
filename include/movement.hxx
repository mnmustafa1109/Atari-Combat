#ifndef MOVEMENT_HXX
#define MOVEMENT_HXX

#include "../include/glm/glm.hpp"

class Movement {
    // store the model translation matrix
    glm::mat4 model;
    // store the current view
    glm::mat4 view;
    // store the projection matrix
    glm::mat4 projection;
    float deltaTime;  // time between current frame and last frame
    float lastFrame;
    static Movement* instance;
    Movement();

   public:
    static Movement* getInstance();
    void move(float x,
              float y,
              float z,
              float angle,
              float speed);
    glm::mat4 getModel();
    glm::mat4 getView();
    glm::mat4 getProjection();
    float getDeltaTime()const ;
    float getLastFrame()const;
    void setLastFrame(float lastFrame) ;
    void setDeltaTime(float deltaTime) ;
    void clear();
};

#endif  //