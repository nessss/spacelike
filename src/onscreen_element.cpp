#include "onscreen_element.h"
#include "zone.h"

OnscreenElement::OnscreenElement(int x, int y, char symbol, int depth, unsigned int attr) :
    m_x(x), m_y(y),
    m_symbol(symbol),
    m_symbolSeen(false),
    m_depth(depth),
    m_attribute(attr) {}

bool OnscreenElement::move(int deltaX, int deltaY){
    if(m_zone == NULL){
        return false; 
    }
    m_symbolSeen = false;
    return m_zone->moveElement(this, deltaX, deltaY);
}
