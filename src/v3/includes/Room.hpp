#include "DynamicArray.hpp"

class Room{
    protected:
        int N, M;
        Room *top, *right, *bottom, *left;
        Player P;
        DynamicArray<Entity> playground;
        DynamicArray<Enemy> enemies;
    public:
        Room(int N, int M);
        int get_max_x();
        int get_max_y();
        Player get_player();
        void set_player(Player P);
        void random_generate_walls();
        void random_generate_enemies();
        void random_move_enemies();
        bool is_something_in_the_way(int x, int y);
        bool is_enemy_in_the_way(int x, int y);
        Room *get_top();
        Room *get_right();
        Room *get_bottom();
        Room *get_left();
        void set_top(Room *room);
        void set_right(Room *room);
        void set_bottom(Room *room);
        void set_left(Room *room);
        Room *new_room(Room *room, int sidebaby);
        DynamicArray<Entity> get_playground();
        DynamicArray<Enemy> get_enemies();
};