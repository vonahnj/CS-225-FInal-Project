#include "graph.h"
#include "encounter.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


namespace encounters {
    const size_t Graph::NUM_COLUMNS = 11;

    Graph::Graph(const std::string &file_name) {
        // open file
        std::fstream fin;
        fin.open(file_name, std::ios::in);

        int missedEntries = 0;
        while (fin.good()) {
            // Read in columns of line
            std::string line, word;
            getline(fin, line);
            std::stringstream s(line);
            std::vector<std::string> components;
            while (getline(s, word, ',')) {
                components.push_back(word);
            }

            // Ensure there are enough columns in the line
            if (components.size() < NUM_COLUMNS) {
                missedEntries++;
                continue;
            }

            // parse columns to managable form
            date d = parseDate(components.at(0));
            double lat = parseDouble(components.at(9));
            double longit = parseDouble(components.at(10));

            // add to list of nodes if values all exist
            if (d.year == 0 || lat == 0 || longit == 0) {
                missedEntries++;
            } else {
                encounter *newEncounter = new encounter(d, lat, longit);
                nodes_.push_back(newEncounter);
            }
        }

        std::cout<<"missed: "<<missedEntries<<std::endl;
        std::cout<<"worked: "<<nodes_.size()<<std::endl;
        std::cout<<"read: "<<(1 - (double)(missedEntries)/(missedEntries + nodes_.size()))<<std::endl;
    }

    Graph::~Graph() {
        for (size_t index = 0; index < nodes_.size(); ++index) {
            delete nodes_.at(index);
        }
    }

    date Graph::parseDate(const std::string &dateStr) {
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

    double Graph::parseDouble(const std::string &doubleStr) {
        try {
            return std::stod(doubleStr);
        } catch (std::invalid_argument e) {} catch (std::out_of_range e) {}
        return 0;
    }
}