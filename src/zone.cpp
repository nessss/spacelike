#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "zone.h"
#include "rapidxml.hpp"

/**
 * @param[in] w Width of the zone
 * @param[in] h Height of the zone
 */

Zone::Zone(unsigned int w, unsigned int h){

    if(w == 0) throw std::invalid_argument("Zone::Zone(unsigned int w, unsigned int h) w == 0");
    if(h == 0) throw std::invalid_argument("Zone::Zone(unsigned int w, unsigned int h) h == 0");

    resize(w, h);

}

Zone::Zone(int w, int h){

    if(w <= 0) throw std::invalid_argument("Zone::Zone(int w, int h): w <= 0");
    if(h <= 0) throw std::invalid_argument("Zone::Zone(int w, int h): h <= 0");

    resize((int)w, (int)h);
}

/**
 * Get the width of the zone
 * @details The number of columns.
 * @retval int Width of the zone
 */
unsigned int Zone::w(){
    return m_w;
}

/**
 * Set the width of the zone
 * @copydetails Zone::w()
 * @retval int New width of the zone
 */
unsigned int Zone::w(unsigned int w){
    // TODO: make this not break everything
    if(w == 0) throw std::invalid_argument("Zone::w(unsigned int w) w == 0");
    m_w = w;
    return m_w;
}

unsigned int Zone::w(int w){
    if(w <= 0) throw std::invalid_argument("Zone::w(int w): w <= 0");
    return this->w((unsigned int)w);
}

/**
 * Get the height of the zone
 * @details The number of rows.
 * @retval int Height of the zone
 */
unsigned int Zone::h(){
    return m_h;
}

/**
 * Set the height of the zone
 * @copydetails Zone::h()
 * @retval int New height of the zone
 */
unsigned int Zone::h(unsigned int h){
    // TODO: make this not break everything
    if(h == 0) throw std::invalid_argument("Zone::h(unsigned int h) h == 0");
    m_h = h;
    return m_h;
}

unsigned int Zone::h(int h){
    if(h <= 0) throw std::invalid_argument("Zone::h(unsigned int h) h <= 0");
    return this->h((unsigned int)h);
}

Tile* Zone::tile(unsigned int xy){
    if(xy >= m_w * m_h) throw std::out_of_range("Zone::tile(int xy) argument out of range");
    return m_tiles[xy];
}

Tile* Zone::tile(unsigned int x, unsigned int y){
    if(x >= m_w) throw std::out_of_range("Zone::tile(unsigned int x, unsigned int y): x >= width");
    if(y >= m_h) throw std::out_of_range("Zone::tile(unsigned int x, unsigned int y): y >= height");
    return tile(flattenCoordinates(x, y));
}

Tile* Zone::tile(int x, int y){
    if(x < 0)    throw std::out_of_range("Zone:tile(int x, int y) x < 0");
    if(x >= m_w) throw std::out_of_range("Zone:tile(int x, int y) x > w");
    if(y < 0)    throw std::out_of_range("Zone:tile(int x, int y) y < 0");
    if(y >= m_h) throw std::out_of_range("Zone:tile(int x, int y) y > h");
    if(x < 0 || y < 0){
        throw std::out_of_range("Zone::tile");
    }
    return tile((unsigned int)x, (unsigned int)y);
}

Tile* Zone::tile(OnscreenElement* element){
    return tile(flattenCoordinates(element));
}

std::vector<Tile*> Zone::tiles() const {
    return m_tiles;
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

        unsigned int idx = flattenCoordinates(element);
        m_tiles[idx]->addElement(element);

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
        element->zone(NULL);

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
        unsigned int oldX = element->x();
        unsigned int oldY = element->y();

        if((int)oldX + deltaX < 0 || (int)oldX + deltaX >= w()){ return false; }
        if((int)oldY + deltaY < 0 || (int)oldY + deltaY >= h()){ return false; }

        unsigned int newX = element->x() + deltaX;
        unsigned int newY = element->y() + deltaY;

        m_tiles[flattenCoordinates(element)]->moveElement(
                element, m_tiles[flattenCoordinates(newX, newY)]);
        element->x(newX);
        element->y(newY);
        return true;
    }
    return false;
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

unsigned int Zone::resize(unsigned int w, unsigned int h){
    m_w = w;
    m_h = h;

    if(m_tiles.size() == 0){
        m_tiles.assign(m_w * m_h, NULL);
        for(int x = 0; x < m_w; ++x){
            for(int y = 0; y < m_h; ++y){
                unsigned int idx = flattenCoordinates(x, y);
                if(x == 0 || x == m_w - 1 || y == 0 || y == m_h -1){
                    m_tiles[idx] = new Tile(x, y, '#');
                    m_tiles[idx]->blocksMovement(true);
                }else{
                    m_tiles[idx] = new Tile(x, y);
                }
            }
        }
    }

    return m_w * m_h;
}

/** Get "flattened" one-dimensional representation of coordinates
 * @param[in] x X component of coordinates to be flattened
 * @param[in] y Y component of coordinates to be flattened
 * @retval int Flattened coordinates 
 */
unsigned int Zone::flattenCoordinates(unsigned int x, unsigned int y){
    return x + (y * m_w);
}

/**
 * @copybrief Zone::flattenCoordinates(int,int)
 * @param[in] element* Pointer to element whose flattened coordinates should be returned
 * @retval int Flattened coordinates of element
 */
unsigned int Zone::flattenCoordinates(const OnscreenElement* element){
    return flattenCoordinates(element->x(), element->y());
}

/**
 * @typedef std::vector<OnscreenElement*> Zone::ElementVector
 * A depth-ordered std::set of OnscreenElement*
 */

/**
 * @typedef std::unordered_set<OnscreenElement*> Zone::ElementSet
 * An id-ordered std::set of OnscreenElements*
 */
