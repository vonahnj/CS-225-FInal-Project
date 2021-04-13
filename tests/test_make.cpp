#include "../cs225/catch/catch.hpp"
#include "../encounter.h"

using namespace encounters;

TEST_CASE("Test Make") {
    encounter one;
    one.time.year = 2020; one.time.month=12; one.time.day=31;
    encounter two;
    two.time.year = 2021; two.time.month=12; two.time.day=31;

    REQUIRE(dist(one.time, two.time) == -365);
}