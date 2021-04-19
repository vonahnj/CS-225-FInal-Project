#include "data_reader.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace encounters {
    using std::string;
    using std::vector;

    const double DataReader::TIME_THRESHOLD = 7.0;
    const double DataReader::DISTANCE_THRESHOLD = 10.0;
    const string DataReader::DESIRED_STATE = "il";

    vector<encounter*> DataReader::readFromFile(const string &file_name) {
        std::fstream fin;
        fin.open(file_name, std::ios::in);

        vector<encounter*> nodes;
        
        size_t withinTime = 0;
        size_t idNum = 0;
        
        while (fin.good()) {
            // Read in columns of line
            std::string line, word;
            getline(fin, line);
            std::stringstream s(line);
            std::vector<std::string> components;
            while (getline(s, word, ',')) {
                components.push_back(word);
            }

            // Ensure there are enough columns in the line and the encounter is in the correct state
            if (components.size() < NUM_COLUMNS /*|| components.at(STATE_COLUMN) != DESIRED_STATE */) {
                continue;
            }

            // parse columns to managable form
            date d = parseDate(components.at(DATE_COLUMN));
            double lat = parseDouble(components.at(LATITUDE_COLUMN));
            double longit = parseDouble(components.at(LONGITUDE_COLUMN));

            // don't add to list if values could not be parsed
            if (d.year == 0 || lat == 0 || longit == 0) {
                continue;
            }

            encounter *newEncounter = new encounter(d, lat, longit, idNum++);
            nodes.push_back(newEncounter);
            
            // Move withinTime pointer to point to the oldest record within the time threshold
            bool updated = false;
            while (!updated && withinTime < nodes.size() - 1) {
                if (dist(nodes.at(withinTime)->time, nodes.back()->time) > TIME_THRESHOLD ) {
                    withinTime++;
                } else updated = true;
            }

            // Link all records to older records within the time threshold
            for (size_t index = withinTime; index < nodes.size() - 1; index++) {
                linkTimewise(nodes, index, nodes.size() - 1);
            }
            
        }

        linkNodesDistanceWise(nodes);

        return nodes;
    }

    date DataReader::parseDate(const std::string &dateStr) {
        std::string part;
        std::stringstream s(dateStr);
        std::vector<std::string> components;

        // Collect components of date to form [month, day, year]
        while (getline(s, part, '/')) {
            if (components.size() == 2) {
                components.push_back(part.substr(0, 4));
            } else {
                components.push_back(part);
            }
        }

        // parse components to translate into ints
        if (components.size() == 3) {
            try {
                return date(std::stoi(components.at(1)), std::stoi(components.at(0)), std::stoi(components.at(2)));
            } catch (std::invalid_argument e) {} catch (std::out_of_range e) {}
        }
        return date();
    }

    double DataReader::parseDouble(const std::string &doubleStr) {
        try {
            return std::stod(doubleStr);
        } catch (std::invalid_argument e) {} catch (std::out_of_range e) {}
        return 0;
    }

    void DataReader::linkNodesDistanceWise(vector<encounter*> &nodes) {
        for (size_t f_index = 0; f_index < nodes.size(); f_index++) {
            encounter &first = *nodes.at(f_index);

            for (size_t l_index = f_index + 1; l_index < nodes.size(); l_index++) {
                encounter &second = *nodes.at(l_index);
                double locDist = dist(first, second);

                if (locDist < DISTANCE_THRESHOLD) {
                    first.time_neighbors.push_back(encounter::edge(first, second, locDist));
                    second.time_neighbors.push_back(encounter::edge(second, first, locDist));
                }
            }
        }
    }

    void DataReader::linkTimewise(vector<encounter*> &nodes, size_t firstIndex, size_t secondIndex) {
        encounter *first = nodes.at(firstIndex);
        encounter *second = nodes.at(secondIndex);
        double timeDist = dist(first->time, second->time);

        first->time_neighbors.push_back(encounter::edge(*first, *second, timeDist));
        second->time_neighbors.push_back(encounter::edge(*second, *first, timeDist));
    }
} // namespace encounters