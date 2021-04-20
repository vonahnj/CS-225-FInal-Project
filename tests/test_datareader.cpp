#include "../cs225/catch/catch.hpp"
#include "../data_reader.h"
#include "../encounter.h"

#include <vector>
#include <iostream>

using namespace encounters;

void destroyEncounterVec1(vector<encounter*> &vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        delete vec.at(i);
    }
}

void linkTime(encounter &first, encounter &second) {
    first.time_neighbors.push_back(encounter::edge(first.id, second.id, dist(first.time, second.time)));
    second.time_neighbors.push_back(encounter::edge(second.id, first.id, dist(first.time, second.time)));
}

void linkDist(encounter &first, encounter &second) {
    first.loc_neighbors.push_back(encounter::edge(first.id, second.id, dist(first, second)));
    second.loc_neighbors.push_back(encounter::edge(second.id, first.id, dist(first, second)));
}

TEST_CASE("Test no data points", "[data_reader]") {
    REQUIRE(DataReader::readFromFile("tests/test_data/no_data.csv").size() == 0);
    REQUIRE(DataReader::readFromFile("tests/test_data/giberish.csv").size() == 0);
}

TEST_CASE("Test few data points", "[data_reader]") {
    vector<encounter> expected = {
        encounter(date(10, 10, 1949), 29.8830556,-97.9411111, 0), 
        encounter(date(11, 10, 1949), 29.8830556,-97.941112, 1), 
        encounter(date(10, 10, 1956), 28.9783333,-96.6458333, 2), 
        encounter(date(1, 1, 2000), 29.8972346,-97.9074231, 3), 
    };

    linkTime(expected.at(0), expected.at(1));

    linkDist(expected.at(0), expected.at(1));
    linkDist(expected.at(0), expected.at(3));
    linkDist(expected.at(1), expected.at(3));
    
    vector<encounter*> result = DataReader::readFromFile("tests/test_data/small_data.csv");

    REQUIRE(result.size() == expected.size());

    for (size_t i = 0; i < expected.size(); i++) {
        REQUIRE(*(result.at(i)) == expected.at(i));
    }

    destroyEncounterVec1(result);
}

TEST_CASE("Test many data points", "[data_reader]") {
    
    vector<encounter*> result = DataReader::readFromFile("tests/test_data/large_data.csv");
    int numRecords = 129;
    int numErroneousRecords = 7;

    REQUIRE(result.size() == numRecords - numErroneousRecords);

    destroyEncounterVec1(result);
}