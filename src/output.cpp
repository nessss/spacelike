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

void Output::init(int w, int h, int offset){
    m_w = w;
    m_h = h;
    m_offset = offset;
    lastScreen = std::vector<char>(m_w * m_h, ' ');
    m_gameWindow = newwin(m_h, m_w, m_offset, m_offset);
    assert(m_gameWindow != NULL);
}

Output& Output::getInstance(){
    static Output instance;
    return instance;
}

void Output::refreshGameWindow(){
    std::vector<int> depths(m_w * m_h, INT_MAX);
    std::vector<char> screen(lastScreen);

    /* find lowest depth values (i.e. highest objects) */
    for(auto entry = elements.begin(); entry != elements.end(); ++entry){
        OnscreenElement *element = entry->second;
        // skip out-of-range elements
        if(element->x() < 0 || element->x() > m_w) continue;
        if(element->y() < 0 || element->y() > m_h) continue;

        int idx = (element->y() * m_w) + element->x();
        if(element->depth() <= depths[idx]){
            depths[idx] = element->depth();
            screen[idx] = element->symbol();
        }
    }

    /* draw elements */

    refresh();
    int cursor_y, cursor_x;
    getyx(stdscr, cursor_y, cursor_x);
    for(int i = 0; i < screen.size(); ++i){
        if(screen[i] != lastScreen[i]){
            mvwaddch(gameWindow, i/m_w, i%m_w, screen[i]);
            lastScreen[i] = screen[i];
        }
    }
    wrefresh(gameWindow);
    move(cursor_y, cursor_x);
}

void getCursorPosition(int &x, int &y){
    getyx(stdscr, y, x);
}

void setCursonPosition(int x, int y){
    move(y, x);
}

void Output::addElement(OnscreenElement *element){
    elements[element->guid()] = element;
}

void Output::removeElement(OnscreenElement *element){
    elements.erase(element->guid());
}
