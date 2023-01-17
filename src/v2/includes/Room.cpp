#include "Room.hpp"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>

Room::Room(int N, int M){
    //N colonne, M righe
    this->N = N;
    this->M = M;
    P = Player(N/2, M/2);
    top = NULL, right = NULL, bottom = NULL, left = NULL;
};

int Room::get_max_x(){
    return this->N;
};

int Room::get_max_y(){
    return this->M;
};

Room *Room::get_top(){
    return this->top;
};

Room *Room::get_right(){
    return this->right;
};

Room *Room::get_bottom(){
    return this->bottom;
};

Room *Room::get_left(){
    return this->left;
};

void Room::set_top(Room *room){
    this->top = room;
};

void Room::set_right(Room *room){
    this->right = room;
};

void Room::set_bottom(Room *room){
    this->bottom = room;
};

void Room::set_left(Room *room){
    this->left = room;
};

DynamicArray<Entity> Room::get_playground(){
    return playground;
}

DynamicArray<Enemy> Room::get_enemies(){
    return enemies;
}

Room *Room::new_room(Room *newroom, int sidebaby){
    switch (sidebaby){   // 0 up 1 right 2 bottom 3 left
        case 0:
            this->set_top(newroom);
            newroom->set_bottom(this);
            break;
        case 1:
            this->set_right(newroom);
            newroom->set_left(this);
            break;
        case 2:
            this->set_bottom(newroom);
            newroom->set_top(this);
            break;
        case 3:
            this->set_left(newroom);
            newroom->set_right(this);
            break;
    }
    newroom->set_player(this->get_player());
    newroom->random_generate_walls();
    newroom->random_generate_enemies();
    return newroom;
}

void Room::random_generate_walls(){
    int x, y, way, span;
    srand(time(NULL));
    int n = rand() % 10 + 2;
    for (int i = 0; i < n; i++){
        x = rand() % (N-2) + 1;
        y = rand() % (M-2) + 1;
        way = rand() % 4;   // 0 up 1 down 2 right 3 left
        switch (way){
            case 0:
            case 1:
                span = rand() % (M-4) + 3; break;
            case 2:
            case 3:
                span = rand() % (N-4) + 3; break;
        }
        for (int h = 0; h < span; h++){
            switch (way){
            case 0:
                if (y - h < 1) break;
                playground.push(Wall(x, y - h));
                break;
            case 1:
                if (y + h >= M - 1) break;
                playground.push(Wall(x, y + h));
                break;
            case 2:
                if (x + h >= N- 1) break;
                playground.push(Wall(x + h, y));
                break;
            case 3:
                if (x - h < 1) break;
                playground.push(Wall(x - h, y));
                break;
            }
        }   
    }
};

void Room::random_generate_enemies(){
    int x, y;
    srand(time(NULL));
    int n = rand() % 4;     //number of enemies
    for (int i = 0; i < n; i++){
        //enemy's coordinates
        x = rand() % (N-2) + 1;
        y = rand() % (M-2) + 1;
        bool done = true;
        do  //position enemy on a free cell (no walls, artifacts...)
        {
            if(!is_something_in_the_way(x, y)){
                done = true;
                enemies.push(Enemy(x, y));
            }
            else{
                done = false;
                x = rand() % (N-2) + 1;
                y = rand() % (M-2) + 1;
            }
        } while (!done);
    }
};


void Room::random_move_enemies(){
    for (Enemy & enemy : enemies){
        auto[x, y] = enemy.get_pos();
        srand(time(NULL));
        int action = rand() % 10;
        if (action < 3){  //30% probability of shooting
            //shoot code
        }
        else{           //70% probability of moving
            int dir = rand() % 4;
            switch (dir){
                case 0: //up
                    if (y > 1){
                        if(!is_something_in_the_way(x, y-1)){
                            y--;
                        }
                    }
                case 1: //down
                    if (y < M - 2){
                        if(!is_something_in_the_way(x, y+1)){
                            y++;
                        }
                    }
                case 2: //right
                    if (x < N - 3){
                        if(!is_something_in_the_way(x+1, y) && !is_something_in_the_way(x+2, y)){
                            x += 2;
                        }
                    }
                case 3: //left
                    if (x > 2){
                        if(!is_something_in_the_way(x-1, y) && !is_something_in_the_way(x-2, y)){
                            x -= 2;
                            break;
                        }
                    }
            }
            enemy.set_pos(x, y);
        }
    }
};

bool Room::is_something_in_the_way(int x, int y){
    /*
        for (auto &el : array){
        // el is a reference to an item of array
        // We can change array's items by changing el
        }
        for (auto el : array){
        // Value of el is copied from an item of array
        // We can not change array's items by changing el
        }
        On each loop, el is set as a reference to playground[n], 
        with n equaling the current loop count starting from 0. 
        So, el is playground[0] on the first round, on the second it's playground[1], 
        and so on. It retrieves the value via iteration.
    */
    for (Entity & el : playground){
        if (el.get_x() == x && el.get_y() == y) return true;
    }
    for (Enemy & el : enemies){
        if (el.get_x() == x && el.get_y() == y) return true;
    }
    auto[Px, Py] = P.get_pos();
    if (Px == x && Py == y)
        return true;

    return false;
}

bool Room::is_enemy_in_the_way(int x, int y){
    for (Enemy & el : enemies){
        if (el.get_x() == x && el.get_y() == y) return true;
    }
    return false;
}

Player Room::get_player(){
    return P;
}

void Room::set_player(Player P){
    this->P = P;
}