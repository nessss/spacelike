#include "player.h"

Player::Player(int x, int y){
    m_symbol = '@';
    m_x = x;
    m_y = y;
    m_depth = 0;
    registerInputs();
}

Player::Player() : Player::Player(0, 0){}

bool Player::visible(){
    /* player is always visible to themself */
    return true; 
}

bool Player::known(){
    /* player is always known to themself */
    return true;
}

bool Player::move(int x, int y){
    return OnscreenElement::move(x, y);
}

void Player::registerInputs(){
    auto moveW  = std::bind(std::mem_fn(&Player::move), -1,  0);
    auto moveS  = std::bind(std::mem_fn(&Player::move),  0,  1);
    auto moveN  = std::bind(std::mem_fn(&Player::move),  0, -1);
    auto moveE  = std::bind(std::mem_fn(&Player::move),  1,  0);
    auto moveNW = std::bind(std::mem_fn(&Player::move), -1, -1);
    auto moveNE = std::bind(std::mem_fn(&Player::move),  1, -1);
    auto moveSW = std::bind(std::mem_fn(&Player::move), -1,  1);
    auto moveSE = std::bind(std::mem_fn(&Player::move),  1,  1);

    Input& input = Input::getInstance();
    input.registerInput(moveW,  'h');
    input.registerInput(moveS,  'j');
    input.registerInput(moveN,  'k');
    input.registerInput(moveE,  'l');
    input.registerInput(moveNW, 'y');
    input.registerInput(moveNE, 'u');
    input.registerInput(moveSW, 'b');
    input.registerInput(moveSE, 'n');
}
