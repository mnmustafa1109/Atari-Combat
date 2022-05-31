#ifndef MOVEMENT_HXX
#define MOVEMENT_HXX

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

class Movement {
    glm::mat4 model;
    glm::mat4 view;
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