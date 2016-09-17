/* Input handling. */

#ifndef INPUT_H
#define INPUT_H 

#include <curses.h>
#include <functional>
#include <unordered_map>
#include "actor.h"
#include "output.h"

class Input{
    public:
        static Input& getInstance();
        void processInput();

        bool registerFunction(std::function<void> fn, char input);

        Actor* focusedActor();
        Actor* focusedActor(Actor *actor);

    private:
        Input(){};
        Input(Input&){};
        void operator=(Input const&);

        std::unordered_multimap<char, void*> m_inputMap;
        std::unordered_multimap<char, OnscreenElement*> m_inputMap;
        Actor* m_focusedActor;
        Output &m_output = Output::getInstance();
};

#endif /* ifndef INPUT_H */
