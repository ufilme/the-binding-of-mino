#include "includes/GameManager.hpp"

int main(int argc, char const *argv[]){
    GameManager TBOM = GameManager();

    TBOM.start();

    return 0;
}

/*

    GAMEMANAGER handles:
        Window (graphics engine):
            Intro:
                game logo animation
            Menu:
                Play/Commnads/Quit
            Game:
                draw all entities
            End:
                end screen
            (
                funcions:
                    draw -> args: Room obj
            )

        Gameplay:
            Room:
                Entities:
                    Players
                    Enemies
                    PowerUp
                    Walls
            (
                functions:
                    start:
                        initialize everything
                    intro/menu:
                        calls respective window
                    update:
                        calls game window
                        handles all interactions
                    close:
                        calls end window
                        reset everything
                        calls menu window

            )
    Base DataStructs:
        Concatenated List:
            Dynamic Array (simplifies search)
*/