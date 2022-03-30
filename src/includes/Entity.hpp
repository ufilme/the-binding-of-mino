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
        Entity(int x, int y);
        tuple<int, int> _getCoord();
        int _getHealth();
        int _getPower();
        int _getSpeed();
        int _setHealth(int k);
        int _setPower(int k);
        int _setSpeed(int k);
        int gotHit();
};

class Player: public Entity{
    protected:
        int max_health;
        int max_power;
        int max_speed;
    public:
        Player(int x, int y);
        int _setHealth(int k);
};

class Priest: public Entity{
    protected:
    public:
        Priest(int x, int y);
};

class Test: public Entity{
    protected:
    public:
        Test(int x, int y);
};