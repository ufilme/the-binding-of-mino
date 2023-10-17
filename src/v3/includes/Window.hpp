#include "Room.hpp"
#include <ncurses.h>

class Window{
    protected:
        int max_w, max_h;
        int offset_w, offset_h;
    public:
        WINDOW *win;
        Window();
        void draw();
        int set_max_w(int w);
        int set_max_h(int h);
};

class MenuWindow : public Window{
    protected:
    public:
        MenuWindow();
        void resize();
        void draw(int pos);
        void commands_draw(int pos);
};

class GameWindow : public Window{
    protected:
    public:
        GameWindow();
        void draw(Room *room);
};