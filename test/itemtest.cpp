#include <string>

#include "catch.hpp"
#include "../src/item.h"

TEST_CASE( "item constructor", "[Item]" )
{
    SECTION( "default constructor" )
    {
        Item defaultItem;

        CHECK( defaultItem.name() == "" );
        CHECK( defaultItem.description() == "" );
        CHECK( defaultItem.group() == Item::Group::None );
        CHECK( defaultItem.weight() == 0 );
        CHECK( defaultItem.value() == 0 );
    }

    SECTION( "name only" )
    {
        std::string itemName = "Flux capacitor";
        Item fluxCapacitor( itemName );

        CHECK( fluxCapacitor.name() == itemName );
        CHECK( fluxCapacitor.description() == "" );
        CHECK( fluxCapacitor.group() == Item::Group::None );
        CHECK( fluxCapacitor.weight() == 0 );
        CHECK( fluxCapacitor.value() == 0 );
    }

    SECTION( "name and description" )
    {
        std::string itemName = "MacGuffin";
        std::string itemDescription = "An ominous glow emanates from this briefcase";

        Item macGuffin(
                itemName,
                itemDescription );

        CHECK( macGuffin.name() == itemName );
        CHECK( macGuffin.description() == itemDescription );
        CHECK( macGuffin.group() == Item::Group::None );
        CHECK( macGuffin.weight() == 0 );
        CHECK( macGuffin.value() == 0 );
    }

    SECTION( "name, description, group" )
    {
        std::string itemName = "Slime mold";
        std::string itemDescription = "A delcious dungeon staple";
        Item::Group itemGroup = Item::Group::Consumable;

        Item slimeMold(
                itemName,
                itemDescription,
                itemGroup );

        CHECK( slimeMold.name() == itemName );
        CHECK( slimeMold.description() == itemDescription );
        CHECK( slimeMold.group() == itemGroup );
        CHECK( slimeMold.weight() == 0 );
        CHECK( slimeMold.value() == 0 );
    }

    SECTION( "name, description, group, weight" )
    {
        std::string itemName = "Slime mold";
        std::string itemDescription = "A delcious dungeon staple";
        Item::Group itemGroup = Item::Group::Consumable;
        int weight = 5;

        Item slimeMold(
                itemName,
                itemDescription,
                itemGroup,
                weight );

        CHECK( slimeMold.name() == itemName );
        CHECK( slimeMold.description() == itemDescription );
        CHECK( slimeMold.group() == itemGroup );
        CHECK( slimeMold.weight() == weight );
        CHECK( slimeMold.value() == 0 );
    }

    SECTION( "all constructor arguments" )
    {
        std::string itemName = "Slime mold";
        std::string itemDescription = "A delcious dungeon staple";
        Item::Group itemGroup = Item::Group::Consumable;
        int weight = 5;
        int value = 15;

        Item slimeMold(
                itemName,
                itemDescription,
                itemGroup,
                weight,
                value );

        CHECK( slimeMold.name() == itemName );
        CHECK( slimeMold.description() == itemDescription );
        CHECK( slimeMold.group() == itemGroup );
        CHECK( slimeMold.weight() == weight );
        CHECK( slimeMold.value() == value );
    }
}

TEST_CASE( "item fields", "[Item]" )
{
    SECTION( "name" )
    {
        Item doppelgangerCorpse;
        std::string slimeMoldName = "Slime mold";
        std::string fluxCapacitorName = "Flux capacitor";
        std::string macGuffinName = "MacGuffin";

        CHECK( doppelgangerCorpse.name() == "" );

        doppelgangerCorpse.name( slimeMoldName );
        CHECK( doppelgangerCorpse.name() == slimeMoldName );

        doppelgangerCorpse.name( fluxCapacitorName );
        CHECK( doppelgangerCorpse.name() == fluxCapacitorName );

        doppelgangerCorpse.name( macGuffinName );
        CHECK( doppelgangerCorpse.name() == macGuffinName );
    }

    SECTION( "description" )
    {
        Item doppelgangerCorpse;
        std::string slimeMoldDescription = "A mouthwatering dungeon staple";
        std::string fluxCapacitorDescription = "The key to the mysteries of the universe";
        std::string macGuffinDescription = "An ominous glow emanates from this briefcase";

        CHECK( doppelgangerCorpse.description() == "" );

        doppelgangerCorpse.description( slimeMoldDescription );
        CHECK( doppelgangerCorpse.description() == slimeMoldDescription );

        doppelgangerCorpse.description( fluxCapacitorDescription );
        CHECK( doppelgangerCorpse.description() == fluxCapacitorDescription );

        doppelgangerCorpse.description( macGuffinDescription );
        CHECK( doppelgangerCorpse.description() == macGuffinDescription );
    }

    SECTION( "group" )
    {
        Item doppelgangerCorpse;

        Item::Group slimeMoldGroup = Item::Group::Consumable;
        Item::Group fluxCapacitorGroup = Item::Group::Craftable;
        Item::Group macGuffinGroup = Item::Group::Quest;

        CHECK( doppelgangerCorpse.group() == Item::Group::None );
        
        doppelgangerCorpse.group( slimeMoldGroup );
        CHECK( doppelgangerCorpse.group() == slimeMoldGroup );

        doppelgangerCorpse.group( fluxCapacitorGroup );
        CHECK( doppelgangerCorpse.group() == fluxCapacitorGroup );

        doppelgangerCorpse.group( macGuffinGroup );
        CHECK( doppelgangerCorpse.group() == macGuffinGroup );
    }
}
