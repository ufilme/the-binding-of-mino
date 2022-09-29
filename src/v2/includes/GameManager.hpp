#include <ncurses.h>
#include "Window.hpp"
//#include "Room.hpp"
#include <ctime>

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
};