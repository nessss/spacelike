/**
 * Base class for actors. Represents entities that exist
 * in world space and can interact with their surroundings.
 */

#ifndef ACTOR_H
#define ACTOR_H

#include "onscreen_element.h"
#include "zone.h"

class Actor : public OnscreenElement{
    public:
        int hp(){ return m_hp; } //!< Get current health points
        int hp(int hp){ m_hp = hp; return hp; } //!< Set current health points

    protected:
        Actor(){} //!< Constructor
        int m_hp; //!< Health points

};

#endif
