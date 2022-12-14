#include "Entity.hpp"
#include <cstdlib>
#include <ctime>

Entity::Entity(int x, int y){
    this->x = x;
    this->y = y;
};

Entity::Entity(){
};

std::tuple<int, int> Entity::get_pos(){
    return {this->x, this->y};
}

std::tuple<int, int> Entity::set_pos(int x, int y){
    this->x = x;
    this->y = y;
    return {this->x, this->y};
}

int Entity::get_x(){
    return x;
};

int Entity::get_y(){
    return y;
};

const char *Entity::get_icon(){
    return icon;
}

Living::Living(int x, int y) : Entity(x, y){
    this-> health = 3;
};

Living::Living(){
};

void Living::inc_health(int value){
    this->health += value;
};

void Living::dec_health(int value){
    this->health -= value;
};


int Living::get_health(){
    return this->health;
};

Player::Player(int x, int y) : Living(x, y){
    this->icon = "@";
}

Player::Player(){
    
}
/*
Player::Player(Player &copy){
    this->x = copy.x;
    this->y = copy.y;
    this->icon = copy.icon;
    this->health = copy.health;
};
*/

Enemy::Enemy(int x, int y, int health) : Living(x, y){
    this->icon = "*";
    this->health = health;
}

Wall::Wall(int x, int y) : Entity(x, y){
    this->icon = "#";
}

Artifact::Artifact(int x, int y) : Entity(x, y){
    this->icon = "X";
}