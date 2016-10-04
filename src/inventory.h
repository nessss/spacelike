/* Inventory class, representing an actor's inventory
 */

#ifndef INVENTORY_H
#define INVENTORY_H 

#include <string>
#include <vector>
#include <set>
#include "item.h"
#include "zone.h"

class Inventory{
    public:

        std::vector< std::pair<char, Item*> > items();
        std::vector< std::pair<char, Item*> > itemsAt(Tile* location);

        bool addItem(Item* item);
        bool removeItem(Item* item);

        const unsigned size() const;

    private:
        std::set<Item*> itemsFromElements(std::set<OnscreenElement*> elements);

        std::vector< std::pair<char, Item*> > m_items;
        const std::string legalSymbols;
        std::set<char> unusedSymbols;
};

#endif /* ifndef INVENTORY_H */
