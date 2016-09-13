#include "player.h"

Player::Player(int x, int y){
    m_symbol = '@';
    m_x = x;
    m_y = y;
    m_depth = 0;
}

Player::Player(){
    m_symbol = '@';
    m_x = 0;
    m_y = 0;
    m_depth = 0;
}

bool Player::visible(){
    /* player is always visible to themself */
    return true; 
}

bool Player::known(){
    /* player is always known to themself */
    return true;
}

bool Player::move(int x, int y){
    if(m_x + x < 0){ return false; }
    if(m_y + y < 0){ return false; }
    m_x += x;
    m_y += y;
    return true;
}
