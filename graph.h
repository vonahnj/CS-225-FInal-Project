#pragma once

#include <string>
#include "encounter.h"
#include "kdtree.h"

namespace encounters {
    class Graph {        
        public: 
        Graph();
        Graph(const std::string &file_name);

        private:
        KDTree nodes_;
    };
} // namespace encounters