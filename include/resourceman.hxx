#ifndef RESOURCEMAN_HXX
#define RESOURCEMAN_HXX
#include <map>
#include <vector>
#include "../include/bullet.hxx"
#include "../include/irrKlang/irrKlang.h"
#include "../include/map.hxx"
#include "../include/obstacle.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/vehicle.hxx"

class Vehicle;
class Bullet;
enum B_TYPE : short;
enum V_COLOR : short;
class ResourceMan {
   public:
    Texture& getTexture(std::string name, std::string path);
    Shader& getShader(std::string name,
                      std::string vertexPath,
                      std::string fragmentPath);
    Shape& getShape(std::string name,
                    SHAPE shape,
                    float x,
                    float y,
                    float z,
                    float width,
                    float height,
                    float rotation,
                    Texture* texture,
                    Shader* shader);

    Texture& getTexture(std::string name);
    Shader& getShader(std::string name);
    Shape& getShape(std::string name);
    Vehicle& getVehicle(std::string name,
                        V_COLOR vehicle,
                        float x,
                        float y,
                        float angle);
    Bullet& getBullet(Vehicle* v, B_TYPE bullet, float x, float y, float angle);
    Vehicle& getVehicle(std::string name);
    Bullet& getBullet(std::string name);
    Obstacle& getObstacle(std::string name,
                          H_TYPE obstacle,
                          float x,
                          float y,
                          float angle,
                          float scale);
    std::map<std::string, Vehicle*>& getVehicles();
    std::map<std::string, Bullet*>& getBullets();
    std::map<std::string, Obstacle*>& getObstacles();
    Map& getMap(std::string name, M_TYPE type);
    std::map<std::string, Map*>& getMaps();
    static ResourceMan* getInstance();
    irrklang::ISoundEngine* getSoundEngine();
    void playSound(std::string name, bool loop = false);
    void setInitSoundEngine();
    ~ResourceMan();

   private:
    irrklang::ISoundEngine* SoundEngine;
    static ResourceMan* instance;
    std::map<std::string, Texture*> textures;
    std::map<std::string, Shader*> shaders;
    std::map<std::string, Shape*> shapes;
    std::map<std::string, Vehicle*> vehicles;
    std::map<std::string, Bullet*> bullets;
    std::map<std::string, Map*> maps;
    std::map<std::string, Obstacle*> obstacles;
};

#endif  // !RESOURCEMAN_HXX