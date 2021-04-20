#include "graph.h"
#include "encounter.h"
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
    
} // namespace encounters