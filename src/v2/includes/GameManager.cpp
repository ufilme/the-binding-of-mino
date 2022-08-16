#include "GameManager.hpp"

using namespace std;

GameManager::GameManager(bool active){
    active = this->active;
};

void GameManager::start(){
    Window WIN = Window();
    this->update(WIN);
};

void GameManager::update(Window WIN){
    while (this->input_ch != 'x'){
        if (this->input_ch == KEY_RESIZE){
            WIN.resize();
        }
        this->input_ch = wgetch(WIN.win);
    }
    endwin();
}