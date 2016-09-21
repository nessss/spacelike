#include <iostream>
#include <fstream>
#include <string>
#include "zone.h"
#include "rapidxml.hpp"

/**
 * @param[in] w Width of the zone
 * @param[in] h Height of the zone
 */
Zone::Zone(int w, int h){
    m_w = w;
    m_h = h;

    m_topmostElements.assign(m_w * m_h, NULL);
    m_tiles.assign(m_w * m_h, NULL);
    for(int x = 0; x < m_w; ++x){
        for(int y = 0; y < m_h; ++y){
            int idx = flattenCoordinates(x, y);
            if(x == 0 || x == m_w - 1 || y == 0 || y == m_h -1){
                m_tiles[idx] = new Tile(x, y, '#');
                m_tiles[idx]->blocksMovement(true);
            }else{
                m_tiles[idx] = new Tile(x, y);
            }
        }
    }
    updateTopmostElements();
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

Tile* Zone::tile(int xy){
    return m_tiles[xy];
}

Tile* Zone::tile(int x, int y){
    return tile(flattenCoordinates(x, y));
}

Tile* Zone::tile(OnscreenElement* element){
    return tile(flattenCoordinates(element));
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
        m_tiles[idx]->addElement(element);

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
        m_tiles[flattenCoordinates(element)]->removeElement(element);
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
bool Zone::moveElement(OnscreenElement *element, int deltaX, int deltaY){
    if(elementRegistered(element)){
        int oldX = element->x();
        int oldY = element->y();
        int newX = element->x() + deltaX;
        int newY = element->y() + deltaY;
        if(newX < 0 || newX >= w()){ return false; }
        if(newY < 0 || newY >= h()){ return false; }
        m_tiles[flattenCoordinates(element)]->moveElement(
                element, m_tiles[flattenCoordinates(newX, newY)]);
        element->x(newX);
        element->y(newY);
        updateTopmostElementAt(oldX, oldY);
        updateTopmostElementAt(element);
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

/**
 * Load a map from a .map file
 */
void Zone::loadMap(const char* path){
    using namespace rapidxml;

    std::ifstream file(path, std::ifstream::in);
    std::string content( (std::istreambuf_iterator<char>(file) ),
                         (std::istreambuf_iterator<char>()     ));

    xml_document<> document;
    document.parse<parse_trim_whitespace>((char*)content.c_str());

    xml_node<>* objectNode = document.first_node("object");
    std::cerr << objectNode->first_attribute("name")->value() << std::endl;

    xml_node<>* legendNode = objectNode->first_node("legend");
    for(xml_node<>* entryNode = legendNode->first_node();
            entryNode; entryNode = entryNode->next_sibling()){
        std::cerr << entryNode->first_attribute("symbol")->value() << " - ";
        std::cerr << entryNode->first_attribute("type")->value() << std::endl;
    }

    xml_node<>* mapNode = objectNode->first_node("map");
    char* mapData = mapNode->value();
    std::cerr << mapNode->value_size() << std::endl;
    int i = 0;
    int row = 0;
    int column = 0;
    while(true){
        while(*mapData != '\n'){
            std::cerr << *mapData;
            std::cerr << column;
            i++;
            column++;
            mapData++;
            if(i >= (int)mapNode->value_size()) break;
        }
        column = 0;
        std::cerr << row << std::endl;
        mapData++;
        i++;
        row++;
        if(i >= (int)mapNode->value_size()) break;
    }
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
    element = m_tiles[flatCoordinates]->topmostElement();
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
