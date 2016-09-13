#include "zone.h"

Zone::Zone(int w, int h){
    m_w = w;
    m_h = h;
    m_topMostElements.assign(m_w * m_h, NULL);
}

bool Zone::elementRegistered(OnscreenElement *element){
    if(elements.count(element->guid()) == 0){
        return false;
    }
    return true;
}

bool Zone::addElement(OnscreenElement *element){
    if(!elementRegistered(element)){
        elements[element->guid()] = element;
        return true;
    }
    return false;
}

bool Zone::removeElement(OnscreenElement *element){
    if(elementRegistered(element)){
        elements.erase(element->guid());
        return true;
    }
    return false;
}

bool Zone::moveElement(OnscreenElement *element, int x, int y){
    if(elementRegistered(element)){
        int prev_x = element->x();
        int prev_y = element->y();
        if(element->move(x, y)){
            updateTopmostElementAt(prev_x, prev_y);
            updateTopmostElementAt(element->x(), element->y());
            return true;
        }
    }
    return false;
}

OnscreenElement* Zone::topmostElementAt(int x, int y){
    return m_topmostElements[x + (y * m_w)];
}
