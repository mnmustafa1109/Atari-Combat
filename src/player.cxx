#include "../include/player.hxx"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/map.hxx"
#include "../include/movement.hxx"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"
#include "../include/vehicle.hxx"


Player::Player() {}

Player::Player(int id, std::string name, int highscore,V_COLOR color) {
    this->id = id;
    this->name = name;
    this->highscore = highscore;
    this->score = 0;
    this->loss = 0;
    this->color = color;
}

V_COLOR Player::getColor() {
    return this->color;
}

void Player::setScore(int score) {
    this->score += score;
}

void Player::setHighscore(int highscore) {
    this->highscore = highscore;
}

int Player::getId() {
    return this->id;
}

std::string Player::getName() {
    return this->name;
}

int Player::getScore() {
    return this->score;
}

int Player::getHighscore() {
    return this->highscore;
}

void Player::inc_loss() {
    this->loss++;
}

int Player::getLoss() {
    return this->loss;
}
