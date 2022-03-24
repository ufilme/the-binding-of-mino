#include "class.h"


projectile::projectile(int px, int py, char d)
{
    x = px;
    y = py;
    dir = d;
};
int projectile::xaxis(int s)
{
    if(s == 0)
        x--;
    else if(s == 1)
        x++;
    return x;
};
int projectile::yaxis(int s)
{
    if(s == 0)
        y--;
    else if(s == 1)
        y++;
    return y;
};
int projectile::direc()
{
    return dir;
};


entity::entity(int h, int row, int col)
{
    health = h;
    x = col;
    y = row;
};
bool entity::got_hit()
{
    health--;
    return health;
};
int entity::life()
{
    return health;
};
int entity::xaxis(int s)
{
    if(s == 0)
        x--;
    else if(s == 1)
        x++;
    return x;
};
int entity::yaxis(int s)
{
    if(s == 0)
        y--;
    else if(s == 1)
        y++;
    return y;
};
