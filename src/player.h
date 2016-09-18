/* Player class, representing a user-controllerable
 * player character.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <functional>
#include "onscreen_element.h"
#include "actor.h"
#include "input.h"

/* forward declaration */
class PlayerInputAction;

class Player : public Actor {
    public:
        Player();
        Player(int, int, char symbol = '@', int depth = 0);
        bool visible();
        bool known();
        bool move(int, int);
    private:
        void registerActions();
        std::vector<PlayerInputAction> actions;
};

class PlayerInputAction : public InputAction{
    public:
        PlayerInputAction(Player* player, std::function<bool(Player*)> fun, char key);
        void operator()();
    private:
        Player* m_player;
        std::function<bool(Player*)> m_fun;
};

#endif /* PLAYER_H */
