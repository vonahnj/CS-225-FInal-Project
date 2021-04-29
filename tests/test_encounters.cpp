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
