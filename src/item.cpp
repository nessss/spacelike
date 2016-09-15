#include "item.h"

Item::Item(string name, string description){
    m_name = name;
    m_description = description;
    m_depth = 10;
    m_symbol = '%';
}

bool Item::visible(){
    // TODO: implement
    return true;
}

bool Item::known(){
    // TODO: implement
    return true;
}

bool Item::move(int x, int y){
    return OnscreenElement::move(x, y);
}
