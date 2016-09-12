/* Input handling. */

#include "actor.h"

class Input{
  public:
    void processInput(int);

    Actor* focusedActor(){ return m_focusedActor; }
    void setFocusedActor(Actor *actor){ m_focusedActor = actor; }

  private:
    Actor *m_focusedActor;
};
