#include <tuple>

class Entity{
    protected:
        int x, y;
        const char *icon;
    public:
        Entity(int x, int y);
        Entity();
        std::tuple<int, int> get_pos();
        std::tuple<int, int> set_pos(int x, int y);
        int get_x();
        int get_y();
        const char *get_icon();
};

class Living : public Entity{
    protected:
        int health;
    public:
        Living(int x, int y);
        Living();
        void inc_health(int value = 1);
        void dec_health(int value = 1);
        int get_health();
};

class Player : public Living{
    public:
        Player(int x, int y);
        Player();
        //Player(Player &copy);
};

class Enemy : public Living{
    public:
        Enemy(int x, int y, int health = 1);
};

class Wall : public Entity{
    public:
        Wall(int x, int y);
};

class Artifact : public Entity{
    public:
        Artifact(int x, int y);
};