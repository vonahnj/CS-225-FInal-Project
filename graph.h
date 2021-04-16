#pragma once

#include <string>
#include "encounter.h"

namespace encounters {
    class Graph {
        static const size_t NUM_COLUMNS = 11;
        static const size_t DATE_COLUMN = 0;
        static const size_t STATE_COLUMN = 2;
        static const size_t LATITUDE_COLUMN = 9;
        static const size_t LONGITUDE_COLUMN = 10;

        const std::string desired_state = "il";
        const double DISTANCE_THRESHOLD = 10.0;
        const double TIME_THRESHOLD = 7.0;
        

        public: 
        Graph(const std::string &file_name);
        ~Graph();

        date parseDate(const std::string &dateStr);
        double parseDouble(const std::string &doubleStr);

        private:
        std::vector<encounter*> nodes_;
        void linkNodesDistanceWise();
        void linkTimewise(size_t firstIndex, size_t secondIndex);
    };
}