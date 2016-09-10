#include "floor_tile.h"

FloorTile::FloorTile(int x, int y){
    m_repr = '#';
    m_x = x;
    m_y = y;
}

FloorTile::FloorTile(int x, int y, char repr){
    m_repr = repr;
    m_x = x;
    m_y = y;
}

char FloorTile::repr(){
    return m_repr;
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
    return false;
}

int FloorTile::x(){
    return m_x;
}

int FloorTile::y(){
    return m_y;
}
