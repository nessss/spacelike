/**
 * One game tile.
 */

#ifndef TILE_H
#define TILE_H

#include <set>
#include "onscreen_element.h"

class Zone;

class Tile : public OnscreenElement{
    public:
        Tile(int x=0, int y=0, char symbol='.');

        OnscreenElement* topmostElement();
        const std::set<OnscreenElement*> elements();
        bool hasElement(OnscreenElement* element);
        bool addElement(OnscreenElement* element);
        bool removeElement(OnscreenElement* element);
        bool moveElement(OnscreenElement* element, Tile* other);

        virtual bool blocksMovement() const;
        virtual bool blocksMovement(bool blocks);

        Zone* zone() const{ return m_zone; }
        Zone* zone(Zone* zone){ m_zone = zone; return m_zone; }

        bool visible(){ return true; }
        bool known(){ return true; }

    private:
        std::set<OnscreenElement*> m_elements;
        OnscreenElement* m_topmostElement;
        bool m_blocksMovement;

        Zone* m_zone;
};

#endif /* TILE_H */
