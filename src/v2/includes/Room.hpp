#include "Object.hpp"
#include <vector>
#include <tuple>

using std::vector;

class Room{
    protected:
        int N, M;
        Room *top;
        Room *right;
        Room *bottom;
        Room *left;
        vector<Object> playground;
    public:
        Room(int N, int M);
        void random_generate_walls();
        bool is_object_in_cell(int x, int y);
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
        std::tuple<vector<Object>::iterator, vector<Object>::iterator> playground_iter();
};