/**
 * Abstract base class for elements that can be printed to the screen.
 */

#ifndef ONSCREEN_ELEMENT_H
#define ONSCREEN_ELEMENT_H

#include <limits.h>
#include <functional>
#include "output_attribute.h"

class Zone;
class Tile;

class OnscreenElement{
    public:
        //! @return `true` if the element is visible
        virtual bool visible() = 0;

        //! @return `true` if the element location is known
        virtual bool known() = 0;

        //! @return `true` if the element successfully moved relative to its current location
        virtual bool move(int, int);

        //! Peek at the symbol (don't set the m_symbolSeen flag)
        virtual char peekSymbol() const { return m_symbol; }

        //! Return on-screen representation and make symbolSeen() return `true` until moved
        virtual char getSymbol() { m_symbolSeen = true; return m_symbol; }

        //! Set the symbol
        virtual char symbol(char newSymbol){ m_symbol = newSymbol; return m_symbol; }

        //! @retval bool `true` if the element has been seen in its current location
        bool symbolSeen() const { return m_symbolSeen; }
        bool symbolSeen(bool seen){ m_symbolSeen = seen; return m_symbolSeen; }

        //! Return X coordinate in world space
        int x() const { return m_x; }
        int x(int x){ m_x = x; return m_x; }

        //! Return Y coordinate in world space
        int y() const { return m_y; }
        int y(int y){ m_y = y; return m_y; }

        //! Return draw order depth of element
        int depth() const { return m_depth; }
        int depth(int newDepth){ m_depth = newDepth; return m_depth; }

        const char* attribute() const { return m_attribute; }
        const char* attribute(const char* attribute){ m_attribute = attribute; return m_attribute; }

        Zone* zone() const { return m_zone; } //!< Get current zone
        Zone* zone(Zone* zone){ m_zone = zone; return m_zone; } //!< Set current zone
        
        Tile* tile() const { return m_tile; } //!< Set current tile
        Tile* tile(Tile* tile){ m_tile = tile; return m_tile; } //!< Get current tile

    protected:
        //! Constructor
        OnscreenElement();

        //! On-screen representation
        char m_symbol;

        //! Whether the symbol has been seen in its current location
        bool m_symbolSeen;

        //@{
        /// World space coordinate
        int m_x, m_y;
        //@}

        //! Draw order depth
        int m_depth;

        //! symbol attribute
        const char* m_attribute;

        Zone* m_zone;
        Tile* m_tile;
};

//! Functor for depth comparison
struct OnscreenElementPtrDepthComp{
    /**
     * Compares two OnscreenElements by depth
     * @param[in] lhs, rhs OnscreenElements to be compared by `depth()`
     * @return `true` if `lhs.depth()` is less than `rhs.depth()`, `false` otherwise
     */
    bool operator()(
            const OnscreenElement* lhs,
            const OnscreenElement* rhs) const {
        return lhs->depth() < rhs->depth();
    }
};

#endif /* ONSCREEN_ELEMENT_H */
