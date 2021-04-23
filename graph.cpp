#include "graph.h"
#include "encounter.h"
#include "traversals.h"
#include "data_reader.h"
#include "kdtree/kdtree.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


namespace encounters {
    using std::vector;

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

    int Graph::findNearestNeighbor(const std::pair<double, double> &location) const {
        return locations_.findNearestNeighbor(Point<2>(location.first, location.second));
    }

    const encounter* Graph::getNode(int id) const {
        if (id == -1 || id >= (int)(nodes_.size())) return NULL;
        return nodes_.at(id);
    }

    Graph::traversal::iterator::iterator(const iterator &other) {
        order = other.order;
    }
    
    Graph::traversal::iterator::iterator(const std::list<encounter*> &desiredOrder) {
        order = desiredOrder;
    }

    const Graph::traversal::iterator& Graph::traversal::iterator::operator=(const iterator& rhs) {
        if (this != &rhs) {
            order = rhs.order;
        }
        return *this;
    }
    
    const Graph::traversal::iterator& Graph::traversal::iterator::operator++() {
        if (!order.empty()) {
            order.pop_front();
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
        Graph::traversal::iterator it;
        return it;
    }

    Graph::traversal::iterator Graph::traversal::begin() {
        return Graph::traversal::iterator(master_);
    }

    Graph::BFS::BFS(const Graph &g, const std::pair<double, double> &start) {
        int startIndex = g.findNearestNeighbor(start);
        vector<encounter*> traversal = Traversals::getBFSTraversal(g.nodes_, startIndex);
        
        while(!traversal.empty()) {
            master_.push_front(traversal.back());
            traversal.pop_back();
        }
    }

    Graph::DFS::DFS(const Graph &g, const std::pair<double, double> &start) {
        int startIndex = g.findNearestNeighbor(start);
        vector<encounter*> traversal = Traversals::getDFSTraversal(g.nodes_, startIndex);
        
        while(!traversal.empty()) {
            master_.push_front(traversal.back());
            traversal.pop_back();
        }
    }
    
} // namespace encounters