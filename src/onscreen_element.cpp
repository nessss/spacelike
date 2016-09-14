#include "onscreen_element.h"

OnscreenElement::OnscreenElement(){
    static GuidGenerator generator;
    auto newGuid = generator.newGuid();
    m_id = std::hash<Guid>{}(newGuid);
    m_symbol = ' ';
    m_x = 0;
    m_y = 0;
    m_depth = INT_MAX;
}
