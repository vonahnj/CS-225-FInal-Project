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
 * Creates an Allocator object and allocates the students.
 */
int main()
{
    std::cout << "Hello World!" << std::endl;
    Graph graph("data.csv");
    Graph::DFS dfs(graph, std::pair<double, double>(36.7477778,-119.7713889));
    return 0;
}
