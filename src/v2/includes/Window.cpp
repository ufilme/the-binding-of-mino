#include "Window.hpp"

Window::Window(){
    // sets up memory and clears the screen
    initscr();
    // avoid keyboard input to be written on screen
    noecho();
    refresh();
    curs_set(0);

    int max_h, max_w;
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
    box(win, 0, 0);

    char title[] = "> The Binding of Mino <";
    int length = sizeof(title) - 1; 
    mvwprintw(win, 0, max_w/2.50 - length/2, title);
}

void Window::_delete(){
    delwin(win);
}

GameWindow::GameWindow(MenuWindow MENU) : Window(){
    Window();       //chiama costruttore classe madre, poi reinizializza win
}

void GameWindow::draw(Room *room){
    box(win, 0, 0);
    Player P = room->get_player();
    auto [x,y] = P.get_pos();
    mvwprintw(win, 0, 0, "y:%d x:%d", y, x);
    mvwprintw(win, y, x, "@");

    auto [it, end] = room->playground_iter();
    for (it; it != end; it++){
        mvwprintw(win, it->get_y(), it->get_x(), it->get_icon());
    }

    //stampa le 4 porte
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);

    mvwprintw(win, max_y/2 - 1, 0, " ");            //porta sx
    mvwprintw(win, max_y/2, 0, " ");

    mvwprintw(win, max_y/2 - 1, max_x - 1, " ");    //porta dx
    mvwprintw(win, max_y/2, max_x - 1, " ");

    mvwprintw(win, 0, max_x/2 - 2, "    ");         //porta up

    mvwprintw(win, max_y - 1, max_x/2 - 2, "    "); //porta down
}

MenuWindow::MenuWindow() : Window(){};

void MenuWindow::draw(int pos){
    //chiama metodo draw della classe Window
    Window::draw();

    //voci del menu
    char choice1[] = "Gioca";
    int length1 = sizeof(choice1) - 1;

    char choice2[] = "Comandi";
    int length2 = sizeof(choice2) - 1;

    char choice3[] = "Esci";
    int length3 = sizeof(choice3) - 1;

    int x = max_w/2.50, y = (max_h/5.00);

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
}

void MenuWindow::cmd_draw(int pos){
    Window::draw();

    //voci del menu
    char info1[] = "Movimento = Frecce";
    int length1 = sizeof(info1) - 1;

    char info2[] = "Attacco di mischia = Z";
    int length2 = sizeof(info2) - 1;

    char info3[] = "Attacco a distanza = X";
    int length3 = sizeof(info3) - 1;

    char info4[] = "Esci = Backspace";
    int length4 = sizeof(info4) - 1;

    char back[] = "Indietro";
    int length_b = sizeof(back) - 1;

    int x = max_w/2.50, y = (max_h/7.50);

    //stampa a schermo le varie informazioni
    mvwprintw(win, y, x - length1/2, info1);
    mvwprintw(win, 2*y, x - length2/2, info2);
    mvwprintw(win, 3*y, x - length3/2, info3);
    mvwprintw(win, 4*y, x - length4/2, info4);
    mvwprintw(win, 5*y, x - length_b/2, back);

    //evidenzia "Indietro" se selezionato
    wattron(win, A_STANDOUT);
    if (pos == 0){
        mvwprintw(win, 5*y, x - length_b/2, back);
    }
    wattroff(win, A_STANDOUT);
}

void MenuWindow::resize(){
    int max_h, max_w;
    getmaxyx(stdscr, max_h, max_w);
    this->set_max_w(max_w);
    this->set_max_h(max_h);
    wclear(win);
    wrefresh(win);
    wresize(win, max_h/1.25, max_w/1.25);
    mvwin(win, max_h/10, max_w/10);
    box(win, 0, 0);
    char title[] = "> The Binding of Mino <";
    int length = sizeof(title) - 1;  // Discount the terminal '\0'
    mvwprintw(win, 0, max_w/2.50 - length/2, title);
}