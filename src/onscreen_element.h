/* Abstract base class for elements that can be printed to the screen.
 */

#ifndef ONSCREEN_ELEMENT_H
#define ONSCREEN_ELEMENT_H

#include <limits.h>
#include <functional>
#include "guid.h"

class OnscreenElement{
    public:
        virtual bool visible() = 0;         /* currently visible?       */
        virtual bool known() = 0;           /* location known?          */
        virtual bool move(int, int) = 0;

        const std::size_t& guid() const { return m_guid; }
        char symbol(){ return m_symbol; }   /* on-screen representation */
        int x(){ return m_x; }              /* location in world-space */
        int y(){ return m_y; }
        int depth(){ return m_depth; }      /* draw order */



    protected:
        OnscreenElement();
        std::size_t m_guid;
        char m_symbol;
        int m_x, m_y;
        int m_depth;
};

inline bool operator<(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs);
inline bool operator>(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs);
inline bool operator<=(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs);
inline bool operator==(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs);
inline bool operator!=(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs);

struct OnscreenElementPtrComp{
    bool operator()(
            const OnscreenElement* lhs,
            const OnscreenElement* rhs) const;
};

#endif /* ONSCREEN_ELEMENT_H */
