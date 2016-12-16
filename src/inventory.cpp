#include "inventory.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

Inventory::Inventory( std::vector<char> keyOrder ) :
    m_keyCompare( generateKeyCompare( keyOrder ) ),
    m_sortCompare( defaultSortCompare( m_keyCompare ) ),
    m_keySet( keyOrder.cbegin(), keyOrder.cend(), m_keyCompare ),
    m_unusedSymbols( keyOrder.cbegin(), keyOrder.cend(), m_keyCompare ){}

Inventory::Inventory( std::string keyOrder ) :
    m_keyCompare( generateKeyCompare( keyOrder ) ),
    m_sortCompare( defaultSortCompare( m_keyCompare ) ),
    m_keySet( keyOrder.cbegin(), keyOrder.cend(), m_keyCompare ),
    m_unusedSymbols( keyOrder.cbegin(), keyOrder.cend(), m_keyCompare ){}

const Item* Inventory::operator[]( char key ) const
{
    if( m_items.count( key ) == 0 )
        return NULL;

    return m_items.at( key );
}

const Item* Inventory::operator[]( int index ) const
{
    if( index >= m_sorted.size() )
        return NULL;

    int i = 0;

    for( auto sortedPair : m_sorted )
    {
        if( i++ == index )
        {
            return sortedPair.second;
        }
    }

    return NULL;
}

bool Inventory::hasItem( Item* item )
{
    return key( item ) != NO_KEY;
}

char Inventory::key( Item* item )
{
    for( auto pair = m_items.begin(); pair != m_items.end(); ++pair )
    {
        if( pair->second == item )
            return pair->first;
    }

    return NO_KEY;
}

char Inventory::addItem( Item* item, char itemKey )
{

    char key;
    if( m_unusedSymbols.count( itemKey ) == 1 )
    {
        key = itemKey;
    }
    else
    {
        key = *( m_unusedSymbols.begin() );
    }

    m_items.insert( std::pair<char, Item*>( key, item ) );

    m_unusedSymbols.erase( key );

    return key;
}

Item* Inventory::removeItem( Item* itemToRemove )
{
    char removalKey = key( itemToRemove );

    return removeItem( removalKey );
}

Item* Inventory::removeItem( char removalKey )
{
    try
    {
        Item* item = m_items.at( removalKey );
        m_items.erase( removalKey );
        m_unusedSymbols.insert( removalKey );
        return item;
    }
    catch( std::out_of_range )
    {
        return NULL;
    }
}

bool Inventory::changeKey( char oldKey, char newKey )
{
    if( m_items.count( oldKey ) == 0 )
        return false;

    if( m_keySet.count( newKey ) == 0 )
        return false;

    Item* oldKeyItem = m_items[ oldKey ];
    removeItem( oldKey );

    if( m_items.count( newKey ) == 1 )
    {
        Item* newKeyItem = m_items[ newKey ];
        removeItem( newKey );
        addItem( newKeyItem, oldKey );
    }

    addItem( oldKeyItem, newKey );

    return true;
}

bool Inventory::changeKey( Item* item, char newKey )
{
    return changeKey( key( item ), newKey );
}


const InventoryKeyCompare Inventory::generateKeyCompare( std::string keyOrder )
{
    InventoryKeyCompare compare;

    for( auto key : keyOrder )
    {
        compare.keyOrder[ key ] = compare.keyOrder.size();
    }

    return compare;
}

const InventoryKeyCompare Inventory::generateKeyCompare( std::vector<char> keyOrder )
{
    InventoryKeyCompare compare;

    for( auto key : keyOrder )
    {
        compare.keyOrder[ key ] = compare.keyOrder.size();
    }

    return compare;
}

const InventorySortCompare Inventory::defaultSortCompare( InventoryKeyCompare keyCompare )
{
    InventorySortCompare compare;
    compare.keyCompare = keyCompare;

    compare.itemGroupOrder.insert( std::pair< Item::Group, int >( Item::Group::Weapon, 0 ) );
    compare.itemGroupOrder.insert( std::pair< Item::Group, int >( Item::Group::Equipment, 1 ) );
    compare.itemGroupOrder.insert( std::pair< Item::Group, int >( Item::Group::Tool, 2 ) );
    compare.itemGroupOrder.insert( std::pair< Item::Group, int >( Item::Group::Consumable, 3 ) );
    compare.itemGroupOrder.insert( std::pair< Item::Group, int >( Item::Group::Craftable, 4 ) );
    compare.itemGroupOrder.insert( std::pair< Item::Group, int >( Item::Group::Quest, 5 ) );
    compare.itemGroupOrder.insert( std::pair< Item::Group, int >( Item::Group::None, 6 ) );

    return compare;
}
