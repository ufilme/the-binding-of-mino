#include "Object.hpp"

Object::Object(int x, int y){
    this->x = x;
    this->y = y;
};

int Object::get_x(){
    return x;
};

int Object::get_y(){
    return y;
};

Wall::Wall(int x, int y) : Object(x, y){

};