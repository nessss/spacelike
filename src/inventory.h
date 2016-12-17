/* Inventory class, representing a collection of items
 */

#ifndef INVENTORY_H
#define INVENTORY_H 

#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include "item.h"
#include "zone.h"

struct InventoryKeyCompare
{
    std::map<char, int> keyOrder;

    bool operator()( const char& lhs, const char& rhs ) const
    {
        try
        {
            return keyOrder.at( lhs ) < keyOrder.at( rhs );
        }
        catch( std::out_of_range )
        {
            if( keyOrder.count( rhs ) != 0 )
                return false;

            return true;

        }
    }
};

struct InventorySortCompare
{
    std::map< Item::Group, int > itemGroupOrder;
    InventoryKeyCompare keyCompare;

    // return true if lhs goes before rhs
    bool operator()(
            const std::pair< char, Item* >& lhs,
            const std::pair< char, Item* >& rhs ) const
    {
        int lhsGroupIndex, rhsGroupIndex;
        try
        {
            lhsGroupIndex = itemGroupOrder.at( lhs.second->group() );
            rhsGroupIndex = itemGroupOrder.at( rhs.second->group() );
            
            if( lhsGroupIndex == rhsGroupIndex )
            {
                return keyCompare( lhs.first, rhs. first );
            }
            else
            {
                return ( lhsGroupIndex < rhsGroupIndex );
            }
        }

        catch( std::out_of_range )
        {
            bool lhsGroupMissing = itemGroupOrder.count( lhs.second->group() );
            bool rhsGroupMissing = itemGroupOrder.count( rhs.second->group() );
            if( lhsGroupMissing )
            {
                if( rhsGroupMissing )
                {
                    return keyCompare( lhs.first, rhs.first );
                }

                return false;
            }
            return true;
        }
    }
};

class Inventory{
    public:
        const char NO_KEY = '\0';
        Inventory( std::vector<char> legalSymbols );
        Inventory( std::string legalSymbols );


        const std::map< char, Item* >& items() const { return m_items; }
        const std::list< std::pair< char, Item* > >& sorted() const { return m_sorted; }

        const Item* operator[]( char key ) const;
        const Item* operator[]( int index ) const;

        bool hasItem( Item* item );
        char key( Item* item );

        char addItem( Item* item, char itemKey='\0' );

        template <typename Iterator>
        std::vector< char > addItems( Iterator begin, Iterator end )
        {
            std::vector< char > result;

            Iterator item = begin;
            while( item != end )
            {
                result.push_back( addItem( *item++ ) );
            }

            return result;
        }

        Item* removeItem( Item* item );
        Item* removeItem( char key );

        bool changeKey( char oldKey, char newKey );
        bool changeKey( Item* item, char newKey );

        const unsigned size() const { return m_items.size() ; }

        const InventoryKeyCompare& keyOrder() const { return m_keyCompare; }
        const std::set<char, InventoryKeyCompare>& legalSymbols() const { return m_keySet; }

    private:
        const InventoryKeyCompare m_keyCompare;
        const InventorySortCompare m_sortCompare;
        const std::set<char, InventoryKeyCompare> m_keySet;

        std::map< char, Item* > m_items;
        std::list< std::pair< char, Item* > > m_sorted;
        std::set< char, InventoryKeyCompare > m_unusedSymbols;

        static const InventoryKeyCompare generateKeyCompare( std::vector<char> keys );
        static const InventoryKeyCompare generateKeyCompare( std::string keys );

        static const InventorySortCompare defaultSortCompare( InventoryKeyCompare keyCompare );
};

#endif /* ifndef INVENTORY_H */
