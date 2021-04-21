#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include "encounter.h"

namespace encounters {
  using std::vector;
  using std::queue;
  using std::stack;

  class Traversals {
  public:
    // Get the traversal (BFS/DFS), given a graph (map) and a starting index (start)
    // The traversal will be returned as a vector of encouters, in the order of the traversal.
    static vector<encounter*> getBFSTraversal(vector<encounter*> map, int start);
    static vector<encounter*> getDFSTraversal(vector<encounter*> map, int start);
  };
}
