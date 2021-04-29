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
  std::vector<size_t> order{0, 3, 1, 2};
  checkOrder(order, traversal);

  traversal = Traversals::getDFSTraversal(small_data, 1);
  order = std::vector<size_t>{1, 3, 0, 2};
  checkOrder(order, traversal);

  traversal = Traversals::getDFSTraversal(small_data, 2);
  order = std::vector<size_t>{2, 0, 3, 1};
  checkOrder(order, traversal);

  traversal = Traversals::getDFSTraversal(small_data, 3);
  order = std::vector<size_t>{3, 1, 0, 2};
  checkOrder(order, traversal);

  deleteNodes(small_data);
}

TEST_CASE("DFS ordering - big", "[DFS][traversals]") {
  vector<encounter*> big_data = DataReader::readFromFile("tests/test_data/large_data.csv");

  std::queue<encounter*> traversal = Traversals::getDFSTraversal(big_data, 0);
  std::vector<size_t> order{
    0, 311, 310, 309, 308, 306, 307, 305, 304, 303, 302, 301, 300, 299, 298, 297, 
    296, 295, 294, 293, 291, 292, 290, 289, 288, 287, 286, 285, 284, 283, 282, 281, 
    280, 279, 278, 277, 276, 275, 274, 273, 272, 271, 257, 270, 269, 268, 267, 266, 
    265, 264, 263, 261, 260, 258, 256, 255, 254, 253, 252, 251, 250, 249, 248, 246, 
    247, 244, 245, 242, 240, 241, 243, 239, 238, 237, 236, 235, 234, 233, 231, 232, 
    230, 229, 228, 227, 226, 225, 224, 223, 222, 220, 219, 221, 218, 217, 216, 215, 
    214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 
    198, 197, 196, 195, 194, 193, 191, 190, 189, 186, 185, 187, 192, 188, 181, 184, 
    183, 182, 180, 179, 178, 177, 176, 174, 173, 172, 171, 169, 168, 167, 175, 170, 
    166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 
    150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 
    132, 134, 131, 133, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 119, 120, 
    118, 117, 116, 115, 114, 113, 112, 111, 109, 108, 107, 106, 110, 105, 104, 103, 
    102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 
    83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 
    62, 63, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 
    43, 42, 41, 40, 37, 39, 38, 36, 35, 34, 32, 33, 30, 28, 31, 29, 27, 26, 25, 24, 
    23, 20, 19, 22, 21, 17, 18, 16, 15, 14, 12, 13, 11, 10, 9, 7, 8, 6, 5, 4, 3, 2, 
    1, 259, 262
  };
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
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 
    19, 20, 23, 24, 25, 26, 27, 28, 29, 31, 32, 33, 34, 35, 36, 37, 
    38, 39, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 
    55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 
    87, 88, 89, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 
    103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 
    116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 
    129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 
    142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 
    155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 
    168, 169, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 
    182, 183, 184, 185, 187, 188, 190, 191, 192, 193, 194, 195, 196, 
    197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 
    210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 
    223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 
    236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 
    249, 251, 252, 253, 254, 255, 256, 257, 258, 260, 261, 263, 264, 
    265, 266, 267, 268, 269, 270, 272, 273, 274, 275, 276, 277, 278, 
    279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 
    292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 
    305, 306, 307, 308, 309, 310, 311, 13, 21, 22, 30, 40, 90, 170, 
    186, 189, 250, 271, 259, 262
  };
  checkOrder(order, traversal);

  deleteNodes(big_data);
}