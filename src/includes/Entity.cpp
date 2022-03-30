#include <string>
#include <tuple>
using namespace std;

/*
    type:
        0       player
        1       enemy
*/
class Entity{
    protected:
        int x, y;
        int health;
        int power;
        int speed;
        int type;
        string sprite;
    public:
        Entity(int x, int y){
            this->x = x;
            this->y = y;
        };
        tuple<int, int> _getCoord(){
            return make_tuple(this->x, this->y);
        };
        int _getHealth(){
            return this->health;
        };
        int _getPower(){
            return this->power;
        };
        int _getSpeed(){
            return this->speed;
        };
        int _setHealt(int k){
            this->health += k;
        };
        int _setPower(int k){
            this->power += k;
        };
        int _setSpeed(int k){
            this->speed += k;
        };
        int gotHit(){
            health--;
            return health;
        };
};

class Player: public Entity{
    protected:
        int max_health;
        int max_power;
        int max_speed;
    public:
        Player(int x, int y) : Entity(x, y){
            this->type = 0;
            this->health = 3;
            this->power = 1;
            this->speed = 1;
        };
};

class Priest: public Entity{
    protected:
    public:
        Priest(int x, int y) : Entity(x, y){
            this->type = 1;
            this->health = 3;
            this->power = 1;
            this->speed = 1;
        };
};

class Test: public Entity{
    protected:
    public:
        Test(int x, int y) : Entity(x, y){
            this->type = 1;
            this->health = 6;
            this->power = 1;
            this->speed = 2;
        };
};