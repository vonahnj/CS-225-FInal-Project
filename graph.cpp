#include "graph.h"
#include "encounter.h"
#include "traversals.h"
#include "data_reader.h"
#include "kdtree/kdtree.h"
#include "heap/heap.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>

namespace encounters {
    using std::vector;
    using std::list;

    // Initialize functions

    Graph::Graph() {}

    Graph::Graph(const std::string &file_name) {
        // Create a KDTree for nearest-neighbors given our observation file
        nodes_ = DataReader::readFromFile(file_name);
        locations_ = KDTree(nodes_);
    }

    Graph::~Graph() {
        // free memory allocated to each node
        for (size_t i = 0; i < nodes_.size(); i++) {
            delete nodes_.at(i);
        }
    }

    // Access Functions

    int Graph::findNearestNeighbor(const std::pair<double, double> &location) const {
        // Get index of location in our dataset closest to user-specified coordinates
        int index = locations_.findNearestNeighbor(Point<2>(location.first, location.second));

        // Return node with lowest index at this exact location (for consistency)
        if (!nodes_.at(index)->neighbors.empty()) {
            const encounter::edge &edge = nodes_.at(index)->neighbors.front();
            if (edge.dist == 0 && edge.end_id < index) {
                index = edge.end_id;
            }
        }
        return index;
    }

    const encounter* Graph::getNode(int id) const {
        if (id == -1 || id >= (int)(nodes_.size())) return NULL;
        return nodes_.at(id);
    }

    int Graph::getNodeCount() {return (int)nodes_.size();}

    std::list<const encounter*> Graph::getShortestPathDijk(const std::pair<double, double> &start, const std::pair<double, double> &end) {
        int startIndex = findNearestNeighbor(start);
        int endIndex = findNearestNeighbor(end);

        return getShortestPathDijk(startIndex, endIndex);
    }

    std::list<const encounter*> Graph::getShortestPathDijk(int startIndex, int endIndex) {
        // Get spanning tree to trace path from start->end
        if (startIndex == -1 || endIndex == -1) return list<const encounter*>();
        vector<int> tree = getSpanningTreeDijk(startIndex);
        if (tree.at(endIndex) == -2) {
            return list<const encounter*>();
        }

        // Recreate path, starting from our end
        std::list<const encounter*> path;
        path.push_front(nodes_.at(endIndex));
        int currentIndex = tree.at(endIndex);

        // Backtrack from end to begining, adding parent node to the front
        // of our list
        while (currentIndex >= 0) {
            path.push_front(nodes_.at(currentIndex));
            currentIndex = tree.at(currentIndex);
        }

        return path;
    }

    vector<int> Graph::getSpanningTreeDijk(int start) {
        // Create initial values
        vector<int> parents(nodes_.size(), -2);
        vector<double> distance(nodes_.size(), INFINITY);
        heap<encounter::edge> min_heap(nodes_.at(start)->neighbors);
        vector<bool> addedToGraph(nodes_.size(), false);

        // Set values for start position
        parents.at(start) = -1;
        distance.at(start) = 0;
        addedToGraph.at(start) = true;
        for (size_t idx = 0; idx < nodes_.at(start)->neighbors.size(); ++idx) {
            parents.at(nodes_.at(start)->neighbors.at(idx).end_id) = start;
            distance.at(nodes_.at(start)->neighbors.at(idx).end_id) = nodes_.at(start)->neighbors.at(idx).dist;
        }

        while (!min_heap.empty()) {
            // Get next shortest edge not added to graph
            encounter::edge edge = min_heap.pop();
            if (addedToGraph.at(edge.end_id) || parents.at(edge.end_id) != edge.start_id) {
                continue;
            }
            addedToGraph.at(edge.end_id) = true;
            distance.at(edge.end_id) = distance.at(parents.at(edge.end_id)) + edge.dist;

            for (encounter::edge &adj_edge : nodes_.at(edge.end_id)->neighbors) {
                // Parse new frontier edges
                if (!addedToGraph.at(adj_edge.end_id)) {
                    // If shorter edge found, update heap and record path in 'parents' (for spanning tree)
                    if (distance.at(adj_edge.start_id) + adj_edge.dist < distance.at(adj_edge.end_id)) {
                        distance.at(adj_edge.end_id) = distance.at(adj_edge.start_id) + adj_edge.dist;
                        parents.at(adj_edge.end_id) = adj_edge.start_id;
                        min_heap.push(adj_edge);
                    }
                }
            }
        }

        return parents;
    }

    vector<double> Graph::getBetweennessValues() {
        // values holdes centrality measures for each node
        vector<double> values = vector<double>(nodes_.size(), 0.0);
        vector<int> tree;

        // Find spanning trees from each starting point for all-pairs shortest paths
        for(int i = 0; i < (int)nodes_.size(); i++) {
            tree = getSpanningTreeDijk(i);

            // Mark the points visited from our fixed start to every possible node
            // but skip nonconnected (-2) or start (-1) node
            for(int j = 0; j < (int)nodes_.size(); j++) {
                if(tree[j] != -2 && tree[j] != -1) {
                    int curr = j;

                    // Traverse/mark visits until we hit our start (-1) node
                    while(tree[curr] != -1) {
                        values[curr]++;
                        curr = tree[curr];
                    }
                    values[curr]++;
                }
            }
        }

        // Normalize our centrality measure by the total ordered pairs of
        // (start, end) we visited - namely, 2*(N choose 2) = N*(N-1) ordered pairs
        for(int i = 0; i < (int)nodes_.size(); i++) {
            values[i] /= nodes_.size() * (nodes_.size() - 1);
        }
        return values;
    }

    // Iterator Functions:

    const Graph::traversal::iterator& Graph::traversal::iterator::operator=(const iterator& rhs) {
        if (this != &rhs) {
            order = rhs.order;
        }
        return *this;
    }

    const Graph::traversal::iterator& Graph::traversal::iterator::operator++() {
        if (!order.empty()) {
            order.pop();
        }
        return *this;
    }

    const encounter* Graph::traversal::iterator::operator*() {
        if (order.empty()) return NULL;
        return order.front();
    }

    const encounter& Graph::traversal::iterator::operator->() {
        return *order.front();
    }

    bool Graph::traversal::iterator::operator==(const iterator& rhs) const {
        if (order.empty() && rhs.order.empty()) return true;
        if (order.empty() || rhs.order.empty()) return false;
        return this->order.front()->id == rhs.order.front()->id;
    }

    bool Graph::traversal::iterator::operator!=(const iterator& rhs) const {
        return !(*this == rhs);
    }

    Graph::traversal::iterator Graph::traversal::end() {
        return Graph::traversal::iterator();
    }

    Graph::traversal::iterator Graph::traversal::begin() {
        return Graph::traversal::iterator(master_);
    }

    Graph::BFS::BFS(const Graph &g, const std::pair<double, double> &start) {
        // Get index at approximate location
        int startIndex = g.findNearestNeighbor(start);
        master_ = Traversals::getBFSTraversal(g.nodes_, startIndex);
    }

    Graph::DFS::DFS(const Graph &g, const std::pair<double, double> &start) {
        // Get index at approximate location
        int startIndex = g.findNearestNeighbor(start);
        master_  = Traversals::getDFSTraversal(g.nodes_, startIndex);
    }

} // namespace encounters
