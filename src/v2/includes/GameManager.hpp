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
        void start(Window WIN);
        void update(Window WIN);
        void update_screen(Window WIN);
        void commands(MenuWindow MENU);
};