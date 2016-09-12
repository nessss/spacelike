/* Input handling. */

#ifndef INPUT_H
#define INPUT_H 

#include <curses.h>
#include "actor.h"
#include "output.h"

class Input{
    public:
        void processInput();

        Actor* focusedActor(){ return m_focusedActor; }
        void setFocusedActor(Actor *actor){ m_focusedActor = actor; }

    private:
        Actor *m_focusedActor;
        Output &m_output = Output::getInstance();
};

#endif /* ifndef INPUT_H */
