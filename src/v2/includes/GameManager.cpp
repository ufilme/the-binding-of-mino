#include "GameManager.hpp"
#include <locale.h>

GameManager::GameManager(){
    setlocale(LC_ALL, "");
};

/**
 * On game start check if terminal window has a valid size
 */
void GameManager::start(){
    Window TEST = Window();

    if (checkTerminalSize(TEST)){
        this->intro();
    } else {
        wtimeout(TEST.win, -1);
        wgetch(TEST.win);
        endwin();
    }
}

/**
 * Show logo animation
 */
void GameManager::intro(){
    IntroWindow WIN = IntroWindow();

    WIN.draw();
    wtimeout(WIN.win, -1);
    wgetch(WIN.win);
    WIN._delete();

    this->menu();
};

/**
 * @brief Handles menu interactions
 * The menu is resizable, avoiding restarting the game if the initial terminal
 * size is too small. So terminal size is checked and a dialog is displayed if
 * it's not valid.
 */
void GameManager::menu(){
    int pos = 0;
    bool exit = false;
    bool tooSmall = false;

    MenuWindow MENU = MenuWindow();
    while ((this->input != 127 && this->input != KEY_BACKSPACE) && !exit){
        if (this->input == KEY_RESIZE){
            tooSmall = false;
            MENU.resize();
            tooSmall = !checkTerminalSize(MENU);
        } else {
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
                            this->update();
                            break;
                        case 1:
                            this->commands(MENU);
                            tooSmall = false;
                            MENU.resize();
                            tooSmall = !checkTerminalSize(MENU);
                            break;
                        case 2:
                            exit = true;
                            break;
                    }
                    break;
            }
        }
        if (!tooSmall){
            MENU.draw(pos);
            mvwprintw(MENU.win, 0, 0, "%d %d", pos, this->input);
        }
        if (!exit)
            this->input = wgetch(MENU.win);
    }
    // deallocates memory and ends ncurses
    endwin();
}

/**
 * Handles commands description in the menu
 * 
 * @param MENU the menu window
 */
void GameManager::commands(MenuWindow MENU){
    int pos = 0;
    bool back = false;
    bool tooSmall = false;
    
    this->input = 0;
    while ((this->input != 127 && this->input != KEY_BACKSPACE) && !back){
        if (this->input == KEY_RESIZE){
            MENU.resize();
            tooSmall = !checkTerminalSize(MENU);
        }
        if (this->input == 10)
            back = true; //se viene usata la voce "Indietro"
        if (!tooSmall){
            MENU.cmd_draw(pos);     //stampa il menu dei comandi
        }
        if (!back)
            this->input = wgetch(MENU.win);
    }
}

/**
 * Initialize game window
 */
void GameManager::pre_update(){
    
};

/**
 * @brief Main GameManager function. Handles Player's movements, room's change
 * and Entities' delays
 */
void GameManager::update(){
    Player P;
    GameWindow GAME;
    Room *room;
    int max_y, max_x;
    system_clock::duration en_start_t = system_clock::now().time_since_epoch();   //to move enemies
    system_clock::duration b_start_t = en_start_t;
    system_clock::duration last_fired = en_start_t;                               //last bullet shot by P
    system_clock::duration en_move_t =  chrono::milliseconds(250);                //enemies moving time
    system_clock::duration b_move_t = chrono::milliseconds(100);                  // bullets moving time
    system_clock::duration reload_time = chrono::milliseconds(500);               //player reload time
    bool roomchanged = 0;

    GAME = GameWindow();
    getmaxyx(GAME.win, max_y, max_x);
    room = new Room(max_x, max_y);
    P = room->get_player();

    wtimeout(GAME.win, 0);                                      //non blocking input
    GAME.draw(room);

    while (this->input != 127 && this->input != KEY_BACKSPACE){
        P = room->get_player();
        en_start_t = this->timed_moving(en_start_t, en_move_t, room, &Room::random_move_enemies);
        b_start_t = this->timed_moving(b_start_t, b_move_t, room, &Room::move_bullets);
        last_fired = this->timed_moving(last_fired, reload_time, &P, &Player::set_reloading, false);
        //needed in case a bullet hit the player decreasing his health
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
                if (!P.get_reloading()){
                    room->add_bullet(x, y, P.get_dir());
                    P.set_reloading(true);
                }
                // last_fired = this->timed_moving(last_fired, reload_time, room, &Room::add_bullet, x, y, P.get_dir());
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
        GAME.draw(room);
        this->input = wgetch(GAME.win);
        if (P.get_health() <= 0){
            GAME._delete();
            this->game_over();
            break;
        }
    }
}

/**
 * Handles end screen
 */
void GameManager::game_over(){
    GameOverWindow WIN = GameOverWindow();
    WIN.draw();

    auto start_t = system_clock::now().time_since_epoch();
    auto wait_t =  chrono::milliseconds(1000);
    while(system_clock::now().time_since_epoch() - start_t < wait_t){
        wtimeout(WIN.win, 0);
        wgetch(WIN.win);
    }

    wtimeout(WIN.win, -1);
    wgetch(WIN.win);
    WIN._delete();
}

/**
 * @brief Check if terminal window has a valid size
 * Draws a dialog if too small
 * 
 * @param WIN window where to check the size
 * @return true if valid size
 * @return false if not valid size
 */
bool GameManager::checkTerminalSize(Window WIN){
    if (WIN.get_max_w() < 110 || WIN.get_max_h() < 45){
        WIN.screenTooSmall(WIN.get_max_w(), WIN.get_max_h());
        return false;
    }
    return true;
}

/**
 * Handles the movement of enemies and bullets
 * 
 * @param start_t initial time
 * @param delay_t time to wait
 * @param room object's pointer which calls the function
 * @param func method's address of the object
 * @return system_clock::now().time_since_epoch() if function is called
 * @return system_clock::duration if function is not called
 */
system_clock::duration GameManager::timed_moving(system_clock::duration start_t, system_clock::duration delay_t,
    Room *room, void (Room::*func)()){
        if (system_clock::now().time_since_epoch() - start_t > delay_t){
            (room->*func)();
            return system_clock::now().time_since_epoch();
        }
        return start_t;
}

/**
 * Handles Player reload time
 * 
 * @param start_t initial time
 * @param delay_t time to wait
 * @param P object's pointer which calls the function
 * @param func method's address of the object
 * @param f true or false based on what to set
 * @return system_clock::now().time_since_epoch() if function is called
 * @return system_clock::duration if function is not called
 */
system_clock::duration GameManager::timed_moving(system_clock::duration start_t, system_clock::duration delay_t,
    Player *P, void (Player::*func)(bool), bool f){
        if (system_clock::now().time_since_epoch() - start_t > delay_t){
            (P->*func)(f);
            return system_clock::now().time_since_epoch();
        }
        return start_t;
}