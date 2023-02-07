#include "DynamicArray.hpp"
#include <tuple>

class Room{
    protected:
        int N, M;       //N colonne, M righe
        Room *top;
        Room *right;
        Room *bottom;
        Room *left;
        Player P;
        DynamicArray<Entity> playground;
        DynamicArray<Enemy> enemies;
        DynamicArray<Bullet> bullets;
        DynamicArray<Artifact> artifacts;
    public:
        Room(int N, int M);
        int get_max_x();
        int get_max_y();
        Player get_player();
        void set_player(Player P);
        void random_generate_walls();
        void random_generate_enemies();
        void random_generate_artifacts();
        std::tuple<int, int, int> random_generate_bullets(int x, int y, DynamicArray<int> excluded_dir);
        void random_move_enemies();
        void move_bullets();
        void add_bullet(int x, int y, int dir);
        void melee_attack(int x, int y);
        bool is_something_in_the_way(int x, int y);
        bool is_enemy_in_the_way(int x, int y);
        bool is_artifact_in_the_way(int x, int y);
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
        DynamicArray<Entity> get_playground();
        DynamicArray<Enemy> get_enemies();
        DynamicArray<Bullet> get_bullets();
        DynamicArray<Artifact> get_artifacts();
};