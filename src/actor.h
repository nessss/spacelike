/* Abstract base class for actors, or entities that exist
 * in world space and can interact with their surroundings.
 */

#ifndef __ACTOR_H_INCLUDED__
#define __ACTOR_H_INCLUDED__

#include "onscreen_element.h"

class Actor : public OnscreenElement{
    public:
        virtual int move(int, int) = 0;
};

#endif
