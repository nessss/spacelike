#include "zone.h"

/**
 * @param[in] w Width of the zone
 * @param[in] h Height of the zone
 */
Zone::Zone(int w, int h){
    m_w = w;
    m_h = h;

    m_topmostElements.assign(m_w * m_h, NULL);
    m_elementsByCoordinates.resize(m_w * m_h);
}

/**
 * Get the width of the zone
 * @details The number of columns.
 * @retval int Width of the zone
 */
int Zone::w(){
    return m_w;
}

/**
 * Set the width of the zone
 * @copydetails Zone::w()
 * @retval int New width of the zone
 */
int Zone::w(int w){
    // TODO: make this not break everything
    m_w = w;
    return m_w;
}

/**
 * Get the height of the zone
 * @details The number of rows.
 * @retval int Height of the zone
 */
int Zone::h(){
    return m_h;
}

/**
 * Set the height of the zone
 * @copydetails Zone::h()
 * @retval int New height of the zone
 */
int Zone::h(int h){
    // TODO: make this not break everything
    m_h = h;
    return m_h;
}

/**
 * Check if an OnscreenElement has been added to the zone
 * @param[in] element* Pointer to the OnscreenElement whose registration status to check
 * @retval bool `true` if the element is registered, `false` otherwise
 */
bool Zone::elementRegistered(OnscreenElement *element){
    if(m_elementSet.count(element) == 0){
        return false;
    }
    return true;
}

/**
 * Add an OnscreenElement to the zone
 * @param[in] element* Pointer to the OnscreenElement to be added
 * @retval bool `true` if the element was added successfully, `false` otherwise
 */
bool Zone::addElement(OnscreenElement *element){
    if(!elementRegistered(element)){
        m_elementSet.insert(element);

        int idx = flattenCoordinates(element);
        m_elementsByCoordinates[idx].insert(element);
        updateTopmostElementAt(idx);
        element->zone(this);
        return true;
    }
    return false;
}

/**
 * Remove an OnscreenElement from the zone
 * @param[in] element* Pointer to the OnscreenElement to be removed
 * @retval bool `true` if the element was removed successfully, `false` otherwise 
 */
bool Zone::removeElement(OnscreenElement *element){
    // TODO: remove from depth set as well
    if(elementRegistered(element)){
        m_elementSet.erase(element);
        return true;
    }
    return false;
}

/**
 * Move an element from one coordinate to another
 * @param[in] element* Pointer to the element to be moved
 * @param[in] old_x X coordinate of the element's old position
 * @param[in] old_y Y coordinate of the element's old position
 * @retval bool `true` if the element was moved successfully, `false` otherwise
 */
bool Zone::moveElement(OnscreenElement *element, int old_x, int old_y){
    if(elementRegistered(element)){
        depthSetAt(old_x, old_y).erase(element);
        depthSetAt(element).insert(element);
        updateTopmostElementAt(old_x, old_y);
        updateTopmostElementAt(element->x(), element->y());
        return true;
    }
    return false;
}

/**
 * Get a pointer to the vector of topmost elements for each coordinate
 * @retval std::vector<OnscreenElement*>* Pointer to the vector of pointers to topmost elements in the zone
 */
const Zone::ElementVector* Zone::topmostElements() const {
    return &m_topmostElements;
}

/*******************************************
 *
 *            private methods 
 *
 ******************************************/

/** Get "flattened" one-dimensional representation of coordinates
 * @param[in] x X component of coordinates to be flattened
 * @param[in] y Y component of coordinates to be flattened
 * @retval int Flattened coordinates 
 */
int Zone::flattenCoordinates(int x, int y){
    return x + (y * m_w);
}

/**
 * @copybrief Zone::flattenCoordinates(int,int)
 * @param[in] element* Pointer to element whose flattened coordinates should be returned
 * @retval int Flattened coordinates of element
 */
int Zone::flattenCoordinates(const OnscreenElement* element){
    return flattenCoordinates(element->x(), element->y());
}

/**
 * Update the internal vector of topmost elements.
 */
void Zone::updateTopmostElements(){
    for(int i=0; i < m_w*m_h; ++i){
        updateTopmostElementAt(i);
    }
}

/**
 * Update the topmost element at specific coordinates
 * @param[in] x X coordinate of location to update
 * @param[in] y Y coordinate of location to update
 */
void Zone::updateTopmostElementAt(int x, int y){
    updateTopmostElementAt(flattenCoordinates(x, y));
}

/**
 * @copybrief Zone::updateTopmostElementAt(int,int)
 * @param[in] flatCoordinates Flattened coordinates of location to update
 */
void Zone::updateTopmostElementAt(int flatCoordinates){
    OnscreenElement* element;
    element = *(m_elementsByCoordinates[flatCoordinates].begin());
    m_topmostElements[flatCoordinates] = element;
}

/**
 * @copybrief Zone::updateTopmostElementAt(int,int)
 * @param[in] element* Pointer to element whose location's topmost element should be updated
 */
void Zone::updateTopmostElementAt(OnscreenElement* element){
    updateTopmostElementAt(flattenCoordinates(element));
}

/**
 * Get a pointer to the topmost element at specific coordinates
 * @param[in] x X component of coordinates
 * @param[in] y Y component of coordinates
 * @retval OnscreenElement* Pointer to topmost element at `x, y`
 */
OnscreenElement* Zone::topmostElementAt(int x, int y){
    return m_topmostElements[flattenCoordinates(x, y)];
}

/**
 * Get a reference to the depth-sorted set of elements at a specific location
 * @param[in] x X coordinate of location
 * @param[in] y Y coordinate of location
 * @retval ElementDepthSet& Reference to std::set<OnscreenElement*, OnscreenElementPtrDepthComp>
 */
Zone::ElementDepthSet& Zone::depthSetAt(int x, int y){
    return m_elementsByCoordinates[flattenCoordinates(x, y)];
} 

/**
 * @copybrief Zone::depthSetAt(int,int)
 * @param[in] flatCoordinates Flattened coordinates of location
 * @retval ElementDepthSet& Reference to std::set<OnscreenElement*, OnscreenElementPtrDepthComp>
 */
Zone::ElementDepthSet& Zone::depthSetAt(int flatCoordinates){
    return m_elementsByCoordinates[flatCoordinates];
} 

/**
 * @copybrief Zone::depthSetAt(int,int)
 * @param[in] element Flattened coordinates of location
 * @retval ElementDepthSet& Reference to std::set<OnscreenElement*, OnscreenElementPtrDepthComp>
 */
Zone::ElementDepthSet& Zone::depthSetAt(OnscreenElement* element){
    return depthSetAt(element->x(), element->y());
}

/**
 * Add an OnscreenElement to the depth-ordered set at its coordinates
 * @param[in] OnscreenElement* Element to be added
 * @retval bool `true` if the element was successfully added, `false` otherwise
 */
bool Zone::addToDepthSet(OnscreenElement* element){
    ElementDepthSet& theSet = depthSetAt(element);
    for(auto it = theSet.begin(); it != theSet.end(); ++it){
        if( (*it)->id() == element->id() ){
            return false;
        }
    }
    theSet.insert(element);
    return true;
}

/**
 * Remove an OnscreenElement from the depth-ordered set at its coordinates
 * @param[in] OnscreenElement* Element to be added
 * @retval bool `true` if the element was successfully added, `false` otherwise
 */
bool Zone::removeFromDepthSet(OnscreenElement* element){
    ElementDepthSet& theSet = depthSetAt(element);
    for(auto it = theSet.begin(); it != theSet.end(); ++it){
        if( (*it)->id() == element->id() ){
            theSet.erase(it);
            return true;
        }
    }
    return false;
}

/**
 * @typedef std::vector<OnscreenElement*> Zone::ElementVector
 * A depth-ordered std::set of OnscreenElement*
 */

/**
 * @typedef std::unordered_set<OnscreenElement*> Zone::ElementSet
 * An id-ordered std::set of OnscreenElements*
 */

/**
 * @typedef std::set<OnscreenElement*, OnscreenElementPtrDepthComp> Zone::ElementDepthSet
 * A depth-ordered std::set of OnscreenElements*
 */

/**
 * @typedef std::vector<ElementDepthSet> Zone::ElementDepthSetVector;
 * An std::vector of ElementDepthSet
 */
