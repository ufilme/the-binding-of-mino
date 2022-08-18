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
    mvwprintw(win, 0, max_w/2.55 - length/2, title);
}