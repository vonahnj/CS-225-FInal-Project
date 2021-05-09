#include "traversals.h"

namespace encounters {
  using std::vector;
  using std::queue;
  using std::stack;

  queue<encounter*> Traversals::getBFSTraversal(const vector<encounter*> &map, int start) {
    queue<encounter*> bfs_traversal;
    vector<bool> visited(map.size(), false);
    if ((size_t)(start) >= map.size() || start < 0) start = 0;

    // start the traversal at the starting location (map[start])
    BFS(map, start, bfs_traversal, visited);

    // Collect all connected components not connected to start
    for (size_t index = 0; index < visited.size(); ++index) {
      if (!visited.at(index)) {
        BFS(map, index, bfs_traversal, visited);
      }
    }

    return bfs_traversal;
  }

  void Traversals::BFS(const vector<encounter*> &map, int start, queue<encounter*> &bfs_traversal, vector<bool> &visited) {
    queue<encounter*> bfs_queue;
    bfs_queue.push(map[start]);

    // Continue until there are no more nodes in the queue
    while (!bfs_queue.empty()) {
      encounter* next_encounter = bfs_queue.front();
      bfs_queue.pop();

      // skip already visited points
      if (visited.at(next_encounter->id)) {
        continue;
      }

      // Add encounter to our resulting traversal record
      bfs_traversal.push(next_encounter);
      visited.at(next_encounter->id) = true;

      // for now we traverse both time/loc neighbors
      for (encounter::edge neighbor : next_encounter->neighbors) {
        if (!visited.at(neighbor.end_id)) {
          bfs_queue.push(map[neighbor.end_id]);
        }
      }
    }
  }

  queue<encounter*> Traversals::getDFSTraversal(const vector<encounter*> &map, int start) {
    queue<encounter*> dfs_traversal;
    vector<bool> visited(map.size(), false);
    if ((size_t)(start) >= map.size() || start < 0) start = 0;

    // start the traversal at the starting location (map[start])
    DFS(map, start, dfs_traversal, visited);

    // Collect all connected components not connected to start
    for (size_t index = 0; index < visited.size(); ++index) {
      if (!visited.at(index)) {
        DFS(map, index, dfs_traversal, visited);
        visited.at(start) = true;
      }
    }

    return dfs_traversal;
  }

  void Traversals::DFS(const vector<encounter*> &map, int start, queue<encounter*> &dfs_traversal, vector<bool> &visited) {
    visited.at(start) = true;
    dfs_traversal.push(map[start]);

    // Visit all the individual connected components
    for (encounter::edge &edge : map.at(start)->neighbors) {
      if (!visited.at(edge.end_id)) {
        DFS(map, edge.end_id, dfs_traversal, visited);
      }
    }
  }
}
