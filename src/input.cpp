#include "input.h"

Input& Input::getInstance(){
    static Input instance;
    return instance;
}

void Input::addAction(InputAction* action){
    m_actions[action->key()].insert(action);
}

void Input::removeAction(InputAction* action){
    m_actions[action->key()].erase(action);
}

/**
 * Process one character from keyboard input, and take appropriate action.
 * @param c The character to process
 */
void Input::processInput(){
    char c = (char)getch();
    for(auto it = m_actions[c].begin(); it != m_actions[c].end(); ++it){
        (**it)();
    }
}
