#include <ncurses.h>
#include "Window.hpp"

class GameManager{
    private:
        int input_ch;
    protected:
        //Player player;
        bool active;
    public:
        GameManager(bool active);
        void intro();
        void start(MenuWindow WIN);
        void update(GameWindow WIN, Player P);
        void update_screen(Window WIN);
        void commands(MenuWindow MENU);
};