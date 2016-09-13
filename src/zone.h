/* Zone representing an area in which OnscreenElements
 * can be arranged.
 */

#ifndef ZONE_H
#define ZONE_H 

#include "onscreen_element.h"
#include "guid.h"
#include <unordered_map>
#include <vector>

typedef std::unordered_map<Guid, OnscreenElement*> ElementMap;

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

        const std::vector& topmostElements(){ return m_topmostElements; }

    private:
        void updateTopmostElements();
        void updateTopmostElementAt(int x, int y);

        int m_w, m_h; /* dimensions */
        ElementMap m_elements;
        std::vector<OnscreenElement*> m_topmostElements;
}

#endif /* ifndef ZONE_H */
