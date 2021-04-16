#pragma once

#include <string>
#include "encounter.h"

namespace encounters {
    class Graph {
        public: 
        Graph(const std::string &file_name);
        ~Graph();

        date parseDate(const std::string &dateStr);
        double parseDouble(const std::string &doubleStr);

        private:
        std::vector<encounter*> nodes_;
    };
}