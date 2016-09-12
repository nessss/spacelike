/* Abstract base class for environment elements,
 * i.e. semi-permament parts of a zone.
 */

#ifndef __ENVIRONMENT_H_ADDED__
#define __ENVIRONMENT_H_ADDED__

#include "onscreen_element.h"

class EnvironmentElement : public OnscreenElement{
    public:
        virtual bool blocksMovement() = 0;
};

#endif
