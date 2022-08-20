#include <ncurses.h>

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
};

class GameWindow : public Window{
    protected:
    public:
};

class MenuWindow : public Window{
    protected:
    public:
        void resize();
        void draw(int pos);
        void cmd_draw(int pos);
};