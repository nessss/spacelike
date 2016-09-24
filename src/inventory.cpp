#include "inventory.h"

const Item* Inventory::operator[](unsigned index) const {
    const Item* item = m_items.at(index);
    return item;
}

Item* Inventory::operator[](unsigned index){
    return m_items.at(index);
}
