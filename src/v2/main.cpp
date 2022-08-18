#include "includes/GameManager.hpp"

int main(){
    GameManager TBOM = GameManager(true);

    TBOM.intro();

    // deallocates memory and ends ncurses
    endwin();
    
    return(0);
}