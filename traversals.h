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

    /**
     * Creates a queue holding the Breadth-First-Search ordered traversal of the nodes
     * in the map starting at the node at the given start index
     * 
     * @param map list of all the nodes in the graph
     * @param start the index of the starting node
     * @return a queue containing the nodes in breadth-first order
     */
    static queue<encounter*> getBFSTraversal(const vector<encounter*> &map, int start);

    /**
     * Creates a queue holding the Depth-First-Search ordered traversal of the nodes
     * in the map starting at the node at the given start index
     * 
     * @param map list of all the nodes in the graph
     * @param start the index of the starting node
     * @return a queue containing the nodes in depth-first order
     */
    static queue<encounter*> getDFSTraversal(const vector<encounter*> &map, int start);

  private: 
    /**
     * Conducts a Breadth-First-Search starting at the node given by the parameters.
     * One call of this method conducts a BFS traversal of the entire connected component
     * connected to the starting node. It fills the bfs_traversal queue with the nodes 
     * as it visits them.
     * 
     * @param map list of all the nodes in the graph
     * @param start the index of the starting node
     * @param bfs_traversal a queue to add the traversal to
     * @param visited an array to track whether the traversal has visited a given node
     */
    static void BFS(const vector<encounter*> &map, int start, queue<encounter*> &bfs_traversal, vector<bool> &visited);

    /**
     * Conducts a Depth-First-Search starting at the node given by the parameters
     * One call of this method recursively calls itself until the entire connected component
     * connected to the starting node is in the traversal. It fills the dfs_traversal queue 
     * with the nodes as it visits them.
     * 
     * @param map list of all the nodes in the graph
     * @param start the index of the starting node
     * @param dfs_traversal a queue to add the traversal to
     * @param visited an array to track whether the traversal has visited a given node
     */
    static void DFS(const vector<encounter*> &map, int start, queue<encounter*> &dfs_traversal, vector<bool> &visited);
  };
}
