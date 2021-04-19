#include "graph.h"
#include "encounter.h"
#include "data_reader.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


namespace encounters {
    using std::vector;

    Graph::Graph() {}

    Graph::Graph(const std::string &file_name) {
        vector<encounter*> encounters = DataReader::readFromFile(file_name);
        nodes_ = KDTree(encounters);
    }
    
} // namespace encounters