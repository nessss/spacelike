#include "output.h"
#include <iostream>
#include <limits.h>

Output::Output(int w, int h, int offset){
    m_w = w;
    m_h = h;
    m_offset = offset;
    lastScreen = std::vector<char>(m_w * m_h, ' ');
}

void Output::refresh(){
    std::vector<int> depths(m_w * m_h, INT_MAX);
    std::vector<char> screen(lastScreen);

    /* find lowest depth values (i.e. highest objects) */
    for(auto entry = elements.begin(); entry != elements.end(); ++entry){
        OnscreenElement *element = entry->second;
        int idx = (element->y() * m_w) + element->x();
        if(element->x() < 0 || element->x() > m_w) continue;
        if(element->y() < 0 || element->y() > m_h) continue;
        if(element->depth() <= depths[idx]){
            depths[idx] = element->depth();
            screen[idx] = element->symbol();
        }
    }

    /* draw elements */

    int cursor_y, cursor_x;
    getyx(stdscr, cursor_y, cursor_x);
    for(int i = 0; i < screen.size(); ++i){
        if(screen[i] != lastScreen[i]){
            mvaddch(i/m_w + m_offset, i%m_w + m_offset, screen[i]);
            lastScreen[i] = screen[i];
        }
    }
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
