#pragma once

#include <vector>
#include <string>
#include "encounter.h"

namespace encounters {
    using std::vector;
    using std::string;

    class DataReader {
        public: 
        // Information about the structure of the csv file
        static const size_t NUM_COLUMNS = 11;
        static const size_t DATE_COLUMN = 0;
        static const size_t STATE_COLUMN = 2;
        static const size_t LATITUDE_COLUMN = 9;
        static const size_t LONGITUDE_COLUMN = 10;

        static const double TIME_THRESHOLD; // The time (in days) within two encounters must fall to be time neighbors
        static const double DISTANCE_THRESHOLD; // The distance (in kilometers) within two encounters must fall to be location neighbors
        static const string DESIRED_STATE;

        /**
         * Reads data from a csv file into encounter nodes. This ignores 
         * data that does not have the following required fields: 
         * 1. Longitude
         * 2. Latitude
         * 3. Timestamp
         * 
         * It also connects all nodes to encounters that occurred around the same
         * time or near the same location (time neighbors and location neighbors) while
         * assigning a unique id number to each node such that the n is the id of the
         * nth valid loaded data point.
         * 
         * @param fileName the name of the csv file where the data resides
         * @return all encounters in the csv file linked to encounters with similar time and location
         */
        static vector<encounter*> readFromFile(const string &fileName);
        
        private:
        /**
         * Converts string into date struct
         * @param dateStr the date in 'MM/DD/YYYY 00:00' form
         * @return a struct holding the month, day, and year defined in the dateStr; 
         *         if the string does not hold a valid date, the method returns the default date
         */
        static date parseDate(const std::string &dateStr);

        /**
         * Converts string into date struct
         * @param doubleStr a double in string form
         * @return the double represented in the string
         */
        static double parseDouble(const std::string &doubleStr);

        /**
         * Links nodes with distance edges, making them location neighbors, if they fall 
         * within a given radius of each other
         * @param nodes the nodes to be linked
         */
        static void linkNodesDistanceWise(vector<encounter*> &nodes);

        /**
         * Links nodes with time edges, making them time neighbors, if they fall 
         * within a given time range of each other
         * @param nodes the nodes to be linked
         */
        static void linkNodesTimeWise(vector<encounter*> &nodes);
    };
} // namespace encounters