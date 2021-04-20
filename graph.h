#pragma once

#include <string>
#include "encounter.h"
#include "kd_tree/kdtree.h"

namespace encounters {
    class Graph {        
        public: 
        Graph();
        ~Graph();
        Graph(const std::string &file_name);

        private:
        KDTree locations_;
        vector<encounter*> nodes_;
    };
} // namespace encounters