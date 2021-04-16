#include "../cs225/catch/catch.hpp"
#include "../encounter.h"

using namespace encounters;

TEST_CASE("Test time elapsed between two timepoints - basic") {
    encounter one;
    one.time.year = 2020; one.time.month=12; one.time.day=31;
    encounter two;
    two.time.year = 2021; two.time.month=12; two.time.day=31;

    REQUIRE(dist(one.time, two.time) == 365);
}

// calculated from https://www.timeanddate.com/date/durationresult.html?d1=22&m1=3&y1=2008&d2=13&m2=8&y2=2021&ti=on&
TEST_CASE("Test time elapsed between two timepoints - random") {
    encounter one;
    one.time.year = 2008; one.time.month=3; one.time.day=2;
    encounter two;
    two.time.year = 2021; two.time.month=8; two.time.day=13;

    REQUIRE(dist(one.time, two.time) == 4892);
}

//https://www.movable-type.co.uk/scripts/latlong.html
TEST_CASE("Test distance between two places") {
    location one;
    one.first = 40.1342432; one.second = 50.2343242;
    location two;
    two.first = 56.342324; two.second = 18.4243243;

    REQUIRE(dist(one.time, two.time) == 2923);
}
