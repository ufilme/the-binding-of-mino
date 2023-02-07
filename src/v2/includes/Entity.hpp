#include <tuple>

class Entity{
    protected:
        int x, y;
        const char *icon;
    public:
        Entity();
        Entity(int x, int y);
        bool operator!=(Entity rhs);
        std::tuple<int, int> get_pos();
        std::tuple<int, int> set_pos(int x, int y);
        int get_x();
        int get_y();
        const char *get_icon();
};

class Alive : public Entity{
    protected:
        int health;
    public:
        Alive();
        Alive(int x, int y);
        void inc_health(int value = 1);
        void dec_health(int value = 1);
        int get_health();
};

class Player : public Alive{
    protected:
        int direction;          //0 up, 1 down, 2 right, 3 left
    public:
        Player();
        Player(int x, int y);
        int get_dir();
        void set_dir(int dir);
};

class Enemy : public Alive{
    public:
        Enemy();
        Enemy(int x, int y, int health = 1);
};

class Wall : public Entity{
    public:
        Wall(int x, int y);
};

class Artifact : public Entity{
    public:
        Artifact();
        Artifact(int x, int y);
};

class Bullet : public Entity{
    protected:
        int dir;
    public:
        Bullet();
        Bullet(int x, int y, int dir);
        bool operator!=(Bullet rhs);
        int get_dir();
};