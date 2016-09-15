/** Abstract base class for environment elements.
 * Represents semi-permament parts of a zone.
 */

#ifndef __ENVIRONMENT_H_ADDED__
#define __ENVIRONMENT_H_ADDED__

#include "onscreen_element.h"

class EnvironmentElement : public OnscreenElement{
    protected:
        /**
         * Check if this blocks movement
         * @retval bool `true` if this blocks movement, `false` otherwise
         */
        virtual bool blocksMovement() = 0;
};

#endif
