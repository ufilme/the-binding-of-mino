#include <ncurses.h>
#include "library.h"
#include <ctime>
#include <chrono>
using namespace std;

class projectile
{
    protected:
        int x, y;
        char dir;
    public:
        projectile(int px, int py, char d)
        {
            x = px;
            y = py;
            dir = d;
        };
        int xaxis(int s)
        {
            if(s == 0)
                x--;
            else if(s == 1)
                x++;
            return x;
        };
        int yaxis(int s)
        {
            if(s == 0)
                y--;
            else if(s == 1)
                y++;
            return y;
        };
        int direc()
        {
            return dir;
        };
};

class entity
{
    protected:
        int health;
        int x;
        int y;

    public:
        entity(int h, int row, int col)
        {
            health = h;
            x = col;
            y = row;
        };
        bool got_hit()
        {
            health--;
            return health;
        };
        int life()
        {
            return health;
        };
        int xaxis(int s)
        {
            if(s == 0)
                x--;
            else if(s == 1)
                x++;
            return x;
        };
        int yaxis(int s)
        {
            if(s == 0)
                y--;
            else if(s == 1)
                y++;
            return y;
        };
};

class hero: public entity
{
    protected:
    public:
        hero(int h, int row, int col):entity(h, row, col){};
        projectile shoot(char d)
        {
            projectile p = projectile(x, y, d);
            return p;
        };
        /*int xaxis(int s)
        {
            if(s == 0)
                x--;
            else if(s == 1)
                x++;
            return x;
        };
        int yaxis(int s)
        {
            if(s == 0)
                y--;
            else if(s == 1)
                y++;
            return y;
        };*/
};

class enemy: public entity
{
    protected:
        bool alive;
    public:
        enemy(int h, int row, int col):entity(h, row, col)
        {
            alive = true;
        };
        void got_hit()
        {
            if(health > 0)
            {
                entity::got_hit();
                if(health == 0)
                    alive = false;
            }
        };
        bool is_alive()
        {
            return alive;
        };
};

int main()
{
    bool game_over = false, esc = false, proj = false;
    projectile p = projectile(0, 0, '0');
    char user = '0';
    int row, col;
    auto t = chrono::steady_clock::now();
    initscr();
    getmaxyx(stdscr,row,col);
    timeout(0);

    hero me = hero(3, row/2, col/2);
    enemy bad = enemy(3, row/4, col/4);
    bool a = bad.is_alive();

    print_map(col, row, me.xaxis(-1), me.yaxis(-1), bad.xaxis(-1), bad.yaxis(-1), a);

    while(!(game_over || esc))
    {
        bool a = bad.is_alive();
        print_map(col, row, me.xaxis(-1), me.yaxis(-1), bad.xaxis(-1), bad.yaxis(-1), a);
        if(proj)
        {
            bool m = false;
            bool x = false;
            int del = 0;
            int old;
            int dead = 1;
            if(chrono::steady_clock::now() - t >= chrono::milliseconds(20))
            {
                t = chrono::steady_clock::now();
                switch (p.direc())
                {
                case 'k':
                    old = p.yaxis(1);
                    x = false;
                    break;
                case 'j':
                    old = p.xaxis(0);
                    x = true;
                    break;
                case 'i':
                    old = p.yaxis(0);
                    x = false;
                    break;
                case 'l':
                    old = p.xaxis(1);
                    x = true;
                    break;
                default:
                    break;
                }
            }
            if(p.xaxis(-1) <= 0 || p.xaxis(-1) >= col-1)
            {
                del = 1;
            }
            else if(p.yaxis(-1) <= 0 || p.yaxis(-1) >= row-1)
            {
                del = 2;
            }
            if(p.yaxis(-1) == bad.yaxis(-1) && p.xaxis(-1) == bad.xaxis(-1))
            {
                bad.got_hit();
                if(x)
                    del = 1;
                else
                    del = 2;
            }
            handle_proj(p.xaxis(-1), p.yaxis(-1), del, old);
            if(del != 0)
                proj = false;
        }
        user = getch();
        if(user == 'i' || user == 'j' || user == 'k' || user == 'l')
        {
            if(!proj)
            {
                //t = time(0);
                t = chrono::steady_clock::now();
                p = me.shoot(user);
                proj = true;
            }
        }
        else
        {
            switch(user)
            {
                case 'q':
                    esc = true;
                    break;
                case 'w':
                    if(me.yaxis(-1) > 1)
                        me.yaxis(0);
                    else
                        game_over = true;
                    break;
                case 'a':
                    if(me.xaxis(-1) > 1)
                        me.xaxis(0);
                    else
                        game_over = true;
                    break;
                case 's':
                    if(me.yaxis(-1) < (row-2))
                        me.yaxis(1);
                    else
                        game_over = true;
                    break;
                case 'd':
                    if(me.xaxis(-1) < (col-2))
                        me.xaxis(1);
                    else
                        game_over = true;
                    break;
                default:
                    break;
            }
            if(me.xaxis(-1) == bad.xaxis(-1) && me.yaxis(-1) == bad.yaxis(-1))
                game_over = true;
        }
    }

    move(row/2, col/2);
    if(game_over)
        printw("GAME OVER!");
    else
        printw("GAME TERMINATED!");
    timeout(-1);
    refresh();
    t = chrono::steady_clock::now();
    while(chrono::steady_clock::now() - t < chrono::milliseconds(1000))
    {}
    getch();

    endwin();
    return 0;
}