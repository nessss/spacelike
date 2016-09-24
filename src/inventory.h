/* Inventory class, representing an actor's inventory
 */

#ifndef INVENTORY_H
#define INVENTORY_H 

#include <vector>
#include "item.h"

class Inventory{
    public:
        const Item* operator[](unsigned index) const;
        Item* operator[](unsigned index);

        const unsigned size() const;

    private:
        std::vector<Item*> m_items;
};

#endif /* ifndef INVENTORY_H */
