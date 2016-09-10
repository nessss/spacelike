/* Player class, representing a user-controllerable
 * player character.
 */

#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include <ncurses.h>
#include "onscreen_element.h"

class Player : OnscreenElement{
    public:
        Player();
        Player(int, int);

        char repr();
        bool visible();
        bool known();
        int x();
        int y();

        int move(int,int);

        void process_input(int);
        void refresh();
    private:
        char m_repr;
        int m_x, m_y;
};

#endif
