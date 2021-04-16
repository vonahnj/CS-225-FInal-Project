#include "graph.h"
#include "encounter.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace encounters {
    Graph::Graph(const std::string &file_name) {
        std::fstream fin;
        fin.open(file_name, std::ios::in);

        int index = 0;
        int missedEntries = 0;
  
        while (fin.good() && index < 5) {
            index++;
            std::string line, word;
            getline(fin, line);
            std::stringstream s(line);
            std::vector<std::string> components;

            while (getline(s, word, ',')) {
                components.push_back(word);
            }

            if (components.size() < 11) {
                missedEntries++;
                continue;
            }

            std::string timestamp = components.at(0);
            std::string latitude = components.at(9);
            std::string longitude = components.at(10);

            //std::cout<<timestamp<<'\t'<<latitude<<'\t'<<longitude<<'\t'<<std::endl;
            date d = parseDate(timestamp);
            double lat = parseDouble(latitude);
            double longit = parseDouble(longitude);
        }
    }

    date Graph::parseDate(const std::string &dateStr) {
        std::string part;
        std::stringstream s(dateStr);
        std::vector<std::string> components;

        while (getline(s, part, '/')) {
            if (components.size() == 2) {
                components.push_back(part.substr(0, 4));
            } else {
                components.push_back(part);
            }
        }

        if (components.size() == 3) {
            try {
                return date(std::stoi(components.at(1)), std::stoi(components.at(0)), std::stoi(components.at(2)));
            } catch (std::invalid_argument e) {} 
            catch (std::out_of_range e) {}
        }
        return date();
    }

    double Graph::parseDouble(const std::string &doubleStr) {
        return 0;
    }
}