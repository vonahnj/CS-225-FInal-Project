#include "../cs225/catch/catch.hpp"
#include "../data_reader.h"
#include "../encounter.h"
#include "../traversals.h"

#include <vector>
#include <queue>
#include <iostream>

using namespace encounters;

// Small data map returns cycle of 0, 1, 3 with unconnected node 2

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

void checkOrder(std::vector<size_t> order, std::queue<encounter*> traversal) {
  REQUIRE(traversal.size() == order.size());

  vector<size_t>::iterator it = order.begin();

  while (!traversal.empty()) {
    if (traversal.front()->id != *it) {
      INFO(std::to_string(traversal.front()->id)+" is not " + std::to_string(*it));
      FAIL();
    }
    traversal.pop();
    ++it;
  }

  SUCCEED();
}

void deleteNodes(vector<encounter*> &vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        delete vec.at(i);
    }
}

TEST_CASE("DFS traversal visits all nodes from start", "[DFS][traversals]") {
  vector<encounter*> small_data = DataReader::readFromFile("tests/test_data/small_data.csv");

  std::queue<encounter*> traversal = Traversals::getDFSTraversal(small_data, 0);
  checkVisitsAll(small_data.size(), traversal);
  deleteNodes(small_data);
}

TEST_CASE("BFS traversal visits all nodes from start", "[BFS][traversals]") {
  vector<encounter*> small_data = DataReader::readFromFile("tests/test_data/small_data.csv");

  std::queue<encounter*> traversal = Traversals::getBFSTraversal(small_data, 0);
  checkVisitsAll(small_data.size(), traversal);
  deleteNodes(small_data);
}

TEST_CASE("DFS ordering", "[DFS][traversals]") {
  vector<encounter*> small_data = DataReader::readFromFile("tests/test_data/small_data.csv");

  std::queue<encounter*> traversal = Traversals::getDFSTraversal(small_data, 0);
  std::vector<size_t> order{0, 1, 3, 2};
  checkOrder(order, traversal);

  traversal = Traversals::getDFSTraversal(small_data, 1);
  order = std::vector<size_t>{1, 0, 3, 2};
  checkOrder(order, traversal);

  traversal = Traversals::getDFSTraversal(small_data, 2);
  order = std::vector<size_t>{2, 0, 1, 3};
  checkOrder(order, traversal);

  traversal = Traversals::getDFSTraversal(small_data, 3);
  order = std::vector<size_t>{3, 0, 1, 2};
  checkOrder(order, traversal);

  deleteNodes(small_data);
}

TEST_CASE("DFS ordering - big", "[DFS][traversals]") {
  vector<encounter*> big_data = DataReader::readFromFile("tests/test_data/large_data.csv");

  std::queue<encounter*> traversal = Traversals::getDFSTraversal(big_data, 0);
  std::vector<size_t> order{
    0, 43, 295, 163, 119, 285, 92, 270, 218, 145, 
    260, 14, 277, 290, 117, 252, 156, 101, 287, 217, 
    127, 116, 231, 86, 103, 279, 46, 273, 311, 58, 
    122, 123, 102, 151, 164, 55, 304, 48, 72, 205, 
    35, 210, 25, 7, 251, 112, 223, 83, 159, 36, 183, 
    63, 175, 216, 8, 221, 1, 292, 54, 170, 250, 21, 189, 
    271, 90, 30, 13, 40, 22, 232, 157, 281, 53, 109, 33, 
    227, 6, 240, 308, 200, 129, 272, 193, 66, 85, 94, 93, 
    4, 230, 180, 71, 142, 310, 228, 161, 11, 100, 82, 155, 
    107, 195, 194, 5, 190, 204, 51, 65, 59, 245, 120, 226, 
    91, 41, 74, 32, 154, 88, 291, 128, 150, 167, 278, 237, 
    144, 12, 17, 282, 179, 26, 89, 137, 131, 213, 108, 225, 
    229, 177, 148, 191, 75, 239, 185, 62, 61, 249, 15, 160, 
    256, 184, 257, 37, 27, 294, 198, 166, 69, 206, 130, 162, 
    215, 248, 95, 284, 68, 196, 299, 134, 141, 283, 125, 
    275, 220, 38, 241, 199, 44, 246, 203, 263, 211, 261, 
    147, 222, 233, 39, 34, 9, 224, 253, 174, 235, 172, 307, 
    187, 202, 47, 73, 105, 301, 293, 149, 29, 24, 23, 115, 
    113, 169, 171, 76, 234, 45, 64, 208, 78, 99, 126, 96, 
    18, 181, 176, 165, 286, 31, 168, 173, 124, 146, 243, 
    267, 264, 20, 247, 192, 110, 135, 269, 97, 297, 121, 
    302, 268, 114, 118, 50, 56, 136, 158, 178, 80, 87, 2, 
    139, 79, 77, 106, 104, 244, 153, 3, 212, 209, 67, 132, 
    303, 207, 201, 300, 298, 296, 52, 238, 10, 236, 138, 
    254, 289, 152, 255, 19, 98, 84, 28, 276, 309, 111, 42, 
    274, 197, 219, 288, 140, 305, 280, 182, 57, 49, 81, 
    306, 16, 242, 133, 143, 214, 60, 70, 186, 266, 258, 
    265, 188, 259, 262
  };

  checkVisitsAll(big_data.size(), traversal);
  checkOrder(order, traversal);

  deleteNodes(big_data);
 }



TEST_CASE("BFS ordering", "[BFS][traversals]") {
  vector<encounter*> small_data = DataReader::readFromFile("tests/test_data/small_data.csv");

  std::queue<encounter*> traversal = Traversals::getBFSTraversal(small_data, 0);
  std::vector<size_t> order{0, 1, 3, 2};
  checkOrder(order, traversal);

  traversal = Traversals::getBFSTraversal(small_data, 1);
  order = std::vector<size_t>{1, 0, 3, 2};
  checkOrder(order, traversal);

  traversal = Traversals::getBFSTraversal(small_data, 2);
  order = std::vector<size_t>{2, 0, 1, 3};
  checkOrder(order, traversal);

  traversal = Traversals::getBFSTraversal(small_data, 3);
  order = std::vector<size_t>{3, 0, 1, 2};
  checkOrder(order, traversal);

  deleteNodes(small_data);
}

TEST_CASE("BFS ordering - big", "[BFS][traversals]") {
  vector<encounter*> big_data = DataReader::readFromFile("tests/test_data/large_data.csv");

  std::queue<encounter*> traversal = Traversals::getBFSTraversal(big_data, 0);
  std::vector<size_t> order{
    0, 43, 145, 270, 163, 260, 285, 218, 
    92, 295, 119, 14, 277, 117, 290, 178, 
    87, 80, 158, 252, 286, 165, 233, 34, 39, 
    31, 9, 187, 202, 174, 224, 172, 235, 253, 
    307, 101, 287, 156, 76, 96, 45, 169, 171, 
    126, 176, 115, 181, 113, 18, 208, 99, 64, 
    78, 234, 149, 47, 301, 293, 105, 23, 24, 29, 
    73, 217, 241, 147, 263, 261, 199, 203, 222, 
    38, 220, 246, 44, 211, 125, 275, 116, 231, 
    127, 273, 86, 103, 279, 168, 46, 212, 19, 
    238, 236, 209, 98, 152, 254, 255, 207, 153, 
    104, 84, 106, 289, 139, 201, 28, 138, 296, 
    79, 244, 3, 77, 298, 303, 132, 10, 52, 300, 
    276, 67, 309, 136, 56, 2, 299, 134, 141, 283, 
    196, 50, 118, 248, 215, 284, 95, 68, 243, 
    267, 124, 173, 264, 146, 311, 304, 25, 35, 
    151, 48, 55, 58, 72, 210, 102, 205, 164, 122, 
    123, 130, 266, 258, 162, 69, 206, 198, 166, 
    229, 75, 131, 294, 27, 37, 177, 257, 256, 61, 
    249, 62, 148, 184, 185, 239, 137, 15, 191, 225, 
    213, 160, 108, 89, 20, 114, 268, 302, 7, 251, 112, 
    223, 121, 111, 197, 288, 42, 274, 140, 305, 219, 
    195, 107, 194, 100, 155, 82, 65, 128, 144, 88, 59, 
    51, 226, 5, 167, 17, 41, 278, 179, 190, 74, 291, 12, 
    237, 154, 91, 26, 32, 120, 204, 150, 245, 282, 83, 
    57, 182, 280, 81, 49, 306, 16, 11, 247, 110, 97, 
    297, 269, 192, 135, 36, 183, 159, 161, 272, 142, 
    94, 4, 180, 93, 193, 85, 66, 71, 310, 230, 228, 
    6, 200, 308, 240, 129, 8, 63, 175, 216, 221, 70, 
    265, 188, 157, 33, 281, 53, 227, 109, 232, 242, 
    54, 292, 1, 214, 60, 143, 133, 21, 13, 22, 30, 
    271, 90, 189, 170, 40, 250, 186, 259, 262
  };
  checkVisitsAll(big_data.size(), traversal);
  checkOrder(order, traversal);

  deleteNodes(big_data);
}