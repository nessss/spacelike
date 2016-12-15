/* Inventory class, representing a collection of items
 */

#ifndef INVENTORY_H
#define INVENTORY_H 

#include <string>
#include <vector>
#include <set>
#include <map>
#include <cctype>
#include <stdexcept>
#include "item.h"
#include "zone.h"

struct InventoryKeyCompare {

    std::map<char, int> keyOrder;

    bool operator()( const char& lhs, const char& rhs ) const
    {
        try
        {
            return keyOrder.at( lhs ) < keyOrder.at( rhs );
        }
        catch( std::out_of_range )
        {
            if( keyOrder.count( rhs ) == 0 )
                return false;

            return true;

        }
    }
};

class Inventory{
    public:
        const char NO_KEY = '\0';
        Inventory( std::vector<char> legalSymbols );
        Inventory( std::string legalSymbols );

        const std::map<char, Item*>& items() const { return m_items; }

        const Item* operator[]( char key ) const;

        bool hasItem( Item* item );
        char key( Item* item );

        char addItem( Item* item, char itemKey='\0' );
        Item* removeItem( Item* item );
        Item* removeItem( char key );

        bool changeKey( char oldKey, char newKey );
        bool changeKey( Item* item, char newKey );

        const unsigned size() const { return m_items.size() ; }

        const std::set<char, InventoryKeyCompare>& legalSymbols() const { return m_keySet; }

        void testPrint( std::string message );

    private:
        const InventoryKeyCompare m_keyOrder;
        const std::set<char, InventoryKeyCompare> m_keySet;

        std::map<char, Item*> m_items;
        std::set<char, InventoryKeyCompare> m_unusedSymbols;

        static const InventoryKeyCompare generateKeyCompare( std::vector<char> keys );
        static const InventoryKeyCompare generateKeyCompare( std::string keys );
};

#endif /* ifndef INVENTORY_H */
