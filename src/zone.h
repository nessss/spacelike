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

typedef std::unordered_set<OnscreenElement*> ElementSet;
typedef std::set<OnscreenElement*, OnscreenElementPtrDepthComp> ElementDepthSet;
typedef std::vector<ElementDepthSet> ElementDepthSetVector;
typedef std::vector<OnscreenElement*> ElementVector;

class Zone{
    public:
        Zone(int w, int h);

        int w(){ return m_w; }
        int w(int w){ m_w = w; return m_w; }

        int h(){ return m_h; }
        int h(int h){ m_h = h; return m_h; }

        bool elementRegistered(OnscreenElement *element);
        bool addElement(OnscreenElement *element);
        bool removeElement(OnscreenElement *element);
        bool moveElement(OnscreenElement *element, int x, int y);

        OnscreenElement* topmostElementAt(int x, int y);

        const ElementVector* topmostElements() const;

    private:
        int flattenCoordinates(int x, int y);
        int getFlatCoordinates(const OnscreenElement& element);
        void updateTopmostElements();
        void updateTopmostElementAt(int flatCoordinate);
        void updateTopmostElementAt(int x, int y);

        ElementDepthSet& depthSetAtCoordinates(int x, int y);
        ElementDepthSet& depthSetAtElementCoordinates(OnscreenElement* element);
        bool addElementToCoordinateVector(OnscreenElement *element);
        bool removeElementfromCoordinateVector(OnscreenElement *element);

        int m_w, m_h; /* dimensions */
        ElementSet m_elementSet;
        ElementVector m_topmostElements;
        ElementDepthSetVector m_elementsByCoordinates;
};

#endif /* ifndef ZONE_H */
