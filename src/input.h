/* Input handling. */

#ifndef INPUT_H
#define INPUT_H 

#include <curses.h>
#include "actor.h"
#include "output.h"

class Input{
    public:
        static Input& getInstance();
        void processInput();

        Actor* focusedActor();
        Actor* focusedActor(Actor *actor);

    private:
        Input(){};
        ~Input(){};
        Actor* m_focusedActor;
        Output &m_output = Output::getInstance();
};

#endif /* ifndef INPUT_H */
