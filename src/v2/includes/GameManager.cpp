#include "GameManager.hpp"

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
    wtimeout(GAME.win, 0);                                      //non blocking input
    system_clock::duration en_start_t = system_clock::now().time_since_epoch();   //to move enemies
    system_clock::duration b_start_t = en_start_t;
    system_clock::duration last_fired = en_start_t;                               //last bullet shot by P
    system_clock::duration en_move_t =  chrono::milliseconds(250);                //enemies moving time
    system_clock::duration b_move_t = chrono::milliseconds(100);                  // bullets moving time
    system_clock::duration reload_time = chrono::milliseconds(500);               //player reload time
    GAME.draw(room);
    Player P = room->get_player();
    int max_y, max_x;
    bool roomchanged = 0;
    while (this->input != 127 && this->input != KEY_BACKSPACE){
        en_start_t = this->timed_moving(en_start_t, en_move_t, room, &Room::random_move_enemies);
        b_start_t = this->timed_moving(b_start_t, b_move_t, room, &Room::move_bullets);
        //needed in case a bullet hit the player decreasing his health
        P = room->get_player();
        roomchanged = 0;
        auto [x, y] = P.get_pos();
        getmaxyx(GAME.win, max_y, max_x);
        switch (this->input){
            case KEY_UP:
            case 65:
                P.set_dir(0);
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
                P.set_dir(2);
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
                P.set_dir(1);
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
                P.set_dir(3);
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
            case 120:       //120 = x = shoot
                /*
                if(system_clock::now().time_since_epoch() - last_fired >= reload_time)
                    room->add_bullet(x, y, P.get_dir());
                */
                last_fired = this->timed_moving(last_fired, reload_time, room, &Room::add_bullet, x, y, P.get_dir());
                break;

            case 122:       //122 = z = melee attack
                room->melee_attack(x, y);
                break;
            case 99:        //99 = c = use explosive
                if (P.dec_explosive())
                    room->use_explosive(x, y);
                break;
        }
        if (!roomchanged){
            P.set_pos(x, y);
        }
        auto[a_in_the_way, type, value] = room->is_artifact_in_the_way(x, y);
        if (a_in_the_way){
            if (type == 0){
                if (P.get_health() <= 10 - value){
                    P.inc_health(value);
                }
            }
            else if (type == 1){
                P.inc_explosive(value);
            }
            
        }
        room->set_player(P);
        werase(GAME.win);
        GAME.draw(room);
        mvwprintw(GAME.win, 0, GAME.get_max_w()/1.25 - 3, "%d", this->input);
        wrefresh(GAME.win);
        this->input = wgetch(GAME.win);
        if (P.get_health() <= 0){
            GameOverWindow WIN = GameOverWindow();
            this->game_over(WIN);
            break;
        }
    }
    werase(GAME.win);
    wrefresh(GAME.win);
}

void GameManager::game_over(GameOverWindow WIN){
    WIN.draw();
    wtimeout(WIN.win, -1);

    /*
    auto start_t = system_clock::now().time_since_epoch();
    auto wait_t =  chrono::milliseconds(1000);
    while(system_clock::now().time_since_epoch() - start_t < wait_t){}
    */

    wgetch(WIN.win);
}

system_clock::duration GameManager::timed_moving(system_clock::duration start_t, system_clock::duration delay_t,
    Room *room, void (Room::*func)()){
        if (system_clock::now().time_since_epoch() - start_t > delay_t){
            (room->*func)();
            return system_clock::now().time_since_epoch();
        }
        return start_t;
}

system_clock::duration GameManager::timed_moving(system_clock::duration start_t, system_clock::duration delay_t,
    Room *room, void (Room::*func)(int, int, int), int x, int y, int dir){
        if (system_clock::now().time_since_epoch() - start_t > delay_t){
            (room->*func)(x, y, dir);
            return system_clock::now().time_since_epoch();
        }
        return start_t;
}