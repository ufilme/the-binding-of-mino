#include "Entity.hpp"
#include "Map.hpp"
using namespace std;

struct mapList{
    Map map;
    struct mapList *next;
    struct mapList *prev;
};

class GameManager{
    protected:
        Player player;
    public:
        GameManager(){
            player = player(0,0);
        }
        void intro(){
            //menu
        }
        void start(){
            this->intro()
            Map map;
            map.load();
            this->update(map);
        };
        void update(Map map){
            // ncurses
            while(true){
                // input
                switch (expression)
                {
                case :
                    break;
                
                default:
                    break;
                }
                this->update_screen(map);
            }
        };
        void update_screen(){
        };
};