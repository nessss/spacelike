/* Floor tile.
 */

#ifndef __FLOOR_H_ADDED__
#define __FLOOR_H_ADDED__

#include "environment_element.h"

class FloorTile : EnvironmentElement{
    public:
        FloorTile();
        FloorTile(int,int);
        FloorTile(int,int,char);
        char repr();
        bool visible();
        bool known();
        bool blocksMovement();
        int x();
        int y();

    private:
        char m_repr;
        int m_x;
        int m_y;
};

#endif // __FLOOR_H_ADDED__
