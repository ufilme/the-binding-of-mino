#include <ncurses.h>

void print_map(int col, int row, int h_x, int h_y, int e_x, int e_y, bool e_a)
{
    for(int x = 0; x < col; x++)
    {
        for(int y = 0; y < row; y++)
        {
            move(y, x);
            if(x == e_x && y == e_y)
            {
                if(e_a)
                    addch('L');
                else
                    addch(' ');
            }
            else if(x == 0 || y == 0 || x == col-1 || y == row-1)
            {
                addch('#');
            }
            else if(x == h_x && y == h_y)
            {
                printw("\U0001F52B");
                move(y,x+1);
                printw("\U0001F920");
            }
            else
                addch(' ');
        }
    }
}

void handle_proj(int x, int y, int d, int o)
{
    if(d == 1)
        move(y, o);
    else if(d == 2)
        move(o, x);
    else
        move(y, x);
    if(d != 0)
        addch(' ');
    else
        addch('.');
}