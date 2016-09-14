#include "zone.h"

Zone::Zone(int w, int h){
    m_w = w;
    m_h = h;

    m_topmostElements.assign(m_w * m_h, NULL);
    m_elementsByCoordinates.resize(m_w * m_h);
}

bool Zone::elementRegistered(OnscreenElement *element){
    if(m_elementSet.count(element) == 0){
        return false;
    }
    return true;
}

bool Zone::addElement(OnscreenElement *element){
    if(!elementRegistered(element)){
        m_elementSet.insert(element);

        int idx = getFlatCoordinates(*element);
        m_elementsByCoordinates[idx].insert(element);
        updateTopmostElementAt(idx);
        return true;
    }
    return false;
}

bool Zone::removeElement(OnscreenElement *element){
    if(elementRegistered(element)){
        m_elementSet.erase(element);
        return true;
    }
    return false;
}

bool Zone::moveElement(OnscreenElement *element, int x, int y){
    if(elementRegistered(element)){
        int prev_x = element->x();
        int prev_y = element->y();
        ElementDepthSet& oldLocation = depthSetAtElementCoordinates(
                element);
        if(element->move(x, y)){
            oldLocation.erase(element);
            depthSetAtElementCoordinates(element).insert(element);
            updateTopmostElementAt(prev_x, prev_y);
            updateTopmostElementAt(element->x(), element->y());
            return true;
        }
    }
    return false;
}

int Zone::flattenCoordinates(int x, int y){
    return x + (y * m_w);
}

int Zone::getFlatCoordinates(const OnscreenElement& element){
    return flattenCoordinates(element.x(), element.y());
}

void Zone::updateTopmostElements(){
    for(int i=0; i < m_w*m_h; ++i){
        updateTopmostElementAt(i);
    }
}

void Zone::updateTopmostElementAt(int flatCoordinate){
    OnscreenElement* element;
    element = *(m_elementsByCoordinates[flatCoordinate].begin());
    m_topmostElements[flatCoordinate] = element;
}

void Zone::updateTopmostElementAt(int x, int y){
    updateTopmostElementAt(flattenCoordinates(x, y));
}

OnscreenElement* Zone::topmostElementAt(int x, int y){
    return m_topmostElements[flattenCoordinates(x, y)];
}

const ElementVector* Zone::topmostElements() const {
    return &m_topmostElements;
}

ElementDepthSet& Zone::depthSetAtCoordinates(int x, int y){
    return m_elementsByCoordinates[flattenCoordinates(x, y)];
} 

ElementDepthSet& Zone::depthSetAtElementCoordinates(OnscreenElement* element){
    return depthSetAtCoordinates(element->x(), element->y());
}

bool Zone::addElementToCoordinateVector(OnscreenElement *element){
    ElementDepthSet& coordinateSet = depthSetAtCoordinates(
            element->x(),
            element->y());
    if(coordinateSet.count(element) > 0){
        return false;
    }
    coordinateSet.insert(element);
    return true;
}
