/* Player class, representing a user-controllerable
 * player character.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "onscreen_element.h"
#include "actor.h"

class Player : public Actor {
    public:
        Player();
        Player(int, int);
        bool visible();
        bool known();
        int move(int, int);
};

#endif /* PLAYER_H */
