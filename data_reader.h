#pragma once

#include <vector>
#include <string>
#include "encounter.h"

namespace encounters {
    using std::vector;
    using std::string;

    class DataReader {
        public: 
        static const size_t NUM_COLUMNS = 11;
        static const size_t DATE_COLUMN = 0;
        static const size_t STATE_COLUMN = 2;
        static const size_t LATITUDE_COLUMN = 9;
        static const size_t LONGITUDE_COLUMN = 10;

        static const double TIME_THRESHOLD;
        static const double DISTANCE_THRESHOLD;
        static const string DESIRED_STATE;

        static vector<encounter*> readFromFile(const string &fileName);
        
        private:
        static date parseDate(const std::string &dateStr);
        static double parseDouble(const std::string &doubleStr);
        static void linkNodesDistanceWise(vector<encounter*> &nodes);
        static void linkNodesTimeWise(vector<encounter*> &nodes);
    };
} // namespace encounters