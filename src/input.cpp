#include "input.h"

Input& Input::getInstance(){
    static Input instance;
    return instance;
}

/**
 * Process one character from keyboard input, and take appropriate action.
 * @param c The character to process
 */
void Input::processInput(){
    char c = (char)getch();
    if(m_focusedActor == 0) return;
    switch(c){
        case 'h':
            m_focusedActor->move(-1, 0);
            m_output.gameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'j':
            m_focusedActor->move(0, 1);
            m_output.gameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'k':
            m_focusedActor->move(0, -1);
            m_output.gameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'l':
            m_focusedActor->move(1, 0);
            m_output.gameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'y':
            m_focusedActor->move(-1, -1);
            m_output.gameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'u':
            m_focusedActor->move(1, -1);
            m_output.gameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'b':
            m_focusedActor->move(-1, 1);
            m_output.gameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'n':
            m_focusedActor->move(1, 1);
            m_output.gameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case '0':
            m_output.gameWindowCursorPosition(
                    0, 0);
            break;
    }
}

/**
 * Get pointer to actor over which player has active control.
 * @retval Actor* Focused `Actor*`
 */
Actor* Input::focusedActor(){
    return m_focusedActor; 
}

/**
 * Set actor over which player has active control.
 * @param actor `Actor*` to be focused
 * @retval Actor* Newly focused `Actor*`
 */
Actor* Input::focusedActor(Actor* actor){
    m_focusedActor = actor; 
    return m_focusedActor;
}
