#include "traversals.h"


namespace encounters {
  using std::vector;
  using std::queue;
  using std::stack;

  // in the future: add edges to show the actual traversal taking place?
  vector<encounter*> Traversals::getBFSTraversal(vector<encounter*> map, int start) {
    queue<encounter*> bfs_queue;
    vector<encounter*> bfs_traversal;

    // start the traversal at the starting location (map[start])
    bfs_queue.push(map[start]);

    while (!bfs_queue.empty()) {
      encounter* next_encounter = bfs_queue.front();
      bfs_queue.pop();

      if (std::find(bfs_traversal.begin(), bfs_traversal.end(), next_encounter) != bfs_traversal.end()) {
        continue; // skip already visited points
      }
      bfs_traversal.push_back(next_encounter);

      // for now we traverse both time/loc neighbors
      for (encounter::edge time_neighbor : next_encounter->time_neighbors) {
        bfs_queue.push(map[time_neighbor.end_id]);
      }

      for (encounter::edge loc_neighbor : next_encounter->loc_neighbors) {
        bfs_queue.push(map[loc_neighbor.end_id]);
      }
    }

    return bfs_traversal;
  }

  vector<encounter*> Traversals::getDFSTraversal(vector<encounter*> map, int start) {
    queue<encounter*> dfs_stack;
    vector<encounter*> dfs_traversal;

    dfs_stack.push(map[start]);

    while (!dfs_stack.empty()) {
      encounter* next_encounter = dfs_stack.front();
      dfs_stack.pop();

      if (std::find(dfs_traversal.begin(), dfs_traversal.end(), next_encounter) != dfs_traversal.end()) {
        continue; // skip already visited points
      }
      dfs_traversal.push_back(next_encounter);

      // for now we traverse both time/loc neighbors
      for (encounter::edge time_neighbor : next_encounter->time_neighbors) {
        dfs_stack.push(map[time_neighbor.end_id]);
      }

      for (encounter::edge loc_neighbor : next_encounter->loc_neighbors) {
        dfs_stack.push(map[loc_neighbor.end_id]);
      }
    }

    return dfs_traversal;
  }
}
