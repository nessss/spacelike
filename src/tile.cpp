#include "tile.h"

Tile::Tile(int x, int y, char symbol) : 
    OnscreenElement(x, y, symbol, INT_MAX, OutputAttribute::normal),
    m_topmostElement(this),
    m_blocksMovement(false) {}

OnscreenElement* Tile::topmostElement(){
    return m_topmostElement;
}

bool Tile::hasElement( OnscreenElement* element ){
    if(m_elements.count(element) == 1){
        return true;
    }
    return false;
}

const std::set<OnscreenElement*> Tile::elements(){
    return m_elements;
}

bool Tile::addElement( OnscreenElement* element ){

    if(hasElement(element)){
        return false;
    }

    m_elements.insert(element);

    element->tile(this);

    if(m_topmostElement == this || element->depth() < m_topmostElement->depth()){
        m_topmostElement = element;
    }

    Item* item = dynamic_cast<Item*>( element );
    if( item != NULL )
    {
        m_items.insert( item );
    }

    return true;
}

bool Tile::removeElement(OnscreenElement* element){
    if(m_elements.count(element) == 1){
        m_elements.erase(element);
        if(element == m_topmostElement){
            if(m_elements.size() == 0){
                m_topmostElement = this;
                symbolSeen(false);
                return true;
            }
            m_topmostElement = *(m_elements.begin());
            for(auto it = m_elements.begin(); it != m_elements.end(); ++it){
                if((*it)->depth() > m_topmostElement->depth()){
                    m_topmostElement = *it;
                    (*it)->symbolSeen(false);
                }
            }
        }
        return true;
    }
    return false;
}

bool Tile::moveElement(OnscreenElement* element, Tile* other){
    if(hasElement(element) && !other->hasElement(element)){
        removeElement(element);
        other->addElement(element);
        return true;
    }
    return false;
}

const std::set<Item*> Tile::items()
{
    return m_items;
}

bool Tile::blocksMovement() const {
    return m_blocksMovement;
}

bool Tile::blocksMovement(bool blocks){
    m_blocksMovement = blocks;
    return m_blocksMovement;
}
