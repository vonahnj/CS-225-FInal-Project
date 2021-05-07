#include "../cs225/catch/catch.hpp"
#include "../encounter.h"

using namespace encounters;

//https://www.movable-type.co.uk/scripts/latlong.html
TEST_CASE("Test distance between two places") {
    encounter one;
    one.location.first = 40.1342432; one.location.second = 50.2343242;
    encounter two;
    two.location.first = 56.342324; two.location.second = 18.4243243;

    REQUIRE(round(dist(one, two)) == 2923);
}

TEST_CASE("Test operations for edges") {
    encounter::edge first = encounter::edge(1, 2, 3);
    encounter::edge second = encounter::edge(1, 2, 3);
    encounter::edge third = encounter::edge(1, 2, 0);
    REQUIRE(first == second); 
    REQUIRE(first != third);
    REQUIRE(first > third);
    REQUIRE(third < second);
}

TEST_CASE("Test == for encounters") {
    encounter enc1 = encounter(3, 4, 2, "");
    encounter enc2 = encounter(3, 4, 2, "");
    encounter::edge first = encounter::edge(1, 2, 1);
    encounter::edge second = encounter::edge(1, 3, 3);
    encounter::edge third = encounter::edge(1, 1, 0);

    enc1.neighbors.push_back(first);
    enc1.neighbors.push_back(second);
    enc1.neighbors.push_back(third);

    enc2.neighbors.push_back(first);
    enc2.neighbors.push_back(second);
    enc2.neighbors.push_back(third);

    REQUIRE(enc1 == enc2);

    enc1.neighbors.push_back(first);

    REQUIRE(!(enc1 == enc2));
}