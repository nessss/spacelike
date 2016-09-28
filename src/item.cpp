#include "item.h"

Item::Item(string name, string description) : 
    OnscreenElement(0, 0, '%', 10, OutputAttribute::normal),
    m_name(name),
    m_description(description) {}

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
