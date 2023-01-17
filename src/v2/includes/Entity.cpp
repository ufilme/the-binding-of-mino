#include "Entity.hpp"
#include <cstdlib>
#include <ctime>

Entity::Entity(){};

Entity::Entity(int x, int y){
    this->x = x;
    this->y = y;
};

std::tuple<int, int> Entity::get_pos(){
    return {this->x, this->y};
};

std::tuple<int, int> Entity::set_pos(int x, int y){
    this->x = x;
    this->y = y;
    return {this->x, this->y};
};

int Entity::get_x(){
    return x;
};

int Entity::get_y(){
    return y;
};

const char *Entity::get_icon(){
    return icon;
};

Alive::Alive(){};

Alive::Alive(int x, int y) : Entity(x, y){
    this-> health = 3;
};

void Alive::inc_health(int value){
    this->health += value;
};

void Alive::dec_health(int value){
    this->health -= value;
};

int Alive::get_health(){
    return this->health;
};

Player::Player(){};

Player::Player(int x, int y) : Alive(x, y){
    this->icon = "@";
};

Enemy::Enemy(){};

Enemy::Enemy(int x, int y, int health) : Alive(x, y){
    this->icon = "*";
    this->health = health;
};

Wall::Wall(int x, int y) : Entity(x, y){
    this->icon = "#";
};

Artifact::Artifact(int x, int y) : Entity(x, y){
    this->icon = "X";
};