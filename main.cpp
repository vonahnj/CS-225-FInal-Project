/**
 * @file main.cpp
 * A simple program that allocates students to rooms.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include "encounter.h"
#include "graph.h"

using namespace encounters;

void printNodes(const std::list<const encounter*> nodes, const std::string &fileName) {
    std::fstream fout;
    fout.open(fileName, std::ios::out);

    for (const encounter* e : nodes){
        fout<<(*e)<<"\n";
        std::cout<<(*e)<<std::endl;
    }

    fout.close();
}

/**
 * Main routine.
 * Executatble arguments required: 
 * Must have: 
 *  1.) Data file name
 *  2.) Output file name
 *  
 * First Option: 
 *  List 2 pairs of coordinates to determine the shortest path between the 2 points
 *  ex) data.csv output.txt -13.584995 18.3439342 -15.584995 19.3439342
 *      Will load the data from data.csv and output the shortest path that goes from 
 *      (-13.584995, 18.3439342) and (-15.584995, 19.3439342)
 * 
 *  List 1 integer to determine nth most central nodes
 */
int main(int argc, char *argv[])
{
    std::cout << "Hello Friends! " << std::endl;
    if (argc < 3) {
        std::cout<< "Please enter the names both your data file and your output file on the command line" <<std::endl;
        return 1;
    } 
    Graph graph(argv[1]);
    std::cout<<"Found "<<graph.getNodeCount()<<" valid encounters"<<std::endl;

    if (argc == 4) {
        // Centrality
        std::cout<<"Centrality! ";
        int numEntered = std::stoi(argv[3]);
        if (numEntered <= 0) {
            std::cout<<"Please input a positive number of nodes"<<std::endl;
            return 1;
        }
        std::cout<<"Getting "<<numEntered<<" most central nodes"<<std::endl;

        vector<double> values = graph.getBetweennessValues();
        std::cout<<"Centralities Calculated! Determining most central"<<std::endl;
        vector<std::pair<double, size_t> > pairs (values.size());
        for (size_t idx = 0; idx < values.size(); ++idx) {
            pairs.at(idx) = std::pair<double, size_t>(values.at(idx), idx);
        }
        std::sort(pairs.begin(), pairs.end(), std::greater<std::pair<double, size_t>>());

        size_t numDesired = std::min((int)(values.size()), numEntered);
        std::list<const encounter*> nodes;
        for (size_t idx = 0; idx < numDesired; ++idx) {
            nodes.push_back(graph.getNode(pairs.at(idx).second));
        }
        std::cout<<"Outputting data!"<<std::endl;
        printNodes(nodes, argv[2]);

    } else if (argc == 7) {
        // Shortest Path
        std::pair<double, double> start(std::stod(argv[3]), std::stod(argv[4]));
        std::pair<double, double> end(std::stod(argv[5]), std::stod(argv[6]));

        std::list<const encounter*> path = graph.getShortestPathDijk(start, end);
        printNodes(path, argv[2]);

    } else {
        // Incorrect number of arguments
        std::cout<< "Incorrect number of arguments. Please follow the instructions in the READMe"<<std::endl;
        return 1;
    }

    std::cout<<"Thanks for using Encounters!"<<std::endl;
    return 0;
}
