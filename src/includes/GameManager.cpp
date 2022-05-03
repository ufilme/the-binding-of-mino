#include "GameManager.hpp"
#include <ncurses.h>
using namespace std;

struct mapList{
    Map map;
    struct mapList *up;
    struct mapList *down;
    struct mapList *left;
    struct mapList *right;
};

// mapList *HEAD;
// HEAD = new mapList;
// HEAD->map = 

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}



GameManager::GameManager(bool active){
    active = this->active;
};
void GameManager::intro(){
    //menu
};
void GameManager::start(){
    initscr();
    this->intro();
    Map map;
    //map.load();
    this->update(map);
};
void GameManager::update(Map map){
    // ncurses
    clear();
    noecho();
    cbreak();
    WINDOW *win;
    win =  create_newwin(100, 100, 50, 50);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    input_ch = getch();
    while(active){
        // input
        switch (input_ch)
        {
        case KEY_LEFT:
            exit(1);
            break;
        case KEY_RIGHT:
            exit(1);
            break;
        case KEY_UP:
            exit(1);
            break;
        case KEY_DOWN:
            exit(1);
            break;
        
        default:
            break;
        }
        this->update_screen(map);
    }
};
void GameManager::update_screen(Map map){
};

int main(){
    return 0;
}