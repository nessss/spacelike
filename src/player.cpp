#include "player.h"

Player::Player(int x, int y, char symbol, int depth){
    m_x = x;
    m_y = y;
    m_symbol = symbol;
    m_depth = depth;

    registerActions();
}

Player::Player() : Player(0, 0){}

bool Player::visible(){
    /* player is always visible to themself */
    return true; 
}

bool Player::known(){
    /* player is always known to themself */
    return true;
}

bool Player::move(const int x, const int y){
    if(OnscreenElement::move(x, y)){
        int currentX, currentY;
        Output::getInstance().gameWindowCursorPosition(&currentX, &currentY);
        const int newX = currentX + x;
        const int newY = currentY + y;
        Output::getInstance().gameWindowCursorPosition(newX, newY);
        return true;
    }
    return false;
}

void Player::registerActions(){
    using namespace std::placeholders;

    actions.emplace_back(this, std::bind(&Player::move, _1, -1,  0), 'h');
    actions.emplace_back(this, std::bind(&Player::move, _1,  0,  1), 'j');
    actions.emplace_back(this, std::bind(&Player::move, _1,  0, -1), 'k');
    actions.emplace_back(this, std::bind(&Player::move, _1,  1,  0), 'l');
    actions.emplace_back(this, std::bind(&Player::move, _1, -1, -1), 'y');
    actions.emplace_back(this, std::bind(&Player::move, _1,  1, -1), 'u');
    actions.emplace_back(this, std::bind(&Player::move, _1, -1,  1), 'b');
    actions.emplace_back(this, std::bind(&Player::move, _1,  1,  1), 'n');

    Input& input = Input::getInstance();
    for(auto it = actions.begin(); it != actions.end(); ++it){
        input.addAction(&(*it));
    }
}

PlayerInputAction::PlayerInputAction(Player* player, std::function<bool(Player*)> fun, char key){
    m_player = player;
    m_fun = fun;
    m_key = key;
}

void PlayerInputAction::operator()(){
    m_fun.operator()(m_player);
}
