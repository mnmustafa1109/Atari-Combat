#ifndef RESOURCEMAN_HXX
#define RESOURCEMAN_HXX
#include <map>
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/vehicle.hxx"
#include "../include/texture.hxx"
#include "../include/bullet.hxx"
#include "../include/map.hxx"

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
    Vehicle& getVehicle(std::string name, V_COLOR vehicle, float x, float y,float angle);
    Bullet& getBullet(Vehicle* v, B_TYPE bullet, float x, float y,float angle);
    Vehicle& getVehicle(std::string name);
    Bullet& getBullet(std::string name);
    std::map<std::string, Vehicle*> & getVehicles();
    std::map<std::string, Bullet*> & getBullets();
    Map& getMap(std::string name,M_TYPE type);
    static ResourceMan* getInstance();
    ~ResourceMan();

   private:
    static ResourceMan* instance;
    std::map<std::string, Texture*> textures;
    std::map<std::string, Shader*> shaders;
    std::map<std::string, Shape*> shapes;
    std::map<std::string, Vehicle*> vehicles;
    std::map<std::string, Bullet*> bullets;
    std::map<std::string, Map*> maps;

};

#endif  // !RESOURCEMAN_HXX