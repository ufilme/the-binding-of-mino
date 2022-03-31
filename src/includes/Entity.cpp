#include "Entity.hpp"

/*
    type:
        0       player
        1       enemy
*/

Entity::Entity(int x, int y){
    this->x = x;
    this->y = y;
};
tuple<int, int> Entity::_getCoord(){
    return make_tuple(this->x, this->y);
};
int Entity::_getHealth(){
    return this->health;
};
int Entity::_getPower(){
    return this->power;
};
int Entity::_getSpeed(){
    return this->speed;
};
int Entity::_setHealth(int k){
    this->health += k;
    return this->health;
};
int Entity::_setPower(int k){
    this->power += k;
    return this->power;
};
int Entity::_setSpeed(int k){
    this->speed += k;
    return this->speed;
};
int Entity::gotHit(){
    health--;
    return health;
};

Player::Player(int x, int y) : Entity(x, y){
    this->type = 0;
    this->health = 3;
    this->power = 1;
    this->speed = 1;
};
/*
    adds k to player's health, if player's health is higher
    than max_health, health gets reduced to max_health
*/
int Player::_setHealth(int k){
    Entity::_setHealth(k);
    if(this->health > this->max_health)
        this->health = this->max_health;
    return this->health;
};

Priest::Priest(int x, int y) : Entity(x, y){
    this->type = 1;
    this->health = 3;
    this->power = 1;
    this->speed = 1;
};

Test::Test(int x, int y) : Entity(x, y){
    this->type = 1;
    this->health = 6;
    this->power = 1;
    this->speed = 2;
};