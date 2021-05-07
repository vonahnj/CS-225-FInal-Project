#include "../cs225/catch/catch.hpp"
#include "../data_reader.h"
#include "../graph.h"

#include <vector>
#include <iostream>

using namespace encounters;

TEST_CASE("test") {
    Graph graph("tests/test_data/large_data.csv");
    vector<double> values = graph.getBetweennessValues();
    int num = 10;
    if(num > graph.getNodeCount()) {return;}
    vector<double> highest = vector<double>(num, 0);
    for(int i = 0; i < (int)values.size(); i++) {
        if(values[i] > highest[num - 1]) {
            for(int j = 0; j < num; j++) {
                if(values[i] > highest[j]) {
                    int curr = num - 1;
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
    for(int i = 0; i < num; i++) {
        std::cout << highest[i] << std::endl;
    }
}