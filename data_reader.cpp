#include "data_reader.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace encounters {
    using std::string;
    using std::vector;

    const double DataReader::DISTANCE_THRESHOLD = 50.0;
    const string DataReader::DESIRED_STATE = "il";

    vector<encounter*> DataReader::readFromFile(const string &file_name) {
        std::fstream fin;
        fin.open(file_name, std::ios::in);

        vector<encounter*> nodes;
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
            if (components.size() < NUM_COLUMNS || components.at(STATE_COLUMN) != DESIRED_STATE) {
                continue;
            }

            // parse columns to managable form
            double lat = parseDouble(components.at(LATITUDE_COLUMN));
            double longit = parseDouble(components.at(LONGITUDE_COLUMN));

            // don't add to list if values could not be parsed
            if (lat == 0 || longit == 0) {
                continue;
            }

            encounter *newEncounter = new encounter(lat, longit, idNum);
            nodes.push_back(newEncounter);
            idNum++;
            
            // Move withinTime pointer to point to the oldest record within the time threshold
            bool updated = false;
        }

        linkNodes(nodes);

        return nodes;
    }

    double DataReader::parseDouble(const std::string &doubleStr) {
        try {
            return std::stod(doubleStr);
        } catch (std::invalid_argument e) {} catch (std::out_of_range e) {}
        return 0;
    }

    void DataReader::linkNodes(vector<encounter*> &nodes) {
        for (size_t f_index = 0; f_index < nodes.size(); f_index++) {
            encounter &first = *nodes.at(f_index);

            for (size_t l_index = f_index + 1; l_index < nodes.size(); l_index++) {
                encounter &second = *nodes.at(l_index);
                double distance = dist(first, second);

                if (distance < DISTANCE_THRESHOLD) {
                    first.neighbors.push_back(encounter::edge(first.id, second.id, distance));
                    second.neighbors.push_back(encounter::edge(second.id, first.id, distance));
                }
            }
            std::sort(first.neighbors.begin(), first.neighbors.end());
        }
    }
} // namespace encounters