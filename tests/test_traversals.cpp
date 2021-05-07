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
    if(!visit) {
      FAIL();
    }
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
    0, 14, 43, 92, 119, 145, 163, 218, 260, 270, 
    285, 295, 277, 117, 290, 252, 101, 156, 287, 
    217, 127, 116, 231, 86, 103, 279, 46, 273, 
    25, 35, 48, 55, 58, 72, 102, 122, 123, 151, 
    164, 205, 210, 304, 311, 7, 112, 223, 251, 83, 
    36, 159, 183, 8, 63, 175, 216, 221, 1, 54, 292, 
    13, 21, 22, 30, 40, 90, 170, 189, 250, 271, 
    232, 33, 53, 109, 157, 227, 281, 6, 129, 200, 
    240, 308, 4, 66, 71, 85, 93, 94, 142, 161, 
    180, 193, 228, 230, 272, 310, 11, 82, 100, 
    107, 155, 194, 195, 5, 12, 17, 26, 32, 41, 
    51, 59, 65, 74, 88, 91, 120, 128, 144, 150, 
    154, 167, 179, 190, 204, 226, 237, 245, 278, 
    282, 291, 89, 15, 27, 37, 61, 62, 75, 108, 
    131, 137, 148, 160, 177, 184, 185, 191, 213, 
    225, 229, 239, 249, 256, 257, 294, 69, 166, 
    198, 206, 130, 162, 215, 248, 95, 284, 68, 
    196, 134, 141, 283, 299, 125, 275, 38, 44, 
    147, 199, 203, 211, 220, 222, 241, 246, 261, 
    263, 34, 39, 233, 9, 172, 174, 187, 202, 224, 
    235, 253, 307, 23, 24, 29, 47, 73, 105, 149, 
    293, 301, 18, 45, 64, 76, 78, 96, 99, 113, 
    115, 126, 169, 171, 176, 181, 208, 234, 165, 
    286, 31, 168, 124, 146, 173, 243, 264, 267, 
    20, 247, 97, 110, 135, 192, 269, 297, 121, 
    268, 302, 114, 118, 50, 56, 136, 80, 87, 
    158, 178, 2, 3, 10, 19, 28, 52, 67, 77, 79, 
    84, 98, 104, 106, 132, 138, 139, 152, 153, 
    201, 207, 209, 212, 236, 238, 244, 254, 255, 
    276, 289, 296, 298, 300, 303, 309, 42, 111, 
    140, 197, 219, 274, 288, 305, 49, 57, 81, 182, 
    280, 16, 306, 242, 133, 143, 214, 60, 70, 186, 
    258, 266, 188, 265, 259, 262
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
    0, 14, 43, 92, 119, 145, 163, 218, 260, 270, 
    285, 295, 277, 117, 290, 80, 87, 158, 178, 252, 
    165, 286, 34, 39, 233, 31, 9, 172, 174, 187, 202,
    224, 235, 253, 307, 101, 156, 287, 18, 45, 64, 
    76, 78, 96, 99, 113, 115, 126, 169, 171, 176, 
    181, 208, 234, 23, 24, 29, 47, 73, 105, 149, 
    293, 301, 217, 38, 44, 147, 199, 203, 211, 220,
    222, 241, 246, 261, 263, 125, 275, 116, 231, 
    127, 273, 86, 103, 279, 168, 46, 3, 10, 19, 
    28, 52, 67, 77, 79, 84, 98, 104, 106, 132, 138,
    139, 152, 153, 201, 207, 209, 212, 236, 238, 
    244, 254, 255, 276, 289, 296, 298, 300, 303, 
    309, 56, 136, 2, 134, 141, 283, 299, 196, 50, 
    118, 215, 248, 95, 284, 68, 124, 146, 173, 243, 
    264, 267, 25, 35, 48, 55, 58, 72, 102, 122, 123, 
    151, 164, 205, 210, 304, 311, 130, 258, 266, 
    162, 69, 166, 198, 206, 15, 27, 37, 61, 62, 
    75, 108, 131, 137, 148, 160, 177, 184, 185, 
    191, 213, 225, 229, 239, 249, 256, 257, 294, 
    89, 20, 114, 268, 302, 7, 112, 223, 251, 121, 
    42, 111, 140, 197, 219, 274, 288, 305, 82, 100, 
    107, 155, 194, 195, 5, 12, 17, 26, 32, 41, 51, 
    59, 65, 74, 88, 91, 120, 128, 144, 150, 154, 
    167, 179, 190, 204, 226, 237, 245, 278, 282, 
    291, 83, 49, 57, 81, 182, 280, 16, 306, 11, 
    247, 97, 110, 135, 192, 269, 297, 36, 159, 
    183, 4, 66, 71, 85, 93, 94, 142, 161, 180, 
    193, 228, 230, 272, 310, 6, 129, 200, 240, 
    308, 8, 63, 175, 216, 221, 70, 188, 265, 33, 
    53, 109, 157, 227, 281, 232, 242, 1, 54, 292, 
    214, 60, 133, 143, 13, 21, 22, 30, 40, 90, 
    170, 189, 250, 271, 186, 259, 262
  };

  checkVisitsAll(big_data.size(), traversal);
  checkOrder(order, traversal);
  deleteNodes(big_data);
}