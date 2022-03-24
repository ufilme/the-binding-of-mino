#include <string>
#include <tuple>
using namespace std;

class Entity{
    protected:
        int x, y;
        int health;
        int power;
        int speed;
        string sprite;
    public:
        Entity(int x, int y, int health){
            this->x = x;
            this->y = y;
            this->health = health;
        };
        tuple<int, int> _getCoord(){
            return make_tuple(this->x, this->y);
        };
        int _getHealth(){
            return this->health;
        };
        int gotHit(){
            health--;
            return health;
        };
};