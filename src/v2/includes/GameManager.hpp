#include <ncurses.h>
#include "Window.hpp"
#include <ctime>

struct wall{
    int start;          //start == -1 -> ancora da inizializzare
    int end;            //start == -2 -> muro assente
    int axis;
    bool horizontal;
};

struct str_room{
    str_room* top;
    str_room* right;
    str_room* bottom;
    str_room* left;
    
    wall wall1;
    wall wall2;
    /*
    * info su muri, nemici, artefatti...
    */
    int difficulty;
};
typedef str_room* p_room;

class GameManager{
    private:
        int input_ch;
    protected:
        //Player player;
        bool active;
    public:
        p_room room;
        GameManager(bool active);
        void intro();
        void start(MenuWindow WIN);
        void update(GameWindow WIN, Player P);
        void update_screen(Window WIN);
        void commands(MenuWindow MENU);
        void move_room(char direction, int max_y, int max_x);
        void new_room(char direction);
        void create_walls(int max_h, int max_w);
        void gen_wall(int max_h, int max_w);
        w convert_wall(wall w1);
};