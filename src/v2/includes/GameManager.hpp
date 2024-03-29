#include <ncurses.h>
#include "Window.hpp"
#include <chrono>

using namespace std;
using chrono::system_clock;

class GameManager{
    private:
        int input;
    protected:
        Room *room;
    public:
        GameManager();
        void intro();
        void start();
        void menu();
        void update();
        void commands(MenuWindow MENU);
        void game_over();
        bool checkTerminalSize(Window WIN);
        system_clock::duration timed_moving(system_clock::duration start_t, system_clock::duration delay_t,
            Room *room, void (Room::*func)());
        system_clock::duration timed_moving(system_clock::duration start_t, system_clock::duration delay_t,
            Player *P, void (Player::*func)(bool), bool f);
};