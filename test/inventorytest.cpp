#include <iostream>
#include <vector>
#include <string>
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

    Item slimeMold( "Slime mold", "a delicious, nutritious dungeon staple" );
    Item fluxCapacitor( "Flux capacitor", "the key to the secrets of the universe" );
    Item macGuffin( "MacGuffin", "a mysterious golden glow emanates from this briefcase" );

    char slimeKey, fluxKey, macKey;

    CHECK_NOTHROW( slimeKey = inventory.addItem( &slimeMold ) );
    CHECK_NOTHROW( fluxKey = inventory.addItem( &fluxCapacitor ) );
    CHECK_NOTHROW( macKey = inventory.addItem( &macGuffin ) );

    SECTION( "adding items" )
    {
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

        Item masterSword(
                "Master sword",
                "a famous blade that can be wielded only by those with great courage" );

        char swordKey, actualKey;

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
        CHECK( inventory.size() == 3u );

        inventory.removeItem( slimeKey );
        CHECK( inventory.size() == 2u );

        inventory.removeItem( &fluxCapacitor );
        CHECK( inventory.size() == 1u );

        inventory.removeItem( macKey );
        CHECK( inventory.size() == 0u );

        inventory.addItem( &slimeMold );
        CHECK( inventory.size() == 1u );

        inventory.addItem( &fluxCapacitor );
        CHECK( inventory.size() == 2u );

        inventory.addItem( &macGuffin );
        CHECK( inventory.size() == 3u );
    }

    SECTION( "changing keys" )
    {
        CHECK( inventory[ 'a' ] == &slimeMold );
        CHECK( inventory[ 'b' ] == &fluxCapacitor );
        CHECK( inventory[ 'c' ] == &macGuffin );

        SECTION( "by key" )
        {
            SECTION( "swapping" )
            {
                CHECK( inventory.changeKey( 'a', 'c' ) );

                CHECK( inventory[ 'c' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'a' ] == &macGuffin );
            }

            SECTION( "unused key" )
            {
                CHECK( inventory.changeKey( 'a', 'Q' ) );

                CHECK( inventory[ 'Q' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'c' ] == &macGuffin );
            }

            SECTION( "illegal key" )
            {
                CHECK_FALSE( inventory.changeKey( 'a', '!' ) );

                CHECK( inventory[ 'a' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'c' ] == &macGuffin );
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
            }

            SECTION( "unused key" )
            {
                CHECK( inventory.changeKey( &slimeMold, 'X' ) );

                CHECK( inventory[ 'X' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'c' ] == &macGuffin );
            }

            SECTION( "illegal key" )
            {
                CHECK_FALSE( inventory.changeKey( &slimeMold, '*' ) );

                CHECK( inventory[ 'a' ] == &slimeMold );
                CHECK( inventory[ 'b' ] == &fluxCapacitor );
                CHECK( inventory[ 'c' ] == &macGuffin );
            }
        }
    }
}
