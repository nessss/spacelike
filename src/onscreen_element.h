/* Abstract base class for elements that can be
 * printed to the screen.
 */

#ifndef __ONSCREEN_ELEMENT_H_ADDED__
#define __ONSCREEN_ELEMENT_H_ADDED__

class OnscreenElement{
    public:
        virtual char repr() = 0;   /* on-screen representation */
        virtual bool visible() = 0; /* currently visible? */
        virtual bool known() = 0;
        virtual int x() = 0;
        virtual int y() = 0;
};

#endif
