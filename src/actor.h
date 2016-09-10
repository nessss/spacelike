/* Abstract base class for actors, or entities that exist
 * in world space and can interact with their surroundings.
 */

#ifndef __ACTOR_H_INCLUDED__
#define __ACTOR_H_INCLUDED__

class Actor{
    public:
        virtual char repr() = 0; /* on-screen representation */
        virtual int x() = 0;     /* world-space location */ 
        virtual int y() = 0;
};

#endif
