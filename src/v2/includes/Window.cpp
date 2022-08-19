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

    this->set_max_w(max_w);
    this->set_max_h(max_h);

    this->draw();
}

int Window::set_max_w(int w){
    max_w = w;
    return max_w;
}

int Window::set_max_h(int h){
    max_h = h;
    return max_h;
}

void Window::draw(){
    win = newwin(max_h/1.25, max_w/1.25, max_h/10, max_w/10);
    box(win, 0, 0);

    char title[] = "> The Binding of Mino <";
    int length = sizeof(title) - 1;  // Discount the terminal '\0'
    mvwprintw(win, 0, max_w/2.50 - length/2, title);
}

void Window::_delete(){
    delwin(win);
}

void MenuWindow::draw(int pos){
    Window::draw();

    //switch pos
    //highlights text

    char choice1[] = "Gioca";
    int length1 = sizeof(choice1) - 1;

    char choice2[] = "Comandi";
    int length2 = sizeof(choice2) - 1;

    char choice3[] = "Esci";
    int length3 = sizeof(choice3) - 1;

    int x = max_w/2.50, y = (max_h/5.00);

    mvwprintw(win, y, x - length1/2, choice1);
    mvwprintw(win, 2*y, x - length2/2, choice2);
    mvwprintw(win, 3*y, x - length3/2, choice3);

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