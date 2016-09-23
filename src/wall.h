/**
 * An impassible wall.
 */
#include "tile.h"

class Wall : public Tile{
    Wall(int x, int y, char symbol);
    Wall(int x, int y) : Wall(x, y, '#') {}
    Wall() : Wall(0, 0, '#') {}
};
