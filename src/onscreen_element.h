/**
 * Abstract base class for elements that can be printed to the screen.
 */

#ifndef ONSCREEN_ELEMENT_H
#define ONSCREEN_ELEMENT_H

#include <limits.h>
#include <functional>
#include "guid.h"

class Zone;
class OnscreenElement{
    public:
        //! @return `true` if the element is visible
        virtual bool visible() = 0;
        //! @return `true` if the element location is known
        virtual bool known() = 0;
        //! @return `true` if the element successfully moved relative to its current location
        virtual bool move(int, int);

        //! Return unique ID for this element
        std::size_t id() const { return m_id; }
        //! Return on-screen representation
        char symbol() const { return m_symbol; }
        //! Return X coordinate in world space
        int x() const { return m_x; }
        //! Return Y coordinate in world space
        int y() const { return m_y; }
        //! Return draw order depth of element
        int depth() const { return m_depth; }

        Zone* zone() const { return m_zone; } //!< Get current zone
        Zone* zone(Zone* zone){ m_zone = zone; return m_zone; } //!< Set current zone


    protected:
        //! Constructor
        OnscreenElement();
        //! Unique ID
        std::size_t m_id;
        //! On-screen representation
        char m_symbol;
        //@{
        /// World space coordinate
        int m_x, m_y;
        //@}
        //! Draw order depth
        int m_depth;

        Zone* m_zone;
};


/** 
 *  @param lhs an OnscreenElement
 *  @param rhs an OnscreenElement
 *  @return `true` if `lhs.id()` is less than `rhs.id(),` `false` otherwise
 */ 
inline bool operator<(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return lhs.id() < rhs.id();
}

/** 
 *  @param lhs an OnscreenElement
 *  @param rhs an OnscreenElement
 *  @return `true` if `lhs.id()` is greater than `rhs.id(),` `false` otherwise
 */ 
inline bool operator>(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return rhs < lhs;
}

/** 
 *  @param lhs an OnscreenElement
 *  @param rhs an OnscreenElement
 *  @return `true` if `lhs.id()` is less than or equal to `rhs.id(),` `false` otherwise
 */ 
inline bool operator<=(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return !(lhs > rhs);
}

/** 
 *  @param lhs an OnscreenElement
 *  @param rhs an OnscreenElement
 *  @return `true` if `lhs.id()` is greater than or equal to `rhs.id(),` `false` otherwise
 */ 
inline bool operator>=(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return !(lhs < rhs);
}

/** 
 *  @param lhs an OnscreenElement
 *  @param rhs an OnscreenElement
 *  @return `true` if `lhs.id()` is equal to `rhs.id(),` `false` otherwise
 */ 
inline bool operator==(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return lhs.id() == rhs.id();
}

/** 
 *  @param lhs an OnscreenElement
 *  @param rhs an OnscreenElement
 *  @return `true` if `lhs.id()` is not equal to `rhs.id(),` `false` otherwise
 */ 
inline bool operator!=(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return !(lhs.id() == rhs.id());
}

//! Functor for ID comparison
struct OnscreenElementPtrGuidComp{
    /**
     * @param[in] lhs, rhs OnscreenElements to be compared by `id()`
     * @return `true` if `lhs.id()` is less than `rhs.id()`, `false` otherwise
     */
    bool operator()(
            const OnscreenElement* lhs,
            const OnscreenElement* rhs) const {
        return *lhs < *rhs;
    }
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
