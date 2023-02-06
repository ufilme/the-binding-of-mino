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
        void pre_update(MenuWindow WIN);
        void update(GameWindow WIN, Room *room);
        void commands(MenuWindow MENU);
        void game_over(GameOverWindow WIN);
        system_clock::duration timed_moving(system_clock::duration start_t, system_clock::duration delay_t,
            Room *room, void (Room::*func)());
        system_clock::duration timed_moving(system_clock::duration start_t, system_clock::duration delay_t,
            Room *room, void (Room::*func)(int, int, int), int x, int y, int dir);
};