#include "includes/GameManager.hpp"

int main(){
    GameManager TBOM = GameManager();
    TBOM.start();

    // deallocates memory and ends ncurses
    endwin();
    
    return(0);
}