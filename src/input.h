/* Input handling. */

#include "actor.h"
#include <curses.h>

class Input{
  public:
    void processInput();

    Actor* focusedActor(){ return m_focusedActor; }
    void setFocusedActor(Actor *actor){ m_focusedActor = actor; }

  private:
    Actor *m_focusedActor;
};
