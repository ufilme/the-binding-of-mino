#include <ncurses.h>
#include "Room.hpp"

/**
 * Implements graphics
 */
class Window{
    protected:
        int max_w, max_h;
        int offset_w, offset_h;
    public:
        WINDOW *win;
        Window();
        void _delete();
        void draw();
        int set_max_w(int w);
        int set_max_h(int h);
        int get_max_w();
        int get_max_h();
        int set_offset_w(int w);
        int set_offset_h(int h);
        int get_offset_w();
        int get_offset_h();
        void screenTooSmall(int w, int h);
};

class IntroWindow : public Window{
    protected:
    public:
        IntroWindow();
        void draw();
};

class MenuWindow : public Window{
    protected:
    public:
        MenuWindow();
        void resize();
        void draw(int pos);
        void cmd_draw(int pos);
};

class GameWindow : public Window{
    protected:
    public:
        GameWindow();
        void draw(Room *room);
};

class GameOverWindow : public Window{
    protected:
    public:
        GameOverWindow();
        void resize();
        void draw();
};