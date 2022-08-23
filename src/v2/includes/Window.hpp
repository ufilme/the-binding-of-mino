#include <ncurses.h>
#include "Entity.hpp"

class Window{
    protected:
        int max_w, max_h;
    public:
        WINDOW *win;
        Window();
        void _delete();
        void draw();
        int set_max_w(int w);
        int set_max_h(int h);
        int get_max_w();
        int get_max_h();
};

class GameWindow : public Window{
    protected:
    public:
        GameWindow() : Window(){};
        void draw(Player P);
};

class MenuWindow : public Window{
    protected:
    public:
        MenuWindow() : Window(){};
        void resize();
        void draw(int pos);
        void cmd_draw(int pos);
};