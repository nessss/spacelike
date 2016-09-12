#include "application.h"
#include "ncurses.h"

void Application::finish(int sig){
    endwin();

    /* do your non-curses wrapup here */

    exit(0);
}
