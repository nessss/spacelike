#include "player.h"

Player::Player(int x, int y, char symbol, int depth) : 
    Actor(x, y, symbol, depth, OutputAttribute::standout) {}

Player::Player() : Player(0, 0){}

bool Player::visible(){
    /* player is always visible to themself */
    return true; 
}

bool Player::known(){
    /* player is always known to themself */
    return true;
}

bool Player::move(const int deltaX, const int deltaY){
    if(m_zone->tile(m_x + deltaX, m_y + deltaY)->blocksMovement()) return false;
    if(OnscreenElement::move(deltaX, deltaY)){
        Output::getInstance().gameWindowCursorPosition(m_x, m_y);
        return true;
    }
    return false;
}

bool Player::take(){
    for(auto it = m_tile->elements().begin(); it != m_tile->elements().end(); ++it){
        Item* item = dynamic_cast<Item*>(*it);
        if(item != NULL){
            m_tile->removeElement(*it);
            m_inventory.insert(item);
            Output::getInstance().updateInventory(m_inventory);
            Output::getInstance().displayInventory();
            return true;
        }
    }
    return false;
}

void Player::registerActions(){
    using namespace std::placeholders;

    m_actions.emplace_back(this, std::bind(&Player::move, _1, -1,  0), 'h');
    m_actions.emplace_back(this, std::bind(&Player::move, _1,  0,  1), 'j');
    m_actions.emplace_back(this, std::bind(&Player::move, _1,  0, -1), 'k');
    m_actions.emplace_back(this, std::bind(&Player::move, _1,  1,  0), 'l');
    m_actions.emplace_back(this, std::bind(&Player::move, _1, -1, -1), 'y');
    m_actions.emplace_back(this, std::bind(&Player::move, _1,  1, -1), 'u');
    m_actions.emplace_back(this, std::bind(&Player::move, _1, -1,  1), 'b');
    m_actions.emplace_back(this, std::bind(&Player::move, _1,  1,  1), 'n');
    m_actions.emplace_back(this, std::bind(&Player::take, _1), ',');

    Input& input = Input::getInstance();
    for(auto it = m_actions.begin(); it != m_actions.end(); ++it){
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
