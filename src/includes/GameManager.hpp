#include "Entity.hpp"
#include "Map.hpp"
#include <ncurses.h>
using namespace std;

class GameManager{
    private:
        int input_ch;
    protected:
        //Player player;
        bool active;
    public:
        GameManager(bool active);
        void intro();
        void start();
        void update(Map map);
        void update_screen(Map map);
};