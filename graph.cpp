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

    vector<double> Graph::getBetweennessValues() {
        vector<double> values = vector<double>(nodes_.size(), 0.0);
        vector<int> tree;
        // vector<vector<int> > test_trees; 
        // vector<int> tree1 = {-1, 0, -2, 0};
        // vector<int> tree2 = {1, -1, -2, 1};
        // vector<int> tree3 = {-2, -2, -1, -2};
        // vector<int> tree4 = {3, 3, -2, -1};
        // test_trees.push_back(tree1); 
        // test_trees.push_back(tree2); 
        // test_trees.push_back(tree3); 
        // test_trees.push_back(tree4); 

        for(int i = 0; i < (int)nodes_.size(); i++) {
            tree = getSpanningTreeDijk(i);
            //tree = test_trees[i];
            for(int j = 0; j < (int)nodes_.size(); j++) {
                if(tree[j] != -2 && tree[j] != -1) {
                    int curr = j;
                    while(tree[curr] != -1) {
                        values[curr]++;
                        curr = tree[curr];
                    }
                    values[curr]++;
                }
                std::cout << tree[j];
            }
            std::cout << std::endl;
        }
        for(int i = 0; i < (int)nodes_.size(); i++) {
            values[i] /= nodes_.size() * (nodes_.size() - 1);
            std::cout << values[i] << std::endl;
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
        int startIndex = g.findNearestNeighbor(start);
        master_ = Traversals::getBFSTraversal(g.nodes_, startIndex);
    }

    Graph::DFS::DFS(const Graph &g, const std::pair<double, double> &start) {
        int startIndex = g.findNearestNeighbor(start);
        master_  = Traversals::getDFSTraversal(g.nodes_, startIndex);
    }
    
} // namespace encounters