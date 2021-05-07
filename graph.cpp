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
        nodes_ = DataReader::readFromFile(file_name);
        locations_ = KDTree(nodes_);
    }

    Graph::~Graph() {
        for (size_t i = 0; i < nodes_.size(); i++) {
            delete nodes_.at(i);
        }
    }

    // Access Functions

    int Graph::findNearestNeighbor(const std::pair<double, double> &location) const {
        return locations_.findNearestNeighbor(Point<2>(location.first, location.second));
    }

    const encounter* Graph::getNode(int id) const {
        if (id == -1 || id >= (int)(nodes_.size())) return NULL;
        return nodes_.at(id);
    }

    std::list<encounter*> Graph::getShortestPathDijk(const std::pair<double, double> &start, const std::pair<double, double> &end) {
        int startIndex = findNearestNeighbor(start);
        int endIndex = findNearestNeighbor(end);

        // Get spanning tree
        if (startIndex == -1) return list<encounter*>();
        vector<int> tree = getSpanningTreeDijk(startIndex);
        if (tree.at(endIndex) == -2) {
            return list<encounter*>();
        }

        // Create path from end
        std::list<encounter*> path;
        path.push_front(nodes_.at(endIndex));
        int currentIndex = tree.at(endIndex);

        // Backtrack from end to begining
        while (currentIndex >= 0) {
            path.push_front(nodes_.at(currentIndex));
            currentIndex = tree.at(currentIndex);
        }

        return path;
    }
    
    vector<int> Graph::getSpanningTreeDijk(int start) {
        vector<int> parents(nodes_.size(), -2);
        vector<double> distance(nodes_.size(), INFINITY);
        heap<encounter::edge> min_heap(nodes_.at(start)->neighbors);
        vector<bool> addedToGraph(nodes_.size(), false);

        parents.at(start) = -1;
        distance.at(start) = 0;
        addedToGraph.at(start) = true;

        for (size_t idx = 0; idx < nodes_.at(start)->neighbors.size(); ++idx) {
            parents.at(nodes_.at(start)->neighbors.at(idx).end_id) = start;
        }

        while (!min_heap.empty()) {
            // Get next shortest edge not added to graph
            encounter::edge edge = min_heap.pop();
            while (addedToGraph.at(edge.end_id)) {
                edge = min_heap.pop();
            }
            addedToGraph.at(edge.end_id) = true;

            for (encounter::edge &adj_edge : nodes_.at(edge.end_id)->neighbors) {
                // Parse new frontier edges

                if (!addedToGraph.at(adj_edge.end_id)) {
                    // If shorter edge found, update heap and records
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
        int startIndex = g.findNearestNeighbor(start);
        master_ = Traversals::getBFSTraversal(g.nodes_, startIndex);
    }

    Graph::DFS::DFS(const Graph &g, const std::pair<double, double> &start) {
        int startIndex = g.findNearestNeighbor(start);
        master_  = Traversals::getDFSTraversal(g.nodes_, startIndex);
    }
    
} // namespace encounters