#include "Window.hpp"

class GameManager{
    protected:
        int input;
        Room *room;
    public:
        GameManager();
        void start();
        void intro();
        void menu(MenuWindow win);
        void commands(MenuWindow win);
        void pre_update();
        void update(GameWindow win, Room *room);
        void close(GameWindow win);
};