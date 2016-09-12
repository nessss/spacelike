#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <assert.h>
#include <list>
#include <iostream>

#include "main.h"
#include "input.h"
#include "output.h"
#include "player.h"
#include "floor_tile.h"

int main(int argc, char *argv[]){

    int rows = 20;
    int cols = 40;

    Player player;
    Input input;
    Output output(cols, rows);
    std::list<FloorTile> floorTiles;

    for(int x = 0; x < cols; x++){
        for(int y = 0; y < rows; y++){
            floorTiles.emplace_front(x, y);
            output.addElement(&(floorTiles.front()));
        }
    }

    input.setFocusedActor(&player);
    output.addElement(&player);

    signal(SIGINT, finish);  /* arrange interrupts to terminate */

    initscr();               /* initialize curses library */
    keypad(stdscr, TRUE);           /* enable keyboard mapping */
    nonl();                  /* tell curses not to do NL->CR/NL on output */
    cbreak();                /* take input chars one at a time, no wait for \n */
    noecho();                /* do not echo input */
    //curs_set(0);             /* invisible cursor */

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

    output.refresh();

    for(;;){
        int c = getch();
        input.processInput(c);

        output.refresh();
    }

    finish(0);
}

static void finish(int sig){
    endwin();

    /* do your non-curses wrapup here */

    exit(0);
}
