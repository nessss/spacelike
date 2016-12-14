#include "inventory.h"
#include <algorithm>
#include <iostream>
#include <iterator>

Inventory::Inventory( std::vector<char> legalSymbols )
{
    m_legalSymbols = std::vector<char>( legalSymbols );
}

Inventory::Inventory( std::string legalSymbols )
{
    m_legalSymbols = std::vector<char>(
            legalSymbols.begin(),
            legalSymbols.end() );

}

template <typename Container>
std::map<char, Item*> Inventory::viewItems(
        Container<Item*>::iterator<Item*> begin,
        Container<Item*>::iterator<Item*> end )
{
    std::map<char, Item*> result;

    auto symbol = m_legalSymbols.cbegin();

    for( auto item = begin; item != end; )
    {
        result.insert( *symbol, *item );
        ++symbol;
        ++item;
    }

    return result;
}

bool Inventory::addItem( Item* item )
{
    std::set<Item*> locationItems = item->tile()->items();

    if( locationItems.count( item ) == 1 )
    {
        m_items.insert( std::pair<char, Item*>( 'a', item ) );
        item->zone()->tile( item )->removeElement( item );
        item->zone( NULL );
    }
    return true;
}
