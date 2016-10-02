#include "catch.hpp"
#include "../src/zone.h"

TEST_CASE( "Zone is constructed", "[ZoneConstructor]" ) {
    Zone zone(40, 20);

    SECTION( "Zone width is as expected" ) {
        REQUIRE( zone.w() == 40 );
    }

    SECTION( "Zone height is as expected" ) {
        REQUIRE( zone.h() == 20 );
    }

    SECTION( "Zone.tile(0, 0) is as expected" ) {
        REQUIRE( zone.tile(0, 0)->peekSymbol() == '#' );
        REQUIRE( zone.tile(0, 0)->blocksMovement() == true );

        REQUIRE( zone.tile(1, 1)->peekSymbol() == '.' );
        REQUIRE( zone.tile(1, 1)->blocksMovement() == false );
    }
}

TEST_CASE( "Zone exceptions are thrown", "[ZoneExceptions]" ) {

    SECTION( "Zone::tile out_of_range exceptions are thrown" ) {
        Zone zone(10, 10);

        REQUIRE_THROWS_AS( zone.tile( 0, -1), std::out_of_range );
        REQUIRE_THROWS_AS( zone.tile(-1,  0), std::out_of_range );
        REQUIRE_THROWS_AS( zone.tile(-1, -1), std::out_of_range );

        REQUIRE_THROWS_AS( zone.tile(10,  0), std::out_of_range );
        REQUIRE_THROWS_AS( zone.tile( 0, 10), std::out_of_range );
        REQUIRE_THROWS_AS( zone.tile(10, 10), std::out_of_range );

        REQUIRE_THROWS_AS( zone.tile(76,  0), std::out_of_range );
        REQUIRE_THROWS_AS( zone.tile( 0, 23), std::out_of_range );
        REQUIRE_THROWS_AS( zone.tile(92, 87), std::out_of_range );
    }

    SECTION( "Zone constructor invalid_argument exceptions are thrown" ) {
        REQUIRE_THROWS_AS( Zone zone(-7,  20), std::invalid_argument );
        REQUIRE_THROWS_AS( Zone zone( 0,  20), std::invalid_argument );
        REQUIRE_THROWS_AS( Zone zone( 9, -20), std::invalid_argument );
        REQUIRE_THROWS_AS( Zone zone(12,   0), std::invalid_argument );
        REQUIRE_THROWS_AS( Zone zone( 0,   0), std::invalid_argument );
        REQUIRE_THROWS_AS( Zone zone(-5, -32), std::invalid_argument );
    }

}
