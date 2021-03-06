#include "output.h"
#include "application.h"
#include <iostream>
#include <limits.h>
#include <cassert>
#include <algorithm>

Output::Output(){
    /* init curses */
    signal(SIGINT, Application::finish);  /* arrange interrupts to terminate */

    /* force xterm-256color to avoid tmux silliness */
    SCREEN* terminal = newterm((char*)"xterm-256color", stdout, stdin);
    set_term(terminal);
    keypad(stdscr, TRUE);     /* enable keyboard mapping */
    nonl();                   /* tell curses not to do NL->CR/NL on output */
    cbreak();                 /* take input chars one at a time, no wait for \n */
    noecho();                 /* do not echo input */
    curs_set(0);              /* invisible cursor */
    attrset(A_NORMAL);

    if(has_colors()){
        start_color();
        use_default_colors();
    }
}

void Output::init(const OutputOptions& options, Zone* startingZone){

    this->options = options;
    zone(startingZone);

    m_gamePad = newpad(zone()->h(), zone()->w());
    m_inventoryPad = newpad(256, 256);

    assert(m_gamePad != NULL);
    assert(m_inventoryPad != NULL);
}

Output& Output::getInstance(){
    static Output instance;
    return instance;
}

void Output::refreshGameWindow(){
    if(m_zone == NULL) return;


    int cursorY, cursorX; /* save cursor position */
    getyx(m_gamePad, cursorY, cursorX);

    std::vector<Tile*> tiles = m_zone->tiles();

    for(auto it = tiles.cbegin(); it < tiles.cend(); ++it){
        OnscreenElement* element = (*it)->topmostElement();
        if(!element->symbolSeen()){
            mvwaddch(
                    m_gamePad,
                    element->y(), element->x(),
                    element->getSymbol() | element->attribute());
        }
    }

    wmove(m_gamePad, cursorY, cursorX); /* reset cursor */
    wnoutrefresh(stdscr);
    pnoutrefresh(m_gamePad,
            0, 0,
            options.gameWindowY, options.gameWindowX,
            options.gameWindowY + options.gameWindowH, 
            options.gameWindowX + options.gameWindowW);

    doupdate();
}

void Output::updateInventory(std::set<Item*> items){

    werase(m_inventoryPad);

    int i = 0;
    m_longestName = 0;
    for(auto it = items.begin(); it != items.end(); ++it){
        wmove(m_inventoryPad, i, 0);
        waddstr(m_inventoryPad, (*it)->name().c_str());
        m_longestName = std::max(m_longestName, (int)(*it)->name().length());
    }
}

void Output::displayInventory(){

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    int startY = options.gameWindowY;
    int startX = maxX - m_longestName - 2;

    int endY = min(options.gameWindowY + options.gameWindowH, maxY - 1);
    int endX = maxX - 1;

    wnoutrefresh(stdscr);
    pnoutrefresh(m_inventoryPad, 0, 0, startY, startX, endY, endX);

    doupdate();

    getch();

    wnoutrefresh(stdscr);
    doupdate();
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
    getyx(m_gamePad, *y, *x);
}

void Output::gameWindowCursorPosition(const int x, const int y){
    wmove(m_gamePad, y, x);
    wmove(stdscr, y + options.gameWindowY, x + options.gameWindowX);
}
