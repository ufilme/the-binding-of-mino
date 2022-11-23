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

Player::Player(int x, int y) : Entity(x, y){
    this->icon = "@";
}

Player::Player(Player &copy) : Entity(){
    x = copy.x;
    y = copy.y;
    icon = copy.icon;
};

Enemy::Enemy(int x, int y) : Entity(x, y){
    this->icon = "*";
}

Wall::Wall(int x, int y) : Entity(x, y){
    this->icon = "#";
}

Artifact::Artifact(int x, int y) : Entity(x, y){
    this->icon = "X";
}