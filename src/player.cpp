#include "player.h"

Player::Player(int x, int y){
    m_repr = '@';
    m_x = x;
    m_y = y;
}

Player::Player(){
    m_repr = '@';
    m_x = 0;
    m_y = 0;
}

char Player::repr(){
    return m_repr;
}

int Player::x(){
    return m_x;
}

int Player::y(){
    return m_y;
}

int Player::move(int x, int y){
    if(m_x + x < 0){ return 1; }
    if(m_y + y < 0){ return 1; }
    m_x += x;
    m_y += y;
}

void Player::process_input(int c){
    switch((char)c){
        case 'h':
            move(-1, 0);
            break;
        case 'j':
            move(0, 1);
            break;
        case 'k':
            move(0, -1);
            break;
        case 'l':
            move(1, 0);
            break;
        case 'y':
            move(-1, -1);
            break;
        case 'u':
            move(1, -1);
            break;
        case 'b':
            move(-1, 1);
            break;
        case 'n':
            move(1, 1);
            break;
    }
}

void Player::refresh(){
    mvaddch(m_y, m_x, m_repr);
}
