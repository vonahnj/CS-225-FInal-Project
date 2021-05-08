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
        // Get approximate location
        int index = locations_.findNearestNeighbor(Point<2>(location.first, location.second));
        
        // Return node with lowest index at this location
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
        // Get spanning tree
        if (startIndex == -1 || endIndex == -1) return list<const encounter*>();
        vector<int> tree = getSpanningTreeDijk(startIndex);
        if (tree.at(endIndex) == -2) {
            return list<const encounter*>();
        }

        // Create path from end
        std::list<const encounter*> path;
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

    vector<double> Graph::getBetweennessValues() {
        vector<double> values = vector<double>(nodes_.size(), 0.0);
        vector<int> tree;
        for(int i = 0; i < (int)nodes_.size(); i++) {
            tree = getSpanningTreeDijk(i);
            for(int j = 0; j < (int)nodes_.size(); j++) {
                if(tree[j] != -2 && tree[j] != -1) {
                    int curr = j;
                    while(tree[curr] != -1) {
                        values[curr]++;
                        curr = tree[curr];
                    }
                    values[curr]++;
                }
            }
        }
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