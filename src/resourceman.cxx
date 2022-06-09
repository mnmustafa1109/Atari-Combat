#include "../include/resourceman.hxx"
#include <string>
#include "../include/bullet.hxx"
#include "../include/irrKlang/irrKlang.h"
#include "../include/map.hxx"
#include "../include/obstacle.hxx"
#include "../include/player.hxx"
#include "../include/powerups.hxx"
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"
#include "../include/uuid.hxx"
#include "../include/vehicle.hxx"

// initialize the sound engine and display the error message if any
void ResourceMan::setInitSoundEngine() {
    this->SoundEngine = irrklang::createIrrKlangDevice(
        irrklang::ESOD_ALSA,
        irrklang::ESEO_MULTI_THREADED | irrklang::ESM_NO_STREAMING,
        "default");

    if (!this->SoundEngine) {
        std::cout << "Could not start sound engine" << std::endl;
    }
}

// add the sound name and it will load the sound from its path to the memory
void ResourceMan::addSound(std::string name) {
    std::string path = "../data/audio/" + name + ".ogg";
    if (sounds.find(name) == sounds.end()) {
        sounds[name] = SoundEngine->addSoundSourceFromFile(
            path.c_str(), irrklang::ESM_AUTO_DETECT, true);
    } else {
        // sounds[name]->setIsPaused(false);
    }
    return;
}

// play the sound with the given name pass loop true or false if you wanna loop
// the music or not give error if the sound is not found
void ResourceMan::playSound(std::string name, bool loop) {
    if (sounds.find(name) == sounds.end()) {
        std::cout << "Sound " << name << " not found" << std::endl;
    } else {
        SoundEngine->play3D(sounds[name], {0, 0, 0}, loop);
    }
    return;
}

// delete the sound engine
void ResourceMan::delSoundEngine() {
    this->SoundEngine->drop();
}

// update the sound engine
void ResourceMan::updateSound() {
    // SoundEngine->update();
}

// get the instance of the resource manager class
// cant be initialized more than once as it is a singleton class
ResourceMan* ResourceMan::getInstance() {
    if (instance == nullptr) {
        instance = new ResourceMan();
    }
    return instance;
}

// add the texture to the map if it doesn't exist
// or else return the existing texture
// first the texture name then the path name and in last if you want it fliped
// vertically
Texture& ResourceMan::getTexture(std::string name,
                                 std::string path,
                                 bool flip) {
    if (textures.find(name) == textures.end()) {
        textures[name] = new Texture(path, flip);
    }
    return *textures[name];
}

// add the shader to the map if it doesn't exist
// or else return the existing shader
// first the shader name then the vertex and fragment shader path
Shader& ResourceMan::getShader(std::string name,
                               std::string vertexPath,
                               std::string fragmentPath) {
    if (shaders.find(name) == shaders.end()) {
        shaders[name] = new Shader(vertexPath, fragmentPath);
    }
    return *shaders[name];
}

// add the shape to the map if it doesn't exist
// or else return the existing shape
// first the shape name then the shape type
// its axis width rotation and position
//  and which shader to use along the texture
Shape& ResourceMan::getShape(std::string name,
                             SHAPE shape,
                             float x,
                             float y,
                             float z,
                             float width,
                             float height,
                             float rotation,
                             Texture* texture,
                             Shader* shader) {
    if (shapes.find(name) == shapes.end()) {
        shapes[name] =
            new Shape(shape, x, y, z, width, height, rotation, texture, shader);
    }
    return *shapes[name];
}

// add the vehicle to the map if it doesn't exist
// or else return the existing vehicle
// first the vehicle name then the vehicle type
// its axis width rotation and position
//  and which shader to use along the texture
Vehicle& ResourceMan::getVehicle(std::string name,
                                 float x,
                                 float y,
                                 float angle,
                                 int id) {
    if (vehicles.find(name) == vehicles.end()) {
        vehicles[name] = new Vehicle(name, x, y, angle, id);
    }
    return *vehicles[name];
}

// get the texture from the map if it doesn't exist
// or else print the error message
Texture& ResourceMan::getTexture(std::string name) {
    if (textures.find(name) == textures.end()) {
        std::cout << "Texture " << name << " not found." << std::endl;
    }
    return *textures[name];
}

// get the shader from the map if it doesn't exist
// or else print the error message
Shader& ResourceMan::getShader(std::string name) {
    if (shaders.find(name) == shaders.end()) {
        std::cout << "Shader " << name << " not found." << std::endl;
    }
    return *shaders[name];
}

// get the shape from the map if it doesn't exist
// or else print the error message
Shape& ResourceMan::getShape(std::string name) {
    if (shapes.find(name) == shapes.end()) {
        std::cout << "Shape " << name << " not found." << std::endl;
    }
    return *shapes[name];
}

// get the vehicle from the map if it doesn't exist
// or else print the error message
Vehicle& ResourceMan::getVehicle(std::string name) {
    if (vehicles.find(name) == vehicles.end()) {
        std::cout << "Vehicle " << name << " not found." << std::endl;
    }
    return *vehicles[name];
}

// return the map of the textures reference edition
std::map<std::string, Vehicle*>& ResourceMan::getVehicles() {
    return vehicles;
}

// pass the name of the bullet its shootig vehicle and the position of the
// bullet or vehicle along other positonal variables
Bullet& ResourceMan::getBullet(Vehicle* v,
                               B_TYPE bullet,
                               float x,
                               float y,
                               float angle) {
    // generate a random and unique uuid
    std::string b_name = uuid::generate_uuid_v4();
    while (1) {
        // if it dont exist in the map
        if (bullets.find(b_name) == bullets.end()) {
            bullets[b_name] = new Bullet(b_name, bullet, x, y, angle);
            std::cout << "Bullet " << b_name << " created." << std::endl;
            v->inc_bullet();
            return *bullets[b_name];
        }
        // if it does exist in the map
        else {
            // generate a new uuid
            b_name = uuid::generate_uuid_v4();
        }
    }

    return *bullets[b_name];
}

// get the bullet from the map if it doesn't exist
// or else print the error message
Bullet& ResourceMan::getBullet(std::string name) {
    if (bullets.find(name) == bullets.end()) {
        std::cout << "Bullet " << name << " not found." << std::endl;
    }
    return *bullets[name];
}

// return the map of the bullets reference edition
std::map<std::string, Bullet*>& ResourceMan::getBullets() {
    return bullets;
}

// return the font reference to the name pass to it and along the way create it
// if it doesn't exist in the map yet
Font& ResourceMan::getFont(std::string name, std::string path) {
    if (fonts.find(name) == fonts.end()) {
        fonts[name] = new Font(path);
    }
    return *fonts[name];
}

// get the font from the map if it doesn't exist
// or else print the error message
Font& ResourceMan::getFont(std::string name) {
    if (fonts.find(name) == fonts.end()) {
        std::cout << "Font " << name << " not found." << std::endl;
    }
    return *fonts[name];
}

// return the map of the fonts reference edition
std::map<std::string, Font*>& ResourceMan::getFonts() {
    return fonts;
}

// pass the name and the type of the map
// then return the map and create a new map alon the way if it doesn't existed
// yet
Map& ResourceMan::getMap(std::string name, M_TYPE type) {
    if (maps.find(name) == maps.end()) {
        maps[name] = new Map(type);
    }
    std::cout << "Map " << name << " created." << std::endl;
    return *maps[name];
}

// return the map of the textures reference edition
std::map<std::string, Map*>& ResourceMan::getMaps() {
    return maps;
}
// return an obstacle if its created or esle create it
Obstacle& ResourceMan::getObstacle(std::string name,
                                   H_TYPE obstacle,
                                   float x,
                                   float y,
                                   float angle,
                                   float scale) {
    if (obstacles.find(name) == obstacles.end()) {
        obstacles[name] = new Obstacle(obstacle, x, y, angle, scale);
    }
    return *obstacles[name];
}

// return the map of the obstacles reference edition
std::map<std::string, Obstacle*>& ResourceMan::getObstacles() {
    return obstacles;
}

// return the map of the players reference edition
std::map<int, Player*>& ResourceMan::getPlayers() {
    return players;
}

// pass the player id and the name of the player and the color of the player and
// also the highscore then create a new player and return it if it doesn't exist
// in the map yet
Player& ResourceMan::getPlayer(int id,
                               std::string name,
                               int highscore,
                               V_COLOR color) {
    if (players.find(id) == players.end()) {
        players[id] = new Player(id, name, highscore, color);
    }
    return *players[id];
}

// return the map of the player id passed to it or else print the error message
Player& ResourceMan::getPlayer(int id) {
    if (players.find(id) == players.end()) {
        std::cout << "Player " << id << " not found." << std::endl;
    }
    return *players[id];
}

// return the power up if its created or else display the error message
PowerUps& ResourceMan::getPowerup(std::string name) {
    if (powerups.find(name) == powerups.end()) {
        std::cout << "Powerup " << name << " not found." << std::endl;
    }
    return *powerups[name];
}

// intiialize the powerups postion vector
void ResourceMan::initPowerpose() {
    powerpos.push_back({0.0, 0.0});
    powerpos.push_back({0.0, 0.8});
    powerpos.push_back({0.9, 0.0});
    powerpos.push_back({-0.9, 0.0});
    powerpos.push_back({0.0, -0.8});
    powerpos.push_back({0.8, 0.8});
    powerpos.push_back({-0.8, 0.8});
    powerpos.push_back({0.8, -0.8});
    powerpos.push_back({-0.8, -0.8});
    powerpos.push_back({0.9, 0.7});
    powerpos.push_back({-0.9, 0.7});
    powerpos.push_back({0.9, -0.7});
    powerpos.push_back({-0.9, -0.7});
    powerpos.push_back({0.0, 0.6});
    powerpos.push_back({0.0, -0.6});
    powerpos.push_back({0.6, 0.0});
    powerpos.push_back({-0.6, 0.0});
}

// return the vector of power positions reference edition
std::vector<pos>& ResourceMan::getPowerpose() {
    return powerpos;
}

std::map<std::string,Shape*>& ResourceMan::getShapes(){
    return shapes;
}

// create a new powerup and return it and along the way if it doesn't exist
// yet create it everything is random and automated here
PowerUps& ResourceMan::getPowerup() {
    // generate a random and unique uuid
    std::string p_name = uuid::generate_uuid_v4();
    while (1) {
        // if it dont exist in the map
        if (powerups.find(p_name) == powerups.end()) {
            playSound("appear");
            powerups[p_name] = new PowerUps(p_name);
            std::cout << "Powerup " << p_name << " created." << std::endl;
            return *powerups[p_name];
        }
        // if it does exist in the map
        else {
            // generate a new uuid
            p_name = uuid::generate_uuid_v4();
        }
    }
}

// return the map of the powerups reference edition
std::map<std::string, PowerUps*>& ResourceMan::getPowerups() {
    return powerups;
}

// destructor to delete all the resources from the maps and clearing the map
ResourceMan::~ResourceMan() {
    SoundEngine->removeAllSoundSources();
    for (auto& i : textures) {
        delete i.second;
    }
    for (auto& i : shaders) {
        delete i.second;
    }
    for (auto& i : shapes) {
        delete i.second;
    }
    for (auto& i : vehicles) {
        delete i.second;
    }
    for (auto& i : bullets) {
        delete i.second;
    }
    for (auto& i : maps) {
        delete i.second;
    }
    for (auto& i : obstacles) {
        delete i.second;
    }
    for (auto& i : players) {
        delete i.second;
    }

    textures.clear();
    shaders.clear();
    shapes.clear();
    vehicles.clear();
    bullets.clear();
    maps.clear();
    obstacles.clear();
    players.clear();
}
