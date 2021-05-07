#include "../cs225/catch/catch.hpp"
#include "../data_reader.h"
#include "../graph.h"

#include <vector>
#include <iostream>

using namespace encounters;

TEST_CASE("test") {
    Graph graph("tests/test_data/large_data.csv");
    vector<double> values = graph.getBetweennessValues();
    vector<double> highest = vector<double>(10, 0);
    for(int i = 0; i < (int)values.size(); i++) {
        if(values[i] > highest[9]) {
            for(int j = 0; j < 10; j++) {
                if(values[i] > highest[j]) {
                    int curr = 9;
                    while(curr > i) {
                        highest[curr] = highest[curr - 1];
                        curr--;
                    } 
                    highest[j] = values[i];
                    break;
                }
            }
        }
    }
    for(int i = 0; i < 10; i++) {
        std::cout << highest[i] << std::endl;
    }
}