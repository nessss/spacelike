/* Player class, representing a user-controllerable
 * player character.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <functional>
#include "onscreen_element.h"
#include "actor.h"

class Player : public Actor {
    public:
        Player();
        Player(int, int);
        bool visible();
        bool known();
        bool move(int, int);

    private:
        void registerInputs();
};

#endif /* PLAYER_H */
