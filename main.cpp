/**
 * @file main.cpp
 * A simple program that allocates students to rooms.
 */
#include <iostream>
#include "encounter.h"
#include "graph.h"

using namespace encounters;

/**
 * Main routine.
 * Executatble arguments required: 
 * Must have: 
 *  1.) Data file name
 *  2.) Output file name
 *  
 * First Option: 
 *  List 2 coordinates to determine the shortest path between the 2 points
 *  ex) data.csv output.txt -13.584995 18.3439342
 * 
 *  List 1 integer to determine nth most central nodes
 */
int main(int argc, char *argv[])
{
    std::cout << "Hello Friends!" << std::endl;
    if (argc < 2) {
        std::cout<< "Please enter the names both your data file and your output file on the command line" <<std::endl;
        return 1;
    } 
    Graph graph(argv[0]);

    if (argc == 3) {
        // Centrality
    } else if (argc == 4) {
        // Shortest Path
    } else {
        // Incorrect number of arguments
    }
    return 0;
}
