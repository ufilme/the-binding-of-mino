#include "GameManager.hpp"

GameManager::GameManager(){};

void GameManager::start(){
    MenuWindow win = MenuWindow();
    bool exit = false;
    int pos = 0;
    while ((input != 127 && input != KEY_BACKSPACE) && !exit){
        if (input == KEY_RESIZE){
            win.resize();
        }
        switch (this->input){
            case KEY_UP:
            case 65:
                if (pos == -1)
                    pos = 0;
                else if (pos != 0)
                    pos--;
                break;
            case KEY_DOWN:
            case 66:
                if (pos == -1)
                    pos = 0;
                else if (pos != 2)
                    pos++;
                break;
            case 10:
                switch (pos){
                    case 0:
                        this->input = 0;
                        this->pre_update();
                        win.resize();
                        break;
                    case 1:
                        this->commands(win);
                        win.resize();
                        break;
                    case 2:
                        exit = true;
                        break;
                }
                break;
        }
        win.draw(pos);
        if (!exit)
            input = wgetch(win.win);
    }
}

void GameManager::commands(MenuWindow win){
    bool back = false;
    int pos = 0;
    this->input = 0;
    while ((this->input != 127 && this->input != KEY_BACKSPACE) && !back){
        if (this->input == KEY_RESIZE){
            win.resize();
        }
       if (this->input == 10){
            //se viene usata la voce "Indietro"
            back = true;
        }
        werase(win.win);
        win.commands_draw(pos);     //stampa il menu dei comandi
        mvwprintw(win.win, 0, 0, "%d %d", pos, this->input);
        wrefresh(win.win);
        if (!back)
            this->input = wgetch(win.win);
    }
    werase(win.win);
    wrefresh(win.win);
}

void GameManager::pre_update(){
    GameWindow GAME = GameWindow();
    int max_y, max_x;
    getmaxyx(GAME.win, max_y, max_x);
    room = new Room(max_x, max_y);
    this->update(GAME, room);
};

void GameManager::update(GameWindow win, Room *room){

}