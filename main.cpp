/**
 * @file main.cpp
 * A simple program that allocates students to rooms.
 */
#include <iostream>

#include "avl_tree.h"
#include "data_reader.h"
#include "kd_tree.h"

using namespace encounters;

/**
 * Main routine.
 * Creates an Allocator object and allocates the students.
 */
int main()
{
    std::cout << "Hello World!" << std::endl;
    KDTree kd;
    std::cout<<kd.exists()<<std::endl;

    AVLTree avl;
    std::cout<<avl.exists()<<std::endl;

	DataReader data;
    std::cout<<data.exists()<<std::endl;
    return 0;
}
