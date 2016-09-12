/* Abstract base class for elements that can be printed to the screen.
 */

#ifndef ONSCREEN_ELEMENT_H
#define ONSCREEN_ELEMENT_H

#include "guid.h"

class OnscreenElement{
    public:
        virtual bool visible() = 0;         /* currently visible?       */
        virtual bool known() = 0;           /* location known?          */

        Guid guid();
        char symbol(){ return m_symbol; }   /* on-screen representation */
        int x(){ return m_x; }              /* location in world-space */
        int y(){ return m_y; }
        int depth(){ return m_depth; }      /* draw order */

    protected:
        Guid m_guid;
        char m_symbol;
        int m_x, m_y;
        int m_depth;
};

#endif /* ONSCREEN_ELEMENT_H */
