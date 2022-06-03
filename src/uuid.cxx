#include <random>
#include <sstream>
#include "../include/uuid.hxx"
#include "../include/obstacle.hxx"
using namespace uuid;



// generating a random number depending on the range it gives
float uuid::gen_random_f(float min, float max) {
    std::uniform_real_distribution<float> distr(min, max);
    return distr(gen);
}

int uuid::gen_random_i(int min, int max) {
    std::uniform_int_distribution<int> distr(min, max);
    return distr(gen);
}

H_TYPE  uuid::getRandomHouseType() {
    int random = gen_random_i(0, 5);
    switch (random) {
        case 0:
            return HOUSE1;
        case 1:
            return HOUSE2;
        case 2:
            return HOUSE3;
        case 3:
            return HOUSE4;
        case 4:
            return HOUSE5;
        case 5:
            return HOUSE6;
    }
}

std::string uuid::generate_uuid_v4() {
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    return ss.str();
}

