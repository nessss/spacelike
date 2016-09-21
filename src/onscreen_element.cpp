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

bool OnscreenElement::move(int deltaX, int deltaY){
    if(m_zone == NULL){
        return false; 
    }
    return m_zone->moveElement(this, deltaX, deltaY);
}
