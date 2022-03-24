class projectile
{
    protected:
        int x, y;
        char dir;
    public:
        projectile(int px, int py, char d);
        int xaxis(int s);
        int yaxis(int s);
        int direc();
};

class entity
{
    protected:
        int health;
        int x;
        int y;

    public:
        entity(int h, int row, int col);
        bool got_hit();
        int life();
        int xaxis(int s);
        int yaxis(int s);
};