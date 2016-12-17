#include "item.h"

Item::Item(
        string name,
        string description,
        Item::Group group,
        int weight,
        int value ) : 
    OnscreenElement( 0, 0, '%', 10, OutputAttribute::normal ),
    m_name( name ),
    m_description( description ),
    m_group( group ),
    m_weight( weight ),
    m_value( value ) {}

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
