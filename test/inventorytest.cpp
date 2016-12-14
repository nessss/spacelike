#include <iostream>
#include <vector>
#include <string>
#include "catch.hpp"
#include "../src/inventory.h"
#include "../src/tile.h"
#include "../src/item.h"

std::string testLegalSymbolsString = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
auto testLegalSymbolsVector = std::vector<char>(
        testLegalSymbolsString.cbegin(),
        testLegalSymbolsString.cend() );

TEST_CASE( "Inventory is constructed", "[InventoryConstructor]" )
{
    SECTION( "Legal symbols are as expected" )
    {
        Inventory vectorInventory( testLegalSymbolsString );
        Inventory stringInventory( testLegalSymbolsVector );

        REQUIRE( vectorInventory.legalSymbols() == testLegalSymbolsVector );
        REQUIRE( stringInventory.legalSymbols() == testLegalSymbolsVector );
    }
}

TEST_CASE( "Inventory::viewItems works as expected", "[InventoryViewItems]" )
{
    Inventory inventory( testLegalSymbolsString );
    std::set<Item*> items;

    Item slimeMold( "Slime mold", "a delicious, nutritious dungeon staple" );
    Item fluxCapacitor( "Flux capacitor", "the key to the secrets of the universe" );
    Item macGuffin( "MacGuffin", "a mysterious golden glow emanates from this briefcase" );

    items.insert( &slimeMold );
    items.insert( &fluxCapacitor );
    items.insert( &macGuffin );

    std::map<char, Item*> itemView = inventory.viewItems( items.begin(), items.end() );

    SECTION( "appropriate number of items are in viewItems map" )
    {
        REQUIRE( itemView.size() == items.size() );
    }

    SECTION( "items in viewItems map have appropriate keys" )
    {
        auto setItem = items.cbegin();

        REQUIRE( itemView['a'] == *setItem++ );
        REQUIRE( itemView['b'] == *setItem++ );
        REQUIRE( itemView['c'] == *setItem );
    }
}
