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

        std::size_t guid() const { return m_guid; }
        char symbol() const { return m_symbol; }   /* on-screen representation */
        int x() const { return m_x; }              /* location in world-space */
        int y() const { return m_y; }
        int depth() const { return m_depth; }      /* draw order */

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

struct OnscreenElementPtrGuidComp{
    bool operator()(
            const OnscreenElement* lhs,
            const OnscreenElement* rhs) const;
};

struct OnscreenElementPtrDepthComp{
    bool operator()(
            const OnscreenElement* lhs,
            const OnscreenElement* rhs) const;
};

#endif /* ONSCREEN_ELEMENT_H */
