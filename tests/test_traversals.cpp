#include "../cs225/catch/catch.hpp"
#include "../data_reader.h"
#include "../encounter.h"
#include "../traversals.h"

#include <vector>
#include <queue>
#include <iostream>

using namespace encounters;

void checkVisitsAll(int numNodes, std::queue<encounter*> traversal) {
  REQUIRE(traversal.size() == numNodes);
  std::vector<bool> visited(numNodes, false);

  while (!traversal.empty()) {
    if (visited.at(traversal.front()->id)) {
      FAIL();
    } else {
      visited.at(traversal.front()->id) = true;
    }
    traversal.pop();
  }

  for (bool visit : visited) {
    REQUIRE(visit);
  }
}


TEST_CASE("DFS traversal visits all nodes from start", "[DFS][traversals]") {
  vector<encounter*> small_data = DataReader::readFromFile("tests/test_data/small_data.csv");

  std::queue<encounter*> traversal = Traversals::getDFSTraversal(small_data, 0);
  checkVisitsAll(small_data.size(), traversal);
}

TEST_CASE("BFS traversal visits all nodes from start", "[BFS][traversals]") {
  vector<encounter*> small_data = DataReader::readFromFile("tests/test_data/small_data.csv");

  std::queue<encounter*> traversal = Traversals::getBFSTraversal(small_data, 0);
  checkVisitsAll(small_data.size(), traversal);
}

TEST_CASE("DFS ordering - easy", "[DFS][traversals]") {

}

TEST_CASE("DFS ordering - medium", "[DFS][traversals]") {

}

TEST_CASE("DFS ordering - hard", "[DFS][traversals]") {

}

TEST_CASE("BFS ordering - easy", "[BFS][traversals]") {

}

TEST_CASE("BFS ordering - medium", "[BFS][traversals]") {

}

TEST_CASE("BFS ordering - hard", "[BFS][traversals]") {

}