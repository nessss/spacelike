/* Zone representing an area in which OnscreenElements
 * can be arranged.
 */

#ifndef ZONE_H
#define ZONE_H 

#include "onscreen_element.h"
#include "guid.h"
#include <set>
#include <unordered_set>
#include <vector>

class Zone{

    public:
        typedef std::vector<OnscreenElement*> ElementVector;
        typedef std::unordered_set<OnscreenElement*> ElementSet;
        typedef std::set<OnscreenElement*, OnscreenElementPtrDepthComp> ElementDepthSet;
        typedef std::vector<ElementDepthSet> ElementDepthSetVector;

        Zone(int w, int h);

        int w();
        int w(int w);

        int h();
        int h(int h);

        bool elementRegistered(OnscreenElement *element);
        bool addElement(OnscreenElement *element);
        bool removeElement(OnscreenElement *element);
        bool moveElement(OnscreenElement *element, int x, int y);

        OnscreenElement* topmostElementAt(int x, int y);

        const ElementVector* topmostElements() const;

    private:
        int flattenCoordinates(int x, int y);
        int flattenCoordinates(const OnscreenElement* element);

        void updateTopmostElements();
        void updateTopmostElementAt(int x, int y);
        void updateTopmostElementAt(int flatCoordinates);
        void updateTopmostElementAt(OnscreenElement* element);

        ElementDepthSet& depthSetAt(int x, int y);
        ElementDepthSet& depthSetAt(int flatCoordinates);
        ElementDepthSet& depthSetAt(OnscreenElement* element);

        bool addToDepthSet(OnscreenElement* element);
        bool removeFromDepthSet(OnscreenElement* element);

        int m_w, m_h;
        ElementSet m_elementSet;
        ElementVector m_topmostElements;
        ElementDepthSetVector m_elementsByCoordinates;
};

#endif /* ifndef ZONE_H */
