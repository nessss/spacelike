/* Zone representing an area in which OnscreenElements
 * can be arranged.
 */

#ifndef ZONE_H
#define ZONE_H 

#include "onscreen_element.h"
#include "tile.h"
#include <set>
#include <unordered_set>
#include <vector>

class Zone{

    public:
        typedef std::vector<OnscreenElement*> ElementVector;
        typedef std::unordered_set<OnscreenElement*> ElementSet;

        Zone(unsigned int w, unsigned int h);
        Zone(int w, int h);

        unsigned int w();
        unsigned int w(unsigned int w);
        unsigned int w(int w);

        unsigned int h();
        unsigned int h(unsigned int h);
        unsigned int h(int h);

        Tile* tile(unsigned int xy);
        Tile* tile(unsigned int x, unsigned int y);
        Tile* tile(int x, int y);
        Tile* tile(OnscreenElement* element);

        std::vector<Tile*> tiles() const;

        bool elementRegistered(OnscreenElement *element);
        bool addElement(OnscreenElement *element);
        bool removeElement(OnscreenElement *element);
        bool moveElement(OnscreenElement *element, int x, int y);

        void loadMap(const char* path);

    private:
        unsigned int resize(unsigned int w, unsigned int h);

        inline unsigned int flattenCoordinates(unsigned int x, unsigned int y);
        inline unsigned int flattenCoordinates(const OnscreenElement* element);

        unsigned int m_w, m_h;
        ElementSet m_elementSet;
        std::vector<Tile*> m_tiles;
};

#endif /* ifndef ZONE_H */
