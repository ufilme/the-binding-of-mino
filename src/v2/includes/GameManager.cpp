#include "GameManager.hpp"

using namespace std;

GameManager::GameManager(bool active){
    this->active = active;
};

void GameManager::start(MenuWindow MENU){
    MENU._delete();
    GameWindow GAME = GameWindow();
    Player P = Player(GAME.get_max_w()/2.5, GAME.get_max_h()/2.5, '@');
    this->update(GAME, P);
};

void GameManager::intro(){
    MenuWindow MENU = MenuWindow();
    bool exit = false;
    int pos = 0;
    while (this->input_ch != 127 && !exit){
        if (this->input_ch == KEY_RESIZE){
            MENU.resize();
        }
        switch (this->input_ch){
            case KEY_UP:
                if (pos == -1){
                    pos = 0;
                }
                else if (pos != 0){
                    pos--;
                }
                break;
            case KEY_DOWN:
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
            case KEY_UP:
                pos = 0;
                break;
            case KEY_DOWN:
                pos = 0;
                break;
            case 10:
                //se viene usata la voce "Indietro"
                if (pos == 0){
                    back = true;
                }
                break;
        }
        werase(MENU.win);
        MENU.cmd_draw(pos);     //stampa il menu dei comandi
        mvwprintw(MENU.win, 0, 0, "%d %d", pos, this->input_ch);
        wrefresh(MENU.win);
        if (!back)
            this->input_ch = wgetch(MENU.win);
    }
    werase(MENU.win);
    wrefresh(MENU.win);
}

void GameManager::update(GameWindow GAME, Player P){
    while (this->input_ch != 127){
        auto [x, y] = P.get_pos();
        switch (this->input_ch){
            case KEY_UP:
                if (y > 1)
                    y--;
                break;
            case KEY_DOWN:
                if (y < GAME.get_max_h() / 1.35)
                    y++;
                break;
            case KEY_LEFT:
                if (x > 1)
                    x--;
                break;
            case KEY_RIGHT:
                if (x < GAME.get_max_w() / 1.35)
                    x++;
                break;
        }
        P.set_pos(x, y);
        werase(GAME.win);
        GAME.draw(P);
        mvwprintw(GAME.win, 0, GAME.get_max_w()/1.25 - 3, "%d", this->input_ch);
        wrefresh(GAME.win);
        this->input_ch = wgetch(GAME.win);
    }
}