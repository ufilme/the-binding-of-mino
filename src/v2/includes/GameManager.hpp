#include <ncurses.h>
#include "Window.hpp"

class GameManager{
    private:
        int input;
    protected:
        Room *room;
    public:
        GameManager();
        void intro();
        void start();
        void pre_update(MenuWindow WIN);
        void update(GameWindow WIN, Room *room);
        void commands(MenuWindow MENU);
};