#include "GameManager.hpp"

using namespace std;

GameManager::GameManager(bool active){
    this->active = active;
    room = new str_room;
    room->top = NULL;
    room->right = NULL;
    room->bottom = NULL;
    room->left = NULL;
    room->difficulty = 0;
    room->wall1.start = -1;
    srand(time(0));
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
        mvwprintw(MENU.win, 2, 0, "%d %d", room->wall1.end, room->wall1.start);
        if (!exit)
            this->input_ch = wgetch(MENU.win);
    }
}

void GameManager::start(MenuWindow MENU){
    GameWindow GAME = GameWindow(MENU);
    int max_y, max_x;
    getmaxyx(GAME.win, max_y, max_x);
    create_walls(max_y, max_x);
    Player P = Player(GAME.get_max_w()/2.5, GAME.get_max_h()/2.5, '@');
    this->update(GAME, P);
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

void GameManager::update(GameWindow GAME, Player P){
    //converte muri da struct di GameManager a struct di Window
    w w1 = convert_wall(room->wall1);
    w w2 = convert_wall(room->wall2);

    GAME.draw(P, w1, w2);
    while (this->input_ch != 127 && this->input_ch != KEY_BACKSPACE){
        auto [x, y] = P.get_pos();
        int max_y, max_x;
        getmaxyx(GAME.win, max_y, max_x);
        bool mv_room = false;
        switch (this->input_ch){
            case KEY_UP:
                if (y > 1)
                    y--;
                else if (x >= max_x/2 - 2 && x <= max_x/2 + 1){
                    //va alla stanza sopra
                    mv_room = true;
                    if (room->top == NULL)
                        new_room('t');
                    move_room('t', max_y, max_x);
                    P.set_pos(x, max_y - 2);
                }
                break;
            case KEY_DOWN:
                if (y < max_y - 2)
                    y++;
                else if (x >= max_x/2 - 2 && x <= max_x/2 + 1){
                    //va alla stanza sotto
                    mv_room = true;
                    if (room->bottom == NULL)
                        new_room('b');
                    move_room('b', max_y, max_x);
                    P.set_pos(x, 1);
                }
                break;
            case KEY_LEFT:
                if (x > 1)
                    x--;
                else if (y == max_y/2 - 1 || y == max_y/2){
                    //va alla stanza a sx
                    mv_room = true;
                    if (room->left == NULL)
                        new_room('l');
                    move_room('l', max_y, max_x);
                    P.set_pos(max_x - 2, y);
                }
                break;
            case KEY_RIGHT:
                if (x < max_x - 2)
                    x++;
                else if (y == max_y/2 - 1 || y == max_y/2){
                    //va alla stanza a dx
                    mv_room = true;
                    if (room->right == NULL)
                        new_room('r');
                    move_room('r', max_y, max_x);
                    P.set_pos(1, y);
                }
                break;
            case 65:
                if (y > 1)
                    y--;
                else if (x >= max_x/2 - 2 && x <= max_x/2 + 1){
                    //va alla stanza sopra
                    mv_room = true;
                    if (room->top == NULL)
                        new_room('t');
                    move_room('t', max_y, max_x);
                    P.set_pos(x, max_y - 2);
                }
                break;
            case 66:
                if (y < max_y - 2)
                    y++;
                else if (x >= max_x/2 - 2 && x <= max_x/2 + 1){
                    //va alla stanza sotto
                    mv_room = true;
                    if (room->bottom == NULL)
                        new_room('b');
                    move_room('b', max_y, max_x);
                    P.set_pos(x, 1);
                }
                break;
            case 68:
                if (x > 1)
                    x--;
                else if (y == max_y/2 - 1 || y == max_y/2){
                    //va alla stanza a sx
                    mv_room = true;
                    if (room->left == NULL)
                        new_room('l');
                    move_room('l', max_y, max_x);
                    P.set_pos(max_x - 2, y);
                }
                break;
            case 67:
                if (x < max_x - 2)
                    x++;
                else if (y == max_y/2 - 1 || y == max_y/2){
                    //va alla stanza a dx
                    mv_room = true;
                    if (room->right == NULL)
                        new_room('r');
                    move_room('r', max_y, max_x);
                    P.set_pos(1, y);
                }
                break;
        }
        //converte muri da struct di GameManager a struct di Window
        w1 = convert_wall(room->wall1);
        w2 = convert_wall(room->wall2);

        if (!mv_room)
            P.set_pos(x, y);
        werase(GAME.win);
        GAME.draw(P, w1, w2);
        mvwprintw(GAME.win, 0, GAME.get_max_w()/1.25 - 3, "%d", this->input_ch);
        wrefresh(GAME.win);
        this->input_ch = wgetch(GAME.win);
    }
    werase(GAME.win);
    wrefresh(GAME.win);
}

void GameManager::move_room(char direction, int max_y, int max_x){
    switch (direction){
        case 't':
            room = room->top;
            break;
        case 'r':
            room = room->right;
            break;
        case 'b':
            room = room->bottom;
            break;
        case 'l':
            room = room->left;
            break;
    }
    create_walls(max_y, max_x);
}

void GameManager::new_room(char direction){
    p_room n_room = new str_room;
    n_room->top = NULL;
    n_room->right = NULL;
    n_room->bottom = NULL;
    n_room->left = NULL;
    n_room->wall1.start = -1;
    n_room->difficulty = room->difficulty + 1;
    switch (direction){
        case 't':
            room->top = n_room;
            n_room->bottom = room;
            break;
        case 'r':
            room->right = n_room;
            n_room->left = room;
            break;
        case 'b':
            room->bottom = n_room;
            n_room->top = room;
            break;
        case 'l':
            room->left = n_room;
            n_room->right = room;
            break;
    }
}

void GameManager::create_walls(int max_h, int max_w){
    if (room->wall1.start == -1){
        int n_walls = rand()%3;

        gen_wall(max_h, max_w);
        gen_wall(max_h, max_w);
        /*
        switch (n_walls){
            case 0:
                room->wall1.start = -2;
                room->wall2.start = -2;
                break;
            case 1:
                gen_wall(max_h, max_w);
                room->wall2.start = -2;
                break;
            case 2:
                gen_wall(max_h, max_w);
                gen_wall(max_h, max_w);
                break;
        }
        */
    }
}

void GameManager::gen_wall(int max_h, int max_w){
    if (room->wall1.start == -1){
        room->wall1.horizontal = rand()%2;
        if (room->wall1.horizontal){
            room->wall1.start = rand()%(max_w-2)+1;
            room->wall1.end = rand()%(max_w-2)+1;
            room->wall1.axis = rand()%(max_h-4)+2;
        }
        else{
            room->wall1.start = rand()%(max_h-2)+1;
            room->wall1.end = rand()%(max_h-2)+1;
            room->wall1.axis = rand()%(max_w-4)+2;
        }
        if (room->wall1.start > room->wall1.end){
            int tmp = room->wall1.start;
            room->wall1.start = room->wall1.end;
            room->wall1.end = tmp;
        }
    }
    else{
        room->wall2.horizontal = rand()%2;
        if (room->wall2.horizontal){
            room->wall2.start = rand()%(max_w-2)+1;
            room->wall2.end = rand()%(max_w-2)+1;
            room->wall2.axis = rand()%(max_h-4)+2;
        }
        else{
            room->wall2.start = rand()%(max_h-2)+1;
            room->wall2.end = rand()%(max_h-2)+1;
            room->wall2.axis = rand()%(max_w-4)+2;
        }
        if (room->wall1.start > room->wall1.end){
            int tmp = room->wall1.start;
            room->wall1.start = room->wall1.end;
            room->wall1.end = tmp;
        }
    }
}

w GameManager::convert_wall(wall wa){
    w w1;
    w1.start = wa.start;
    w1.end = wa.end;
    w1.axis = wa.axis;
    w1.horizontal = wa.horizontal;
    return w1;
}