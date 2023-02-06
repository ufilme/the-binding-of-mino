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

DynamicArray<Bullet> Room::get_bullets(){
    return bullets;
}

/*
DynamicArray<Artifact> Room::get_artifacts(){
    return artifacts;
}
*/

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
    //newroom->random_generate_artifacts();
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

/*
void Room::random_generate_artifacts(){
    int x, y;
    srand(time(NULL));
    int n = rand() % 2;     //number of artifacts
    for (int i = 0; i < n; i++){
        //artifact's coordinates
        x = rand() % (N-2) + 1;
        y = rand() % (M-2) + 1;
        bool done = true;
        do  //position artifact on a free cell (no walls, artifacts...)
        {
            if(!is_something_in_the_way(x, y)){
                done = true;
                artifacts.push(Artifact(x, y));
            }
            else{
                done = false;
                x = rand() % (N-2) + 1;
                y = rand() % (M-2) + 1;
            }
        } while (!done);
    }
};
*/

std::tuple<int, int, int> Room::random_generate_bullets(int x, int y, DynamicArray<int> excluded_dir){
    int dir = rand() % 4;
    for (int el : excluded_dir){
        if (dir == el){
            return random_generate_bullets(x, y, excluded_dir);
        }
    }
    switch (dir){
        case 0: //up
                if (y > 1){
                    if(!is_something_in_the_way(x, y-1)){
                        y--;
                    } else {
                        excluded_dir.push(dir);
                        return random_generate_bullets(x, y, excluded_dir);
                    }
                }
            break;
        case 1: //down
            if (y < M - 2){
                if(!is_something_in_the_way(x, y+1)){
                    y++;
                } else {
                    excluded_dir.push(dir);
                    return random_generate_bullets(x, y, excluded_dir);
                }
            }
            break;
        case 2: //right
            if (x < N - 3){
                if(!is_something_in_the_way(x+1, y) && !is_something_in_the_way(x+2, y)){
                    x += 2;
                } else {
                    excluded_dir.push(dir);
                    return random_generate_bullets(x, y, excluded_dir);
                }
            }
            break;
        case 3: //left
            if (x > 2){
                if(!is_something_in_the_way(x-1, y) && !is_something_in_the_way(x-2, y)){
                    x -= 2;
                    break;
                } else {
                    excluded_dir.push(dir);
                    return random_generate_bullets(x, y, excluded_dir);
                }
            }
            break;
    }
    return {x, y, dir};
}

void Room::random_move_enemies(){
    DynamicArray<int> excluded_dir;
    srand(time(NULL));
    int dir;
    for (Enemy & enemy : enemies){
        auto[x, y] = enemy.get_pos();
        int action = rand() % 10;
        if (action < 3){  //30% probability of shooting
            std::tie(x, y, dir) = random_generate_bullets(x, y, excluded_dir);
            excluded_dir.reset();
            bullets.push(Bullet(x, y, dir));
        }
        else{           //70% probability of moving
            dir = rand() % 4;
            switch (dir){
                case 0: //up
                    if (y > 1){
                        if(!is_something_in_the_way(x, y-1)){
                            y--;
                        }
                    }
                    break;
                case 1: //down
                    if (y < M - 2){
                        if(!is_something_in_the_way(x, y+1)){
                            y++;
                        }
                    }
                    break;
                case 2: //right
                    if (x < N - 3){
                        if(!is_something_in_the_way(x+1, y) && !is_something_in_the_way(x+2, y)){
                            x += 2;
                        }
                    }
                    break;
                case 3: //left
                    if (x > 2){
                        if(!is_something_in_the_way(x-1, y) && !is_something_in_the_way(x-2, y)){
                            x -= 2;
                            break;
                        }
                    }
                    break;
            }
            enemy.set_pos(x, y);
        }
    }
};

void Room::move_bullets(){
    DynamicArray<Bullet> to_remove;
    DynamicArray<Enemy> dead_enemies;
    for (Bullet & b : bullets){
        auto [x,y] = b.get_pos();
        int back_x = x;
        int back_y = y;
        int dir = b.get_dir();
        switch (dir){
            case 0: //up
                if (y > 1){
                    if(!is_something_in_the_way(x, y-1)){
                        y--;
                    }
                }
                break;
            case 1: //down
                if (y < M - 2){
                    if(!is_something_in_the_way(x, y+1)){
                        y++;
                    }
                }
                break;
            case 2: //right
                if (x < N - 3){
                    if(!is_something_in_the_way(x+1, y) && !is_something_in_the_way(x+2, y)){
                        x += 2;
                    }
                }
                break;
            case 3: //left
                if (x > 2){
                    if(!is_something_in_the_way(x-1, y) && !is_something_in_the_way(x-2, y)){
                        x -= 2;
                        break;
                    }
                }
                break;
        }
        if (back_x != x || back_y != y){
            b.set_pos(x,y);
        } else {
            //if hit player decrease life
            int Px = P.get_x();
            int Py = P.get_y();
            switch (dir){
                case 0:     //up
                    if (Px == x && Py == y - 1)
                        P.dec_health();
                    break;
                case 1:     //down
                    if (Px == x && Py == y + 1)
                        P.dec_health();
                    break;
                case 2:     //right
                    if ((Px == x + 1 || Px == x + 2) && Py == y)
                        P.dec_health();
                    break;
                case 3:     //left
                    if ((Px == x - 1 || Px == x - 2) && Py == y)
                        P.dec_health();
                    break;
            }
            //if hit enemy decrease life
            for (Enemy & e : enemies){
                int Ex = e.get_x();
                int Ey = e.get_y();
                switch (dir){
                    case 0:     //up
                        if (Ex == x && Ey == y - 1)
                            e.dec_health();
                        break;
                    case 1:     //down
                        if (Ex == x && Ey == y + 1)
                            e.dec_health();
                        break;
                    case 2:     //right
                        if ((Ex == x + 1 || Ex == x + 2) && Ey == y)
                            e.dec_health();
                        break;
                    case 3:     //left
                        if ((Ex == x - 1 || Ex == x - 2) && Ey == y)
                            e.dec_health();
                        break;
                }
                if (e.get_health() <= 0)
                    dead_enemies.push(e);
            }
            to_remove.push(b);
        }
    }
    //remove bullets that hit something
    for (Bullet & b : to_remove){
        bullets.remove_element(b);
    }
    to_remove.reset();
    //remove enemies with 0 health
    for (Enemy & e : dead_enemies){
        enemies.remove_element(e);
    }
    dead_enemies.reset();
}

void Room::add_bullet(int x, int y, int dir){
    bullets.push(Bullet(x, y, dir));
};

void Room::melee_attack(int x, int y){
    DynamicArray<Enemy> dead_enemies;
    for (Enemy & e : enemies){
        int Ex = e.get_x();
        int Ey = e.get_y();

        int range = 2;
        int range_sx, range_dx, range_up, range_down;
        range_sx = x - 2*range;
        range_dx = x + 2*range;
        range_up = y - range;
        range_down = y + range;

        if ((Ex >= range_sx && Ex <= range_dx) && (Ey >= range_up && Ey <= range_down))
            e.dec_health();

        if (e.get_health() <= 0)
            dead_enemies.push(e);
    }

    //remove enemies with 0 health
    for (Enemy & e : dead_enemies){
        enemies.remove_element(e);
    }
    dead_enemies.reset();
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