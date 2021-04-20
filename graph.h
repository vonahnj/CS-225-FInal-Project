#pragma once

#include <string>
#include "encounter.h"
#include "kd_tree/kdtree.h"

namespace encounters {
    class Graph {        
        public: 
        /**
         * Constructs an empy Graph
         */
        Graph();

        /**
         * Constructs a Graph with data from a csv file
         * @param file_name the path to the csv file holding the graph data
         */
        Graph(const std::string &file_name);

        /**
         * Deallocates the memory to prevent memory leaks
         */
        ~Graph();

        private:
        KDTree locations_;
        vector<encounter*> nodes_;
    };
} // namespace encounters