#include "input.h"

void Input::processInput(){
    char c = (char)getch();
    if(m_focusedActor == 0) return;
    switch(c){
        case 'h':
            m_focusedActor->move(-1, 0);
            break;
        case 'j':
            m_focusedActor->move(0, 1);
            break;
        case 'k':
            m_focusedActor->move(0, -1);
            break;
        case 'l':
            m_focusedActor->move(1, 0);
            break;
        case 'y':
            m_focusedActor->move(-1, -1);
            break;
        case 'u':
            m_focusedActor->move(1, -1);
            break;
        case 'b':
            m_focusedActor->move(-1, 1);
            break;
        case 'n':
            m_focusedActor->move(1, 1);
            break;
    }
}
