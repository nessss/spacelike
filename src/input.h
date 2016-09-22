/* Input handling. */

#ifndef INPUT_H
#define INPUT_H 

#include <map>
#include <curses.h>
#include "actor.h"
#include "output.h"

class InputAction{
    public:
        virtual void operator()() = 0;
        char key(){return m_key;}
    protected:
        char m_key;
};

class Input{
    public:
        static Input& getInstance();
        void processInput();
        void addAction(InputAction* action);
        void removeAction(InputAction* action);

    private:
        Input(){};
        ~Input(){};
        std::map<char, std::set<InputAction*>> m_actions;
        Output &m_output = Output::getInstance();
};

#endif /* ifndef INPUT_H */
