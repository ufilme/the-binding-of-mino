#include "Room.hpp"
#include <cstring>
#include <cstdlib>
#include <ctime>

Room::Room(int N, int M){
    this->N = N;
    this->M = M;
    top = NULL, right = NULL, bottom = NULL, left = NULL;
}

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
}

void Room::set_right(Room *room){
    this->right = room;
}

void Room::set_bottom(Room *room){
    this->bottom = room;
}

void Room::set_left(Room *room){
    this->left = room;
}

std::tuple<vector<Object>::iterator, vector<Object>::iterator> Room::playground_iter(){
    return {this->playground.begin(), this->playground.end()};
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
    newroom->random_generate_walls();
    return newroom;
}

void Room::random_generate_walls(){
    int x, y, way, span;
    srand(time(NULL));
    int n = rand() % 10 + 2;
    for (int i = 0; i < n; i++){
        x = rand() % (N-2) + 1;
        y = rand() % (M-2) + 1;
        way = rand() % 3 + 1;   // 0 up 1 down 2 right 3 left
        switch (way){
            case 0:
            case 1:
                span = rand() % (M-4) + 3; break;
            case 2:
            case 3:
                span = rand() % (N-4) + 3; break;
        };
        for (int h = 0; h < span; h++){
            switch (way){
            case 0:
                if (y - h < 1) break;
                playground.push_back(Wall(x, y - h));
                break;
            case 1:
                if (y + h >= M - 1) break;
                playground.push_back(Wall(x, y + h));
                break;
            case 2:
                if (x + h >= N- 1) break;
                playground.push_back(Wall(x + h, y));
                break;
            case 3:
                if (x - h < 1) break;
                playground.push_back(Wall(x - h, y));
                break;
            }
        }   
    }
};

bool Room::is_object_in_cell(int x, int y){
    /*
        el : must be a reference because we cannot copy arrays.
        On each loop, el is set as a reference to playground[n], 
        with n equaling the current loop count starting from 0. 
        So, el is playground[0] on the first round, on the second it's playground[1], 
        and so on. It retrieves the value via iteration.
    */
    for (auto & el : playground){
        if (el.get_x() == x && el.get_y() == y) return true;
    }
    return false;
}