#include <ncurses.h>
#include "Entity.hpp"

struct wall{
    int start;          //start == -1 -> ancora da inizializzare
    int end;            //start == -2 -> muro assente
    int axis;
    bool horizontal;
};

struct str_room{
    str_room* top;
    str_room* right;
    str_room* bottom;
    str_room* left;
    
    wall wall1;
    wall wall2;
    /*
    * info su muri, nemici, artefatti...
    */
    int difficulty;
};
typedef str_room* p_room;

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
};

class MenuWindow : public Window{
    protected:
    public:
        MenuWindow() : Window(){};
        void resize();
        void draw(int pos);
        void cmd_draw(int pos);
};

class GameWindow : public Window{
    protected:
    public:
        //GameWindow() : Window(){};
        GameWindow(MenuWindow MENU);
        void draw(Player P, wall wall1, wall wall2);
};