#ifndef RESOURCEMAN_HXX
#define RESOURCEMAN_HXX
#include <map>
#include <vector>
#include "../include/bullet.hxx"
#include "../include/font.hxx"
#include "../include/irrKlang/irrKlang.h"
#include "../include/map.hxx"
#include "../include/obstacle.hxx"
#include "../include/player.hxx"
#include "../include/powerups.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/vehicle.hxx"

// forward declaration
class Vehicle;
class Bullet;
class Player;
class Font;
class PowerUps;
enum B_TYPE : short;
enum V_COLOR : short;

// poisiton to store the postion of the power ups
struct pos {
    float x;
    float y;
};

// Resource manager class
class ResourceMan {
   public:
    Texture& getTexture(std::string name, std::string path, bool flip);
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
                        float x,
                        float y,
                        float angle,
                        int id);
    Bullet& getBullet(Vehicle* v, B_TYPE bullet, float x, float y, float angle);
    Vehicle& getVehicle(std::string name);
    Bullet& getBullet(std::string name);
    Obstacle& getObstacle(std::string name,
                          H_TYPE obstacle,
                          float x,
                          float y,
                          float angle,
                          float scale);
    Player& getPlayer(int id, std::string name, int highscore, V_COLOR color);
    Player& getPlayer(int id);
    PowerUps& getPowerup();
    PowerUps& getPowerup(std::string name);
    Font& getFont(std::string name, std::string path);
    Font& getFont(std::string name);
    std::map<std::string, Vehicle*>& getVehicles();
    std::map<std::string, Bullet*>& getBullets();
    std::map<std::string, Obstacle*>& getObstacles();
    std::map<std::string, PowerUps*>& getPowerups();

    std::map<int, Player*>& getPlayers();
    std::map<std::string, Font*>& getFonts();
    std::map<std::string,Shape*>& getShapes();
    Map& getMap(std::string name, M_TYPE type);
    std::map<std::string, Map*>& getMaps();
    static ResourceMan* getInstance();
    void delSoundEngine();
    void playSound(std::string name, bool loop = false);
    void addSound(std::string name);
    void updateSound();
    void setInitSoundEngine();
    void initPowerpose();
    std::vector<pos>& getPowerpose();
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
    std::map<int, Player*> players;
    std::map<std::string, irrklang::ISoundSource*> sounds;
    std::map<std::string, Font*> fonts;
    std::map<std::string, PowerUps*> powerups;
    std::vector<pos> powerpos;
};

#endif  // !RESOURCEMAN_HXX