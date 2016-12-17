#include <iostream>
#include <vector>
#include <string>
#include <array>
#include "catch.hpp"
#include "../src/inventory.h"
#include "../src/tile.h"
#include "../src/item.h"

std::string legalSymbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
auto legalSymbolsVector = std::vector<char>(
        legalSymbols.cbegin(),
        legalSymbols.cend() );

TEST_CASE( "Inventory constructor", "[Inventory]" )
{

    SECTION( "string" )
    {
        Inventory* inventory_ptr;
        REQUIRE_NOTHROW( inventory_ptr = new Inventory( legalSymbols ) );
        Inventory& inventory = *inventory_ptr;

        auto testKey = legalSymbols.cbegin();
        auto objectKey = inventory.legalSymbols().cbegin();

        while(
                testKey != legalSymbols.cend() &&
                objectKey != inventory.legalSymbols().cend() )
        {
            CHECK( *testKey++ == *objectKey++ );
        }
    }

    SECTION( "string alternate" )
    {
        std::string testString = "!@#$%^&*~12aqwuxjz";
        Inventory* inventory_ptr;
        REQUIRE_NOTHROW( inventory_ptr = new Inventory( testString ) );
        Inventory& inventory = *inventory_ptr;

        auto testKey = testString.cbegin();
        auto objectKey = inventory.legalSymbols().cbegin();

        while(
                testKey != testString.cend() &&
                objectKey != inventory.legalSymbols().cend() )
        {
            CHECK( *testKey++ == *objectKey++ );
        }
    }

    SECTION( "vector" )
    {
        Inventory* inventory_ptr;
        REQUIRE_NOTHROW( inventory_ptr = new Inventory( legalSymbolsVector ) );
        Inventory& inventory = *inventory_ptr;

        auto testKey = legalSymbolsVector.cbegin();
        auto objectKey = inventory.legalSymbols().cbegin();

        while(
                testKey != legalSymbols.cend() &&
                objectKey != inventory.legalSymbols().cend() )
        {
            CHECK( *testKey++ == *objectKey++ );
        }
    }
}

TEST_CASE( "adding and removing items", "[Inventory]" )
{
    Inventory inventory( legalSymbols );

    Item slimeMold(
            "Slime mold",
            "a delicious, nutritious dungeon staple",
            Item::Group::Consumable );


    Item fluxCapacitor( "Flux capacitor",
		    "the key to the secrets of the universe",
		    Item::Group::Craftable );

    Item macGuffin( "MacGuffin",
		    "a mysterious golden glow emanates from this briefcase",
		    Item::Group::Quest );

    Item masterSword(
            "Master sword",
            "a famous blade that can be wielded only by those with great courage",
            Item::Group::Weapon );

    Item exosuit(
            "Exosuit",
            "Powered armor and weapons platform",
            Item::Group::Equipment );


    std::array< Item*, 5 > testItems
    { {
        &slimeMold,
        &fluxCapacitor,
        &macGuffin,
        &masterSword,
        &exosuit
    } };

    char slimeKey, fluxKey, macKey, swordKey, exoKey;

    std::array< char*, 5 > testKeys
    { {
        &slimeKey,
        &fluxKey,
        &macKey,
        &swordKey,
        &exoKey
    } };

    SECTION( "adding items" )
    {
        SECTION( "add range of items" )
        {
            std::vector< char >* keys;
            CHECK_NOTHROW(
                    keys = new std::vector< char > (
                        inventory.addItems( testItems.cbegin(), testItems.cend() ) ) );
        }

        auto key = testKeys.begin();

        for( auto item : testItems )
        {
            CHECK_NOTHROW( **key++ = inventory.addItem( item ) );
        }


        SECTION( "addItem returns appropriate key" )
        {
            auto key = legalSymbols.cbegin();

            CHECK( slimeKey == *key++ );
            CHECK( inventory[ slimeKey ] == &slimeMold );

            CHECK( fluxKey == *key++ );
            CHECK( inventory[ fluxKey ] == &fluxCapacitor );

            CHECK( macKey == *key );
            CHECK( inventory[ macKey ] == &macGuffin );
        }

        char actualKey;

        SECTION( "addItem with appropriate key" )
        {
            swordKey = 'Z';
            REQUIRE_NOTHROW( actualKey = inventory.addItem( &masterSword, swordKey ) );
            CAPTURE( swordKey );
            CAPTURE( actualKey );

            CHECK( swordKey == actualKey );
            CHECK( inventory[ swordKey ] == &masterSword );
            CHECK( inventory[ actualKey ] == &masterSword );
        }

        SECTION( "addItem with already used key" )
        {
            swordKey = 'a';
            REQUIRE_NOTHROW( actualKey = inventory.addItem( &masterSword, swordKey ) );
            CAPTURE( swordKey );
            CAPTURE( actualKey );

            CHECK( swordKey != actualKey );
            CHECK( inventory[ swordKey ] != &masterSword );
            CHECK( inventory[ actualKey ] == &masterSword );
        }

        SECTION( "addItem with illegal key" )
        {
            swordKey = '#';
            REQUIRE_NOTHROW( actualKey = inventory.addItem( &masterSword, swordKey ) );
            CAPTURE( swordKey );
            CAPTURE( actualKey );

            CHECK( swordKey != actualKey );
            CHECK( inventory[ swordKey ] != &masterSword );
            CHECK( inventory[ actualKey ] == &masterSword );
        }
    }

    SECTION( "removing items" )
    {
        SECTION( "removing items by pointer" )
        {
            CHECK_NOTHROW( inventory.removeItem( &slimeMold ) );
            CHECK_NOTHROW( inventory.removeItem( &fluxCapacitor ) );
            CHECK_NOTHROW( inventory.removeItem( &macGuffin ) );
        }

        SECTION( "removing items by key" )
        {
            CHECK_NOTHROW( inventory.removeItem( slimeKey ) );
            CHECK_NOTHROW( inventory.removeItem( fluxKey ) );
            CHECK_NOTHROW( inventory.removeItem( macKey ) );
        }
    }

    SECTION( "size" )
    {
        auto key = testKeys.begin();

        for( auto item : testItems )
        {
            REQUIRE_NOTHROW( **key++ = inventory.addItem( item ) );
        }

        CHECK( inventory.size() == 5u );

        inventory.removeItem( slimeKey );
        CHECK( inventory.size() == 4u );

        inventory.removeItem( &fluxCapacitor );
        CHECK( inventory.size() == 3u );

        inventory.removeItem( macKey );
        CHECK( inventory.size() == 2u );

        inventory.removeItem( swordKey );
        CHECK( inventory.size() == 1u );

        inventory.removeItem( exoKey );
        CHECK( inventory.size() == 0u );

        inventory.addItem( &slimeMold );
        CHECK( inventory.size() == 1u );

        inventory.addItem( &fluxCapacitor );
        CHECK( inventory.size() == 2u );

        inventory.addItem( &macGuffin );
        CHECK( inventory.size() == 3u );

        inventory.addItem( &masterSword );
        CHECK( inventory.size() == 4u );

        inventory.addItem( &masterSword );
        CHECK( inventory.size() == 5u );
    }

    SECTION( "changing keys" )
    {
        auto key = testKeys.begin();
        for( auto item : testItems )
        {
            REQUIRE_NOTHROW( **key = inventory.addItem( item ) );
        }

        CHECK( inventory[ 'a' ] == &slimeMold );
        CHECK( inventory[ 'b' ] == &fluxCapacitor );
        CHECK( inventory[ 'c' ] == &macGuffin );
        CHECK( inventory[ 'd' ] == &masterSword );
        CHECK( inventory[ 'e' ] == &exosuit );

        SECTION( "by key" )
        {
            SECTION( "swapping" )
            {
                CHECK( inventory.changeKey( 'a', 'c' ) );

                CHECK( inventory[ 'c' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'a' ] == &macGuffin );
                CHECK( inventory[ 'd' ] == &masterSword );
                CHECK( inventory[ 'e' ] == &exosuit );
            }

            SECTION( "unused key" )
            {
                CHECK( inventory.changeKey( 'a', 'Q' ) );

                CHECK( inventory[ 'Q' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'c' ] == &macGuffin );
                CHECK( inventory[ 'd' ] == &masterSword );
                CHECK( inventory[ 'e' ] == &exosuit );
            }

            SECTION( "illegal key" )
            {
                CHECK_FALSE( inventory.changeKey( 'a', '!' ) );

                CHECK( inventory[ 'a' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'c' ] == &macGuffin );
                CHECK( inventory[ 'd' ] == &masterSword );
                CHECK( inventory[ 'e' ] == &exosuit );
            }
        }

        SECTION( "by Item*" )
        {
            SECTION( "swapping" )
            {
                CHECK( inventory.changeKey( &slimeMold, 'c' ) );

                CHECK( inventory[ 'c' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'a' ] == &macGuffin );
                CHECK( inventory[ 'd' ] == &masterSword );
                CHECK( inventory[ 'e' ] == &exosuit );
            }

            SECTION( "unused key" )
            {
                CHECK( inventory.changeKey( &slimeMold, 'X' ) );

                CHECK( inventory[ 'X' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'c' ] == &macGuffin );
                CHECK( inventory[ 'd' ] == &masterSword );
                CHECK( inventory[ 'e' ] == &exosuit );
            }

            SECTION( "illegal key" )
            {
                CHECK_FALSE( inventory.changeKey( &slimeMold, '*' ) );

                CHECK( inventory[ 'a' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'c' ] == &macGuffin );
                CHECK( inventory[ 'd' ] == &masterSword );
                CHECK( inventory[ 'e' ] == &exosuit );
            }
        }
    }

    SECTION( "sorted items" )
    {
        auto key = testKeys.begin();
        for( auto item : testItems )
        {
            REQUIRE_NOTHROW( **key = inventory.addItem( item ) );
        }

        std::vector< Item* > expectedOrder;

        expectedOrder.push_back( &masterSword );
        expectedOrder.push_back( &exosuit );
        expectedOrder.push_back( &slimeMold );
        expectedOrder.push_back( &fluxCapacitor );
        expectedOrder.push_back( &macGuffin );

        REQUIRE( expectedOrder.size() == inventory.sorted().size() );

        auto expectedItem = expectedOrder.cbegin();
        auto sortedPair = inventory.sorted().cbegin();
        do
        {
            CAPTURE( sortedPair->second->name() );
            CAPTURE( ( *expectedItem )->name() );

            CHECK( sortedPair->second->name() == ( *expectedItem )->name() );
        }
        while(  ++expectedItem != expectedOrder.cend() &&
                ++sortedPair != inventory.sorted().cend()  );
    }
}
