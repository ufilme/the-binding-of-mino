class Object{
    protected:
        int x,y;
    public:
        Object(int x, int y);
        int get_x();
        int get_y();
};

class Wall : public Object{
    public:
        Wall(int x, int y);
};