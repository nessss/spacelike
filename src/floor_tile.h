/* Floor tile.
 */

#ifndef __FLOOR_H_ADDED__
#define __FLOOR_H_ADDED__

#include "environment_element.h"

class FloorTile : public EnvironmentElement{
    public:
        FloorTile();
        FloorTile(int,int);
        FloorTile(int,int,char);
        bool visible();
        bool known();
        bool blocksMovement();
};

#endif // __FLOOR_H_ADDED__
