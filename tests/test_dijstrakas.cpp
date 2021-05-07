#include "../cs225/catch/catch.hpp"
#include "../graph.h"

#include <vector>
#include <list>

using namespace encounters;
using std::vector;
using std::list;

void checkPath(list<encounter*> &actual, vector<int> &expected) {
    REQUIRE(actual.size() == expected.size());

    list<encounter*>::iterator actualIt = actual.begin();
    vector<int>::iterator expectedIt = expected.begin();

    while (actualIt != actual.end() && expectedIt != expected.end()) {
        REQUIRE((*actualIt)->id == *expectedIt);
        ++actualIt;
        ++expectedIt;
    }
}

TEST_CASE("Test shortest path, small", "[dijstrakas]") {
    Graph graph("tests/test_data/small_data.csv");

    // check path to itself
    list<encounter*> path = graph.getShortestPathDijk(std::pair<double, double>(29.8830556,-97.9411111), std::pair<double, double>(29.8830556,-97.9411111));
    vector<int> expectedPath = {0};
    checkPath(path, expectedPath);

    // Check path to very closeby encounter
    path = graph.getShortestPathDijk(std::pair<double, double>(29.8830556, -97.941121), std::pair<double, double>(29.8830556,-97.9411111));
    expectedPath = {1, 0};
    checkPath(path, expectedPath);

    // Check path to another connected encounter
    path = graph.getShortestPathDijk(std::pair<double, double>(29.8830556,-97.9411111), std::pair<double, double>(29.8972346,-97.9074231));
    expectedPath = {0, 3};
    checkPath(path, expectedPath);

    // Check path to unconnected component
    path = graph.getShortestPathDijk(std::pair<double, double>(29.8830556,-97.9411111), std::pair<double, double>(28.9783333,-96.6458333));
    expectedPath = {};
    checkPath(path, expectedPath);
}

TEST_CASE("Test shortest path, big", "[dijstrakas]") {
    Graph graph("tests/test_data/big_data.csv");

    list<encounter*> path = graph.getShortestPathDijk(std::pair<double, double>(29.8830556,-97.9411111), std::pair<double, double>(29.8830556,-97.9411111));
    //vector<int> expectedPath = {0};

}