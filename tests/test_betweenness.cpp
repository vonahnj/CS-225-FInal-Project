#include "../cs225/catch/catch.hpp"
#include "../data_reader.h"
#include "../graph.h"

#include <vector>
#include <iostream>

using namespace encounters;

TEST_CASE("test") {
    Graph graph("tests/test_data/large_data.csv");
    graph.getBetweennessValues();
}