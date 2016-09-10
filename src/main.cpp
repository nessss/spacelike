#include <stdlib.h>
#include <curses.h>
#include <signal.h>

#include "main.h"
#include "player.h"

int main(int argc, char *argv[]){
    int num = 0;

    Player player;

    signal(SIGINT, finish);  /* arrange interrupts to terminate */

    initscr();               /* initialize curses library */
    keypad(stdscr, TRUE);           /* enable keyboard mapping */
    nonl();                  /* tell curses not to do NL->CR/NL on output */
    cbreak();                /* take input chars one at a time, no wait for \n */
    noecho();                /* do not echo input */
    curs_set(0);             /* invisible cursor */

    if(has_colors()){
        start_color();

        /*
         * Simple color assignment, often all we need. Color pair 0 cannot
         * be redefined. This example uses the same value for the color
         * pair as for the foreground color, though of course that is not
         * necessary:
         */
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    }

    move(player.y(), player.x());
    addch(player.repr());
    move(player.y(), player.x());

    for(;;){
        int c = getch();

        mvaddch(player.y(), player.x(), ' ');
        player.process_input(c);
        player.refresh();
    }

    finish(0);
}

static void finish(int sig){
    endwin();

    /* do your non-curses wrapup here */

    exit(0);
}
