#include "graph.h"
#include "encounter.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


namespace encounters {

    Graph::Graph(const std::string &file_name) {
        // open file
        std::fstream fin;
        fin.open(file_name, std::ios::in);

        int missedEntries = 0;
        int wrongState = 0;
        int linkTime = 0;
        size_t withinTime = 0;
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
            if (components.size() < NUM_COLUMNS || components.at(STATE_COLUMN) != desired_state) {
                wrongState++;
                missedEntries++;
                continue;
            }

            // parse columns to managable form
            date d = parseDate(components.at(DATE_COLUMN));
            double lat = parseDouble(components.at(LATITUDE_COLUMN));
            double longit = parseDouble(components.at(LONGITUDE_COLUMN));

            // add to list of nodes if values all exist
            if (d.year == 0 || lat == 0 || longit == 0) {
                missedEntries++;
            } else {
                encounter *newEncounter = new encounter(d, lat, longit);
                nodes_.push_back(newEncounter);
                
                bool updated = false;
                while (!updated && withinTime < nodes_.size() - 1) {
                    if (dist(nodes_.at(withinTime)->time, nodes_.back()->time) > TIME_THRESHOLD ) {
                        withinTime++;
                    } else updated = true;
                }

                for (size_t index = withinTime; index < nodes_.size() - 1; index++) {
                    linkTime++;
                    linkTimewise(index, nodes_.size() - 1);
                }
            }
        }

        linkNodes();

        std::cout<<"missed: "<<missedEntries<<std::endl;
        std::cout<<"worked: "<<nodes_.size()<<std::endl;
        std::cout<<"linked timewise: "<<linkTime<<std::endl;
        std::cout<<"wrong state: "<<wrongState<<std::endl;
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

    void Graph::linkNodes() {
        int linkDist = 0;

        for (size_t f_index = 0; f_index < nodes_.size(); f_index++) {
            encounter &first = *nodes_.at(f_index);
            bool unlinked = true;

            for (size_t l_index = f_index + 1; l_index < nodes_.size(); l_index++) {
                encounter &second = *nodes_.at(l_index);

                if (dist(first, second) < DISTANCE_THRESHOLD) {
                    linkDist++;
                    unlinked = false;
                }
            }

            if (unlinked) {
                std::cout<<"unlinked @"<<*nodes_.at(f_index)<<std::endl;
            }
        }

        std::cout<<"linked distance: "<<linkDist<<std::endl;
    }

    void Graph::linkTimewise(size_t firstIndex, size_t secondIndex) {
        encounter *first = nodes_.at(firstIndex);
        encounter *second = nodes_.at(secondIndex);
        double timeDist = dist(first->time, second->time);

        first->time_neighbors.push_back(encounter::edge(*first, *second, timeDist));
        second->time_neighbors.push_back(encounter::edge(*second, *first, timeDist));
    }
}