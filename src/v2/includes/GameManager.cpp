#include "GameManager.hpp"

using namespace std;

GameManager::GameManager(bool active){
};

void GameManager::intro(){
    MenuWindow MENU = MenuWindow();
    bool exit = false;
    int pos = 0;
    while ((this->input_ch != 127 && this->input_ch != KEY_BACKSPACE) && !exit){
        if (this->input_ch == KEY_RESIZE){
            MENU.resize();
        }
        switch (this->input_ch){
            case KEY_UP:
            case 65:
                if (pos == -1){
                    pos = 0;
                }
                else if (pos != 0){
                    pos--;
                }
                break;
            case KEY_DOWN:
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
                        MENU.resize();
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

void GameManager::start(MenuWindow MENU){
    GameWindow GAME = GameWindow(MENU);
    int max_y, max_x;
    getmaxyx(GAME.win, max_y, max_x);
    room = new Room(max_x, max_y);
    this->update(GAME, room);
};

void GameManager::commands(MenuWindow MENU){
    bool back = false;
    int pos = 0;
    this->input_ch = 0;
    while ((this->input_ch != 127 && this->input_ch != KEY_BACKSPACE) && !back){
        if (this->input_ch == KEY_RESIZE){
            MENU.resize();
        }
       if (this->input_ch == 10){
            //se viene usata la voce "Indietro"
            back = true;
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

void GameManager::update(GameWindow GAME, Room *room){
    GAME.draw(room);
    Player *P = room->get_player();
    int max_y, max_x;
    bool roomchanged = 0;
    while (this->input_ch != 127 && this->input_ch != KEY_BACKSPACE){
        roomchanged = 0;
        auto [x, y] = P->get_pos();
        getmaxyx(GAME.win, max_y, max_x);
        switch (this->input_ch){
            case KEY_UP:
            case 65:
                if (y > 1){
                    if(!room->is_something_in_the_way(x, y-1))
                        y--;
                }
                else if (x >= max_x/2 - 2 && x <= max_x/2 + 1){
                    if (room->get_top() == NULL)
                        room = room->new_room(new Room(max_x, max_y), 0);
                    else
                        room = room->get_top();
                    P->set_pos(x, max_y - 2);
                    roomchanged = 1;
                }
                break;
            case KEY_RIGHT:
            case 67:
                if (x < max_x - 3){
                    if(!room->is_something_in_the_way(x+1, y) && !room->is_something_in_the_way(x+2, y))    
                        x += 2;
                }
                else if (y == max_y/2 - 1 || y == max_y/2){
                    if (room->get_right() == NULL)
                        room = room->new_room(new Room(max_x, max_y), 1);
                    else
                        room = room->get_right();
                    P->set_pos(1, y);
                    roomchanged = 1;
                }
                break;
            case KEY_DOWN:
            case 66:
                if (y < max_y - 2){
                    if(!room->is_something_in_the_way(x, y+1))
                        y++;
                }
                else if (x >= max_x/2 - 2 && x <= max_x/2 + 1){
                    if (room->get_bottom() == NULL)
                        room = room->new_room(new Room(max_x, max_y), 2);
                    else
                        room = room->get_bottom();
                    P->set_pos(x, 1);
                    roomchanged = 1;
                }
                break;
            case KEY_LEFT:
            case 68:
                if (x > 2){
                    if(!room->is_something_in_the_way(x-1, y) && !room->is_something_in_the_way(x-2, y))    
                        x -= 2;
                }
                else if (y == max_y/2 - 1 || y == max_y/2){
                    if (room->get_left() == NULL)
                        room = room->new_room(new Room(max_x, max_y), 3);
                    else
                        room = room->get_left();
                    P->set_pos(max_x - 2, y);
                    roomchanged = 1;
                }
                break;
        }
        if (!roomchanged)
            P->set_pos(x, y);
        room->set_player(P);
        werase(GAME.win);
        GAME.draw(room);
        mvwprintw(GAME.win, 0, GAME.get_max_w()/1.25 - 3, "%d", this->input_ch);
        wrefresh(GAME.win);
        this->input_ch = wgetch(GAME.win);
    }
    werase(GAME.win);
    wrefresh(GAME.win);
}