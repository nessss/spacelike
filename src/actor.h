/* Abstract base class for actors, or entities that exist
 * in world space and can interact with their surroundings.
 */

#ifndef __ACTOR_H_INCLUDED__
#define __ACTOR_H_INCLUDED__

#include "onscreen_element.h"

class Actor : public OnscreenElement{
    public:
        int hp(){ return m_hp; }
        int hp(int hp){ m_hp = hp; return hp; }

    private:
        int m_hp;

};

#endif
