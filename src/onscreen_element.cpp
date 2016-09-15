#include "onscreen_element.h"
#include "zone.h"

OnscreenElement::OnscreenElement(){
    static GuidGenerator generator;
    auto newGuid = generator.newGuid();
    m_id = std::hash<Guid>{}(newGuid);
    m_symbol = ' ';
    m_x = 0;
    m_y = 0;
    m_depth = INT_MAX;
}

bool OnscreenElement::move(int x, int y){
    if(m_zone == NULL){
        return false; 
    }
    if(m_x + x < 0 || m_x + x >= m_zone->w()){ return false; }
    if(m_y + y < 0 || m_y + y >= m_zone->h()){ return false; }
    m_x += x;
    m_y += y;
    m_zone->moveElement(this, m_x - x, m_y - y);
    return true;
}
