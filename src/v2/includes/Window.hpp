#include <ncurses.h>

class Window
{
public:
    WINDOW *win;
    Window();
    void resize();
};
