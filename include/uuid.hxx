#ifndef UUID_H
#define UUID_H


#include <random>
#include <sstream>
#include "../include/obstacle.hxx"
#include "../include/map.hxx"
#include "../include/powerups.hxx"

namespace uuid {
static std::random_device rd;
static std::mt19937_64 gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

float gen_random_f(float min, float max);
int gen_random_i(int min, int max);
H_TYPE getRandomHouseType();
M_TYPE getRandomMapType();
P_TYPE getRandomPowerUpType();

std::string generate_uuid_v4();
}  // namespace uuid
#endif // !UUID_H