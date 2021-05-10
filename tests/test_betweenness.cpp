#include "../cs225/catch/catch.hpp"
#include "../data_reader.h"
#include "../graph.h"

#include <vector>
#include <iostream>

using namespace encounters;

TEST_CASE("Verify small data values") {
    Graph graph("tests/test_data/small_data.csv");
    vector<double> values = graph.getBetweennessValues();
    //small data forms a loop between points 0, 1, and 3
    //This means that each point in the loop is part of 2 shortest paths out of 6 possible, so a value of .33
    vector<double> expected = {1.0/3.0, 1.0/3.0, 0, 1.0/3.0};
    REQUIRE(values == expected);
}

TEST_CASE("Verify Parallelogram data values") {
    Graph graph("tests/test_data/parallelogram.csv");
    vector<double> values = graph.getBetweennessValues();
    //nodes 1 and 2 are the most central on the graph, which lines up with the centrality values
    vector<double> expected = {1.0/3.0, 0.4, 7.0/15.0, 1.0/3.0, 1.0/3.0, 1.0/3.0};
    REQUIRE(values == expected);
}
