#include "input.h"

Input::Input(){}

void Input::processInput(){
    char c = (char)getch();
    if(m_focusedActor == 0) return;
    switch(c){
        case 'h':
            m_focusedActor->move(-1, 0);
            m_output.setGameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'j':
            m_focusedActor->move(0, 1);
            m_output.setGameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'k':
            m_focusedActor->move(0, -1);
            m_output.setGameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'l':
            m_focusedActor->move(1, 0);
            m_output.setGameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'y':
            m_focusedActor->move(-1, -1);
            m_output.setGameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'u':
            m_focusedActor->move(1, -1);
            m_output.setGameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'b':
            m_focusedActor->move(-1, 1);
            m_output.setGameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case 'n':
            m_focusedActor->move(1, 1);
            m_output.setGameWindowCursorPosition(
                    m_focusedActor->x(),
                    m_focusedActor->y());
            break;
        case '0':
            m_output.setGameWindowCursorPosition(
                    0, 0);
            break;
    }
}
