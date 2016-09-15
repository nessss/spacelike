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

    m_gameWindowW = options.gameWindowW; 
    m_gameWindowH = options.gameWindowH; 
    m_gameWindowX = options.gameWindowX; 
    m_gameWindowY = options.gameWindowY; 

    m_gameWindow = newwin(
            m_gameWindowH,
            m_gameWindowW,
            m_gameWindowY,
            m_gameWindowX);

    assert(m_gameWindow != NULL);
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
        std::cerr << (*it)->symbol();
        mvwaddch(m_gameWindow, (*it)->y(), (*it)->x(), (*it)->symbol());
    }

    wmove(m_gameWindow, cursor_y, cursor_x); /* reset cursor */

    refresh();
    wrefresh(m_gameWindow);
}

void Output::setZone(Zone* zone){
    m_zone = zone;
}

void Output::getCursorPosition(int &x, int &y){
    getyx(stdscr, y, x);
}

void Output::setCursorPosition(int x, int y){
    move(y, x);
}

void Output::getGameWindowCursorPosition(int &x, int &y){
    getyx(m_gameWindow, y, x);
}

void Output::setGameWindowCursorPosition(int x, int y){
    wmove(m_gameWindow, y, x);
}
