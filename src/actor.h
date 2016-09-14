/* Abstract base class for actors, or entities that exist
 * in world space and can interact with their surroundings.
 */

#ifndef ACTOR_H
#define ACTOR_H

#include "onscreen_element.h"
#include "zone.h"

class Actor : public OnscreenElement{
    public:
        int hp(){ return m_hp; }
        int hp(int hp){ m_hp = hp; return hp; }

        Zone* zone() const { return m_zone; }
        Zone* zone(Zone* zone){ m_zone = zone; return m_zone; }

    protected:
        int m_hp;
        Zone* m_zone;

};

#endif
