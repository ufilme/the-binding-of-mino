#include "Window.hpp"

Window::Window(){
    initscr();
    noecho();
    curs_set(0);

    int max_h, max_w;
    getmaxyx(stdscr, max_h, max_w);

    win = newwin(max_h/1.5, max_w/1.5, max_h/6, max_w/6);
    box(win, 0, 0);

    char title[] = "> The Binding of Mino <";
    int length = sizeof(title) - 1;  // Discount the terminal '\0'
    mvwprintw(win, 0, max_w/3 - length/2, title);
}

void Window::resize(){
    int max_h, max_w;
    getmaxyx(stdscr, max_h, max_w);
    wclear(win);
    wrefresh(win);
    wresize(win, max_h/1.5, max_w/1.5);
    mvwin(win, max_h/6, max_w/6);
    box(win, 0, 0);
    char title[] = "> The Binding of Mino <";
    int length = sizeof(title) - 1;  // Discount the terminal '\0'
    mvwprintw(win, 0, max_w/3 - length/2, title);
}