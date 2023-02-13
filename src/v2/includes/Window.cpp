#include "Window.hpp"
#include <string>
#include <chrono>

using std::chrono::system_clock;

Window::Window(){
    int max_h, max_w;

    // sets up memory and clears the screen
    initscr();
    // avoid keyboard input to be written on screen
    noecho();
    refresh();
    curs_set(0);

    getmaxyx(stdscr, max_h, max_w);
    this->offset_h = (max_h - max_h/1.25)/2;
    this->offset_w = (max_w - max_w/1.25)/2;

    win = newwin(max_h/1.25, max_w/1.25, this->offset_h, this->offset_w);
    keypad(win, TRUE);

    this->set_max_w(max_w);
    this->set_max_h(max_h);
}

int Window::get_max_w(){
    return max_w;
}

int Window::get_max_h(){
    return max_h;
}

int Window::set_max_w(int w){
    max_w = w;
    return max_w;
}

int Window::set_max_h(int h){
    max_h = h;
    return max_h;
}

int Window::get_offset_w(){
    return offset_w;
}

int Window::get_offset_h(){
    return offset_h;
}

int Window::set_offset_w(int w){
    offset_w = w;
    return offset_w;
}

int Window::set_offset_h(int h){
    offset_h = h;
    return offset_h;
}

void Window::draw(){
    char title[] = "> The Binding of Mino <";
    int length = sizeof(title) - 1; 

    box(win, 0, 0);
    mvwprintw(win, 0, max_w/2.50 - length/2, title);
}

void Window::screenTooSmall(int max_w, int max_h){
    int x = max_w/2.50, y = (max_h/2.50);
    char gameover[] = "Terminal screen is too small!";
    int length = sizeof(gameover) - 1;

    //evidenzia quella attualmente selezionata
    wattron(win, A_STANDOUT);
    mvwprintw(win, y, x - length/2, gameover);
    wattroff(win, A_STANDOUT);
}

void Window::_delete(){
    delwin(win);
}

IntroWindow::IntroWindow(){
    Window();
};

void IntroWindow::draw(){
    system_clock::duration start_t;
    system_clock::duration wait_t = std::chrono::milliseconds(100);
    char footer[] = "Press any key to continue";
    int length = sizeof(footer) - 1;
    const char *logo[] = {
        "@@@@@@@  @@@  @@@  @@@@@@@@    @@@@@@@   @@@  @@@  @@@  @@@@@@@   @@@  @@@  @@@   @@@@@@@@",
        "@@@@@@@  @@@  @@@  @@@@@@@@    @@@@@@@@  @@@  @@@@ @@@  @@@@@@@@  @@@  @@@@ @@@  @@@@@@@@@",
        "  @@!    @@!  @@@  @@!         @@!  @@@  @@!  @@!@!@@@  @@!  @@@  @@!  @@!@!@@@  !@@      ",
        "  !@!    !@!  @!@  !@!         !@   @!@  !@!  !@!!@!@!  !@!  @!@  !@!  !@!!@!@!  !@!      ",
        "  @!!    @!@!@!@!  @!!!:!      @!@!@!@   !!@  @!@ !!@!  @!@  !@!  !!@  @!@ !!@!  !@! @!@!@",
        "  !!!    !!!@!!!!  !!!!!:      !!!@!!!!  !!!  !@!  !!!  !@!  !!!  !!!  !@!  !!!  !!! !!@!!",
        "  !!:    !!:  !!!  !!:         !!:  !!!  !!:  !!:  !!!  !!:  !!!  !!:  !!:  !!!  :!!   !!:",
        "  :!:    :!:  !:!  :!:         :!:  !:!  :!:  :!:  !:!  :!:  !:!  :!:  :!:  !:!  :!:   !::",
        "   ::    ::   :::   :: ::::     :: ::::   ::   ::   ::   :::: ::   ::   ::   ::   ::: ::::",
        "   :      :   : :  : :: ::     :: : ::   :    ::    :   :: :  :   :    ::    :    :: :: : ",
        "                                                                                          ",                        
        "                 @@@@@@   @@@@@@@@     @@@@@@@@@@   @@@  @@@  @@@   @@@@@@                ",
        "                @@@@@@@@  @@@@@@@@     @@@@@@@@@@@  @@@  @@@@ @@@  @@@@@@@@               ",
        "                @@!  @@@  @@!          @@! @@! @@!  @@!  @@!@!@@@  @@!  @@@               ",
        "                !@!  @!@  !@!          !@! !@! !@!  !@!  !@!!@!@!  !@!  @!@               ",
        "                @!@  !@!  @!!!:!       @!! !!@ @!@  !!@  @!@ !!@!  @!@  !@!               ",
        "                !@!  !!!  !!!!!:       !@!   ! !@!  !!!  !@!  !!!  !@!  !!!               ",
        "                !!:  !!!  !!:          !!:     !!:  !!:  !!:  !!!  !!:  !!!               ",
        "                :!:  !:!  :!:          :!:     :!:  :!:  :!:  !:!  :!:  !:!               ",
        "                ::::: ::   ::          :::     ::    ::   ::   ::  ::::: ::               ",
        "                 : :  :    :            :      :    :    ::    :    : :  :                "};
    int rows = sizeof(logo) / sizeof(logo[0]);

    Window::draw();
    getmaxyx(stdscr, max_h, max_w);
    this->set_max_w(max_w);
    this->set_max_h(max_h);
    for (int i = 0; i < rows; i++){
        mvwprintw(win, (max_h/2)-(19-i), (max_w/2.5)-45, "%s", logo[i]);
        start_t = system_clock::now().time_since_epoch();
        while(system_clock::now().time_since_epoch() - start_t < wait_t){
            wtimeout(win, 0);
            wgetch(win);
        }
    }
    mvwaddstr(win, (max_h/2.50)+10, (max_w/2.5)-length/2, footer);
}

GameWindow::GameWindow() : Window(){
    Window();       //chiama costruttore classe madre, poi reinizializza win
}

void GameWindow::draw(Room *room){
    int x, y, max_x, max_y;
    Player P = room->get_player();
    int p_health = P.get_health();
    int p_explosive = P.get_explosive();
    std::tie(x,y) = P.get_pos();

    werase(win);
    box(win, 0, 0);
    //mvwprintw(win, room->get_max_y()-1, 0, "y:%d x:%d", y, x);
    mvwprintw(win, 0, 1, " Health: %d, ", p_health);     //player's health
    wprintw(win, " Explosive: %d ", p_explosive);              //player's explosive
    mvwprintw(win, y, x, "@");                          //player's icon

    //print walls and enemies
    DynamicArray<Entity> playground = room->get_playground();
    for (Entity & obj : playground){
        mvwprintw(win, obj.get_y(), obj.get_x(), obj.get_icon());
    }
    DynamicArray<Enemy> enemies = room->get_enemies();
    for (Enemy & en : enemies){
        mvwprintw(win, en.get_y(), en.get_x(), en.get_icon());
    }
    DynamicArray<Bullet> bullets = room->get_bullets();
    for (Bullet & b : bullets){
        mvwprintw(win, b.get_y(), b.get_x(), b.get_icon());
    }
    DynamicArray<Artifact> artifacts = room->get_artifacts();
    for (Artifact & a : artifacts){
        mvwprintw(win, a.get_y(), a.get_x(), a.get_icon());
    }

    //stampa le 4 porte
    getmaxyx(win, max_y, max_x);

    mvwprintw(win, max_y/2 - 1, 0, " ");            //porta sx
    mvwprintw(win, max_y/2, 0, " ");

    mvwprintw(win, max_y/2 - 1, max_x - 1, " ");    //porta dx
    mvwprintw(win, max_y/2, max_x - 1, " ");

    mvwprintw(win, 0, max_x/2 - 2, "    ");         //porta up

    mvwprintw(win, max_y - 1, max_x/2 - 2, "    "); //porta down
    wrefresh(win);
}

MenuWindow::MenuWindow() : Window(){};

void MenuWindow::draw(int pos){
    int x = max_w/2.50, y = (max_h/5.00);
    //voci del menu
    char choice1[] = "Gioca";
    int length1 = sizeof(choice1) - 1;
    char choice2[] = "Comandi";
    int length2 = sizeof(choice2) - 1;
    char choice3[] = "Esci";
    int length3 = sizeof(choice3) - 1;

    werase(win);
    //chiama metodo draw della classe Window
    Window::draw();
    //stampa a schermo le varie opzioni
    mvwprintw(win, y, x - length1/2, choice1);
    mvwprintw(win, 2*y, x - length2/2, choice2);
    mvwprintw(win, 3*y, x - length3/2, choice3);

    //evidenzia quella attualmente selezionata
    wattron(win, A_STANDOUT);
    switch (pos){
        case 0:
            mvwprintw(win, y, x - length1/2, choice1);
            break;
        case 1:
            mvwprintw(win, 2*y, x - length2/2, choice2);
            break;
        case 2:
            mvwprintw(win, 3*y, x - length3/2, choice3);
            break;
    }
    wattroff(win, A_STANDOUT);
    wrefresh(win);
}

void MenuWindow::cmd_draw(int pos){
    int x = max_w/2.50, y = (max_h/8.75);
    //voci del menu
    char info1[] = "Movimento = Frecce";
    int length1 = sizeof(info1) - 1;
    char info2[] = "Attacco di mischia = z";
    int length2 = sizeof(info2) - 1;
    char info3[] = "Attacco a distanza = x";
    int length3 = sizeof(info3) - 1;
    char info4[] = "Piazza esplosivo = c";
    int length4 = sizeof(info4) - 1;
    char info5[] = "Esci = Backspace";
    int length5 = sizeof(info5) - 1;
    char back[] = "Indietro";
    int length_b = sizeof(back) - 1;
    
    werase(win);
    Window::draw();
    //stampa a schermo le varie informazioni
    mvwprintw(win, y, x - length1/2, info1);
    mvwprintw(win, 2*y, x - length2/2, info2);
    mvwprintw(win, 3*y, x - length3/2, info3);
    mvwprintw(win, 4*y, x - length4/2, info4);
    mvwprintw(win, 5*y, x - length5/2, info5);
    mvwprintw(win, 6*y, x - length_b/2, back);

    //evidenzia "Indietro" se selezionato
    wattron(win, A_STANDOUT);
    if (pos == 0){
        mvwprintw(win, 6*y, x - length_b/2, back);
    }
    wattroff(win, A_STANDOUT);
    wrefresh(win);
}

void MenuWindow::resize(){
    int max_h, max_w;
    char title[] = "> The Binding of Mino <";
    int length = sizeof(title) - 1;  // Discount the terminal '\0'

    getmaxyx(stdscr, max_h, max_w);
    this->set_max_w(max_w);
    this->set_max_h(max_h);
    wclear(win);
    wrefresh(win);
    wresize(win, max_h/1.25, max_w/1.25);
    mvwin(win, max_h/10, max_w/10);
    box(win, 0, 0);
    mvwprintw(win, 0, max_w/2.50 - length/2, title);
}

GameOverWindow::GameOverWindow() : Window(){};

void GameOverWindow::resize(){
    int max_h, max_w;
    char title[] = "> The Binding of Mino <";
    int length = sizeof(title) - 1;  // Discount the terminal '\0'

    getmaxyx(stdscr, max_h, max_w);
    this->set_max_w(max_w);
    this->set_max_h(max_h);
    wclear(win);
    wrefresh(win);
    wresize(win, max_h/1.25, max_w/1.25);
    mvwin(win, max_h/10, max_w/10);
    box(win, 0, 0);
    mvwprintw(win, 0, max_w/2.50 - length/2, title);
}

void GameOverWindow::draw(){
    int x = max_w/2.50, y = (max_h/2.50);
    //voci del menu
    char gameover[] = "Game over!";
    int length = sizeof(gameover) - 1;

    //chiama metodo draw della classe Window
    Window::draw();
    //evidenzia quella attualmente selezionata
    wattron(win, A_STANDOUT);
    mvwprintw(win, y, x - length/2, gameover);
    wattroff(win, A_STANDOUT);
}