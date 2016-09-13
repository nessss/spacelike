#include "floor_tile.h"

FloorTile::FloorTile(int x, int y){
    m_symbol = '#';
    m_x = x;
    m_y = y;
    m_depth = 100;
}

FloorTile::FloorTile(int x, int y, char symbol){
    m_symbol = symbol;
    m_x = x;
    m_y = y;
    m_depth = 100;
}

bool FloorTile::visible(){
    // TODO: implement line-of-sight
    return true;
}

bool FloorTile::known(){
    // TODO: implement player memory
    return true;
}

bool FloorTile::blocksMovement(){
    /* always traversable */
    return false;
}

bool FloorTile::move(int x, int y){
    /* cannot move */
    return false;
}
