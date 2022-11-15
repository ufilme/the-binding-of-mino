#include <tuple>

class Entity{
    protected:
        int x, y;
        char icon;
    public:
        Entity(int x, int y);
        Entity();
        std::tuple<int, int> get_pos();
        std::tuple<int, int> set_pos(int x, int y);
        int get_x();
        int get_y();
        char *get_icon();
};

class Player : public Entity{
    public:
        Player(int x, int y);
        Player(const Player& copy);
};

class Enemy : public Entity{
    public:
        Enemy(int x, int y);
};

class Wall : public Entity{
    public:
        Wall(int x, int y);
};

class Artifact : public Entity{
    public:
        Artifact(int x, int y);
};