#include "GameManager.hpp"

using namespace std;

GameManager::GameManager(bool active){
    this->active = active;
};

void GameManager::start(Window MENU){
    MENU._delete();
    GameWindow GAME = GameWindow();
    this->update(GAME);
};

void GameManager::intro(){
    MenuWindow MENU = MenuWindow();
    keypad(MENU.win, true);
    bool exit = false;
    int pos = -1;
    while (this->input_ch != 127 && !exit){
        if (this->input_ch == KEY_RESIZE){
            MENU.resize();
        }
        switch (this->input_ch){
            case 65:
                if (pos == -1){
                    pos = 0;
                }
                else if (pos != 0){
                    pos--;
                }
                break;
            case 66:
                if (pos == -1){
                    pos = 0;
                }
                else if (pos != 2){
                    pos++;
                }
                break;
            case 10:
                switch (pos){
                    case 0:
                        this->input_ch = 0;
                        this->start(MENU);
                        break;
                    case 1:
                        //mostra i comandi
                        this->commands(MENU);
                        MENU.resize();
                        break;
                    case 2:
                        exit = true;
                        break;
                }
                break;
        }
        // sovrascrivi metodo draw nel menuWindow e poi fai disegnare qua
        MENU.draw(pos);
        mvwprintw(MENU.win, 0, 0, "%d %d", pos, this->input_ch);
        if (!exit)
            this->input_ch = wgetch(MENU.win);
    }
}

void GameManager::commands(MenuWindow MENU){
    bool back = false;
    int pos = -1;
    while (this->input_ch != 127 && !back){
        if (this->input_ch == KEY_RESIZE){
            MENU.resize();
        }
        switch (this->input_ch){
            case 65:
                pos = 0;
                break;
            case 66:
                pos = 0;
                break;
            case 10:
                //se viene usata la voce "Indietro"
                if (pos == 0){
                    back = true;
                }
                break;
        }
        
        MENU.cmd_draw(pos);     //stampa il menu dei comandi
        mvwprintw(MENU.win, 0, 0, "%d %d", pos, this->input_ch);
        if (!back)
            this->input_ch = wgetch(MENU.win);
    }
    werase(MENU.win);
    wrefresh(MENU.win);
}

void GameManager::update(Window GAME){
    while (this->input_ch != 127){
        GAME.draw();
        this->input_ch = wgetch(GAME.win);
    }
}