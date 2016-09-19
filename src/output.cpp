#include "output.h"
#include "application.h"
#include <iostream>
#include <limits.h>
#include <cassert>

Output::Output(){
    /* init curses */
    signal(SIGINT, Application::finish);  /* arrange interrupts to terminate */

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

}

void Output::init(const OutputOptions& options){

    m_gameWindow = newwin(
            options.gameWindowH,
            options.gameWindowW,
            options.gameWindowY,
            options.gameWindowX);

    assert(m_gameWindow != NULL);

    m_inventory = newwin(
            options.gameWindowH,
            options.inventoryW,
            options.gameWindowY,
            options.gameWindowW + options.gameWindowX);

    assert(m_gameWindow != NULL);

    /* draw box for inventory */
    box(m_inventory, 0, 0);
    refresh();
    wrefresh(m_inventory);
}

Output& Output::getInstance(){
    static Output instance;
    return instance;
}

void Output::refreshGameWindow(){
    if(m_zone == NULL) return;

    int cursor_y, cursor_x; /* save cursor position */
    getyx(m_gameWindow, cursor_y, cursor_x);

    const Zone::ElementVector* elements = m_zone->topmostElements();

    for(auto it = elements->cbegin(); it < elements->cend(); ++it){
        mvwaddch(m_gameWindow, (*it)->y(), (*it)->x(), (*it)->symbol());
    }

    wmove(m_gameWindow, cursor_y, cursor_x); /* reset cursor */

    refresh();
    wrefresh(m_gameWindow);
}

void Output::displayInventory(std::set<Item*> items){
    int y = 2;
    int x = 1;
    for(auto it = items.begin(); it != items.end(); ++it){
        mvwaddstr(m_inventory, y++, x, (*it)->name().c_str());
    }
    refresh();
    wrefresh(m_inventory);
}

Zone* Output::zone(){
    return m_zone;
}

Zone* Output::zone(Zone* zone){
    m_zone = zone;
    return m_zone;
}

void Output::cursorPosition(int *x, int *y){
    getyx(stdscr, *y, *x);
}

void Output::cursorPosition(const int x, const int y){
    move(y, x);
}

void Output::gameWindowCursorPosition(int *x, int *y){
    getyx(m_gameWindow, *y, *x);
}

void Output::gameWindowCursorPosition(const int x, const int y){
    wmove(m_gameWindow, y, x);
}
