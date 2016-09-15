#include "application.h"
#include "ncurses.h"

/**
 * Clean up curses and exit 0
 * @param[in] sig SIGINT
 */
void Application::finish(int sig){
    endwin();

    exit(0);
}
