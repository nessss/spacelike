/* Inventory class, representing an actor's inventory
 */

#ifndef INVENTORY_H
#define INVENTORY_H 

#include <string>
#include <vector>
#include <set>
#include <map>
#include "item.h"
#include "zone.h"

class Inventory{
    public:
        Inventory( std::vector<char> legalSymbols );
        Inventory( std::string legalSymbols );

        std::map<char, Item*> items();

        template <typename Container>
        std::map<char, Item*> viewItems(
                Container<Item*>::iterator begin,
                Container<Item*>::iterator end );

        bool addItem(Item* item);
        bool removeItem(Item* item);

        const unsigned size() const;

        const std::vector<char>& legalSymbols() const { return m_legalSymbols; }

        void testPrint( std::string message );

    private:
        std::vector<char> m_legalSymbols;

        std::set<Item*> itemsFromElements(std::set<OnscreenElement*> elements);

        std::map<char, Item*> m_items;
        std::set<char> unusedSymbols;
};

#endif /* ifndef INVENTORY_H */
