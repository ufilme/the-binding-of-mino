#include "Entity.hpp"

Entity::Entity(int x, int y, char icon){
    this->x = x;
    this->y = y;
    this->icon = icon;
};

std::tuple<int, int> Entity::get_pos(){
    return {this->x, this->y};
}

std::tuple<int, int> Entity::set_pos(int x, int y){
    this->x = x;
    this->y = y;
    return {this->x, this->y};
}

char Entity::get_icon(){
    return icon;
}