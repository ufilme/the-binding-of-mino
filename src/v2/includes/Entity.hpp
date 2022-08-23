#include <tuple>

class Entity{
    protected:
        int x, y;
        char icon;
    public:
        Entity(int x, int y, char icon);
        std::tuple<int, int> get_pos();
        std::tuple<int, int> set_pos(int x, int y);
        char get_icon();
};

class Player : public Entity{
    public:
        Player(int x, int y, char icon) : Entity(x,y,icon){};
};