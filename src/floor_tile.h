/* Floor tile.
 */

#ifndef __FLOOR_H_ADDED__
#define __FLOOR_H_ADDED__

#include "environment_element.h"

class FloorTile : public EnvironmentElement{
    public:
        FloorTile();
        FloorTile(int x, int y);
        FloorTile(int x, int y, char symbol);
        bool visible();
        bool known();
        bool move(int x, int y);
        bool blocksMovement();
};

#endif // __FLOOR_H_ADDED__
