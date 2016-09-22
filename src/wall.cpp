#include "wall.h"

Wall::Wall(int x, int y, char symbol) :
    Tile(x, y, symbol),
    m_mapId("wall") {}
