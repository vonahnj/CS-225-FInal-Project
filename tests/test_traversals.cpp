#include "../cs225/catch/catch.hpp"
#include "../data_reader.h"
#include "../encounter.h"
#include "../traversals.h"

#include <vector>
#include <iostream>

using namespace encounters;


TEST_CASE("DFS traversal visits all nodes from start", "[traversals]") {
  vector<encounter> expected = {
      encounter(date(10, 10, 1949), 29.8830556,-97.9411111, 0),
      encounter(date(11, 10, 1949), 29.8830556,-97.941112, 1),
    //  encounter(date(10, 10, 1956), 28.9783333,-96.6458333, 2),
      encounter(date(1, 1, 2000), 29.8972346,-97.9074231, 3),
  };

  vector<encounter> not_expected = {
    encounter(date(10, 10, 1956), 28.9783333,-96.6458333, 2)
  };
  /*
  linkTime(expected.at(0), expected.at(1));

  linkDist(expected.at(0), expected.at(1));
  linkDist(expected.at(0), expected.at(3));
  linkDist(expected.at(1), expected.at(3));
  */
  vector<encounter*> small_data = DataReader::readFromFile("tests/test_data/small_data.csv");

  bool fail = false;

  // fail if any values are wrong OR missing!
  for (encounter* enc : Traversals::getDFSTraversal(small_data, 0)) {
    if ((std::find(expected.begin(), expected.end(), *enc) == expected.end()) || (std::find(not_expected.begin(), not_expected.end(),*enc) != not_expected.end())) {
      fail = true;
    }
  }

  REQUIRE(fail == false);
}

TEST_CASE("BFS traversal visits all nodes from start", "[traversals]") {
  vector<encounter> expected = {
      encounter(date(10, 10, 1949), 29.8830556,-97.9411111, 0),
      encounter(date(11, 10, 1949), 29.8830556,-97.941112, 1),
      //encounter(date(10, 10, 1956), 28.9783333,-96.6458333, 2),
      encounter(date(1, 1, 2000), 29.8972346,-97.9074231, 3),
  };

  vector<encounter> not_expected = {
    encounter(date(10, 10, 1956), 28.9783333,-96.6458333, 2)
  };

  vector<encounter*> small_data = DataReader::readFromFile("tests/test_data/small_data.csv");

  bool fail = false;

  // fail if any values are wrong OR missing!
  for (encounter* enc : Traversals::getDFSTraversal(small_data, 0)) {
    if ((std::find(expected.begin(), expected.end(), *enc) == expected.end()) || (std::find(not_expected.begin(), not_expected.end(),*enc) != not_expected.end())) {
      fail = true;
    }
  }

  REQUIRE(fail == false);
}

TEST_CASE("BFS traversal visits only the 3rd node when started from the 3rd (island)", "[traversals]") {
  vector<encounter> expected = {
      encounter(date(10, 10, 1956), 28.9783333,-96.6458333, 2),
  };

  vector<encounter> not_expected = {
      encounter(date(10, 10, 1949), 29.8830556,-97.9411111, 0),
      encounter(date(11, 10, 1949), 29.8830556,-97.941112, 1),
      //encounter(date(10, 10, 1956), 28.9783333,-96.6458333, 2),
      encounter(date(1, 1, 2000), 29.8972346,-97.9074231, 3),
  };

  vector<encounter*> small_data = DataReader::readFromFile("tests/test_data/small_data.csv");

  bool fail = false;

  // fail if any values are wrong OR missing!
  for (encounter* enc : Traversals::getDFSTraversal(small_data, 0)) {
    if ((std::find(expected.begin(), expected.end(), *enc) == expected.end()) || (std::find(not_expected.begin(), not_expected.end(),*enc) != not_expected.end())) {
      fail = true;
    }
  }

  REQUIRE(fail == false);
}

/*
TEST_CASE("DFS traversal visits farther nodes first", "[traversals]") {

}

TEST_CASE("BFS traversal visits neighbors first", "[traversals]") {

}*/
