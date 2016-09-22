#include "door.h"

Door::Door(int x, int y, char openSymbol, char closedSymbol) :
    Tile(x, y),
    m_openSymbol(openSymbol), m_closedSymbol(closedSymbol),
    m_open(false) {}

char Door::getSymbol() const {
    m_symbolSeen = true;
    if(m_open){
        return m_openSymbol;
    }
    return m_closedSymbol;
}

bool Door::blocksMovement() const {
    if(m_open){
        return false;
    }
    return true;
}
