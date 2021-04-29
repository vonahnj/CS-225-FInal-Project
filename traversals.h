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
    static queue<encounter*> getBFSTraversal(vector<encounter*> map, int start);
    static void BFS(vector<encounter*> &map, int start, queue<encounter*> &bfs_traversal, vector<bool> &visited);
    static queue<encounter*> getDFSTraversal(vector<encounter*> map, int start);
    static void DFS(vector<encounter*> &map, int start, queue<encounter*> &dfs_traversal, vector<bool> &visited);
  };
}
