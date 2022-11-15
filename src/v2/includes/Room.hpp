#include "Entity.hpp"
#include <typeinfo>
#include <vector>
#include <tuple>

using std::vector;

class Room{
    protected:
        int N, M;       //N colonne, M righe
        Room *top;
        Room *right;
        Room *bottom;
        Room *left;
        Player P;
        vector<Entity> playground;
    public:
        Room(int N, int M, Player P);
        Player get_player();
        void random_generate_walls();
        void random_generate_enemies();
        void random_move_enemies();
        bool is_cell_free(int x, int y);
        Room *get_top();
        Room *get_right();
        Room *get_bottom();
        Room *get_left();
        void set_top(Room *room);
        void set_right(Room *room);
        void set_bottom(Room *room);
        void set_left(Room *room);
        Room *new_room(Room *room, int sidebaby);
        void change_room();
        std::tuple<vector<Entity>::iterator, vector<Entity>::iterator> playground_iter();
};