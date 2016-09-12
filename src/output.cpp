#include "output.h"
#include <iostream>

Output::Output(int w, int h, int offset){
    m_w = w;
    m_h = h;
    m_offset = offset;
}

void Output::refresh(){
    std::vector<int> depths(m_w * m_h, INT_MAX);
    std::vector<char> screen(m_w * m_h, ' ');

    /* find lowest depth values (i.e. highest objects) */
    for(auto entry = elements.begin(); entry != elements.end(); ++entry){
        OnscreenElement *element = entry->second;
        int idx = (element->y() * m_w) + element->x();
        if(element->depth() <= depths[idx]){
            depths[idx] = element->depth();
            screen[idx] = element->symbol();
        }
    }

    /* draw elements */

    int cursor_y, cursor_x;
    getyx(stdscr, cursor_y, cursor_x);
    for(int y = 0; y < m_h; ++y){
        mvaddnstr(y + m_offset, m_offset, screen.data() + (m_w * y), m_w);
    }
    move(cursor_y, cursor_x);
}

void Output::addElement(OnscreenElement *element){
    elements[element->guid()] = element;
}
