#include "GameManager.hpp"
#include <chrono>

using namespace std;
using chrono::system_clock;

GameManager::GameManager(){};

void GameManager::intro(){};

void GameManager::start(){
    MenuWindow MENU = MenuWindow();
    bool exit = false;
    int pos = 0;
    while ((this->input != 127 && this->input != KEY_BACKSPACE) && !exit){
        if (this->input == KEY_RESIZE)
            MENU.resize();
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
                        this->pre_update(MENU);
                        MENU.resize();
                        break;
                    case 1:
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
        mvwprintw(MENU.win, 0, 0, "%d %d", pos, this->input);
        if (!exit)
            this->input = wgetch(MENU.win);
    }
}

void GameManager::pre_update(MenuWindow MENU){
    GameWindow GAME = GameWindow(MENU);
    int max_y, max_x;
    getmaxyx(GAME.win, max_y, max_x);
    room = new Room(max_x, max_y);
    this->update(GAME, room);
};

void GameManager::commands(MenuWindow MENU){
    bool back = false;
    int pos = 0;
    this->input = 0;
    while ((this->input != 127 && this->input != KEY_BACKSPACE) && !back){
        if (this->input == KEY_RESIZE)
            MENU.resize();
       if (this->input == 10)
            back = true; //se viene usata la voce "Indietro"
        werase(MENU.win);
        MENU.cmd_draw(pos);     //stampa il menu dei comandi
        mvwprintw(MENU.win, 0, 0, "%d %d", pos, this->input);
        wrefresh(MENU.win);
        if (!back)
            this->input = wgetch(MENU.win);
    }
    werase(MENU.win);
    wrefresh(MENU.win);
}

void GameManager::update(GameWindow GAME, Room *room){
    wtimeout(GAME.win, 0);                              //non blocking input
    auto start_time = system_clock::now().time_since_epoch();      //to move enemies
    auto en_move_t =  chrono::milliseconds(250);        //enemies moving time
    GAME.draw(room);
    Player P = room->get_player();
    int max_y, max_x;
    bool roomchanged = 0;
    while (this->input != 127 && this->input != KEY_BACKSPACE){
        if (system_clock::now().time_since_epoch() - start_time > en_move_t){
            room->random_move_enemies();                //move enemies
            GAME.draw(room);
            start_time = system_clock::now().time_since_epoch();   //resets start time
        }
        roomchanged = 0;
        auto [x, y] = P.get_pos();
        getmaxyx(GAME.win, max_y, max_x);
        switch (this->input){
            case KEY_UP:
            case 65:
                if (y > 1){
                    if(!room->is_something_in_the_way(x, y-1))
                        y--;                                        //move if cell is free
                    else if(room->is_enemy_in_the_way(x, y-1))
                        P.dec_health();                            //decrease life if bumped into enemy
                }
                else if (x >= max_x/2 - 2 && x <= max_x/2 + 1){
                    if (room->get_top() == NULL)
                        room = room->new_room(new Room(max_x, max_y), 0);
                    else
                        room = room->get_top();
                    P.set_pos(x, max_y - 2);
                    roomchanged = 1;
                }
                break;
            case KEY_RIGHT:
            case 67:
                if (x < max_x - 3){
                    if(!room->is_something_in_the_way(x+1, y) && !room->is_something_in_the_way(x+2, y))    
                        x += 2;                                     //move if cell is free
                    else if(room->is_enemy_in_the_way(x+1, y) || room->is_enemy_in_the_way(x+2, y))
                        P.dec_health();                            //decrease life if bumped into enemy
                }
                else if (y == max_y/2 - 1 || y == max_y/2){
                    if (room->get_right() == NULL)
                        room = room->new_room(new Room(max_x, max_y), 1);
                    else
                        room = room->get_right();
                    P.set_pos(1, y);
                    roomchanged = 1;
                }
                break;
            case KEY_DOWN:
            case 66:
                if (y < max_y - 2){
                    if(!room->is_something_in_the_way(x, y+1))
                        y++;                                        //move if cell is free
                    else if(room->is_enemy_in_the_way(x, y+1))
                        P.dec_health();                            //decrease life if bumped into enemy
                }
                else if (x >= max_x/2 - 2 && x <= max_x/2 + 1){
                    if (room->get_bottom() == NULL)
                        room = room->new_room(new Room(max_x, max_y), 2);
                    else
                        room = room->get_bottom();
                    P.set_pos(x, 1);
                    roomchanged = 1;
                }
                break;
            case KEY_LEFT:
            case 68:
                if (x > 2){
                    if(!room->is_something_in_the_way(x-1, y) && !room->is_something_in_the_way(x-2, y))    
                        x -= 2;                                     //move if cell is free
                    else if(room->is_enemy_in_the_way(x-1, y) || room->is_enemy_in_the_way(x-2, y))
                        P.dec_health();                            //decrease life if bumped into enemy
                }
                else if (y == max_y/2 - 1 || y == max_y/2){
                    if (room->get_left() == NULL)
                        room = room->new_room(new Room(max_x, max_y), 3);
                    else
                        room = room->get_left();
                    P.set_pos(max_x - 2, y);
                    roomchanged = 1;
                }
                break;
        }
        if (!roomchanged)
            P.set_pos(x, y);
        room->set_player(P);
        werase(GAME.win);
        GAME.draw(room);
        mvwprintw(GAME.win, 0, GAME.get_max_w()/1.25 - 3, "%d", this->input);
        wrefresh(GAME.win);
        this->input = wgetch(GAME.win);
    }
    werase(GAME.win);
    wrefresh(GAME.win);
}