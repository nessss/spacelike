#include "inventory.h"


bool Inventory::addItem(Item* item){
    std::set<Item*> locationItems = itemsFromElements(item->zone()->tile(item)->elements());


    if(locationItems.count(item) == 1){
        m_items.push_back(std::pair<char, Item*>('a', item));
        item->zone()->tile(item)->removeElement(item);
    }
    return true;
}

std::set<Item*> Inventory::itemsFromElements(std::set<OnscreenElement*> elements){
    std::set<Item*> result;
    for(auto it = elements.begin(); it != elements.end(); ++it){
        Item* locationItem = dynamic_cast<Item*>(*it);
        if(locationItem != NULL) result.insert(locationItem);
    }
    
    return result;
}
