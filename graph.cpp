#include "graph.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace encounters {
    Graph::Graph(const std::string &file_name) {
        std::cout<<"Graph constructor"<<std::endl;
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

            std::cout<<timestamp<<'\t'<<latitude<<'\t'<<longitude<<'\t'<<std::endl;
        }
    }
}