# CS 225 Data Structures
## Development (ahqiu2-pzy2-jvonahn2-merchia2)

##### May 16th to May 22nd 
The code was written to read the data from the csv file into a graph in **data_reader.h/cpp**. Useful structs and comparision functions to measure distance and compare location and distance were written in **encounter.h/cpp**. The KDTree from mp_mosaics was transfered over and adapted to be able to build off of a vector of encounter pointers, using the locations as node keys and the id number of the encounter as node values. This was done in **kdtree/point.h/hpp** and **kdtree/kdtree.h/cpp**. The make file was updated accordingly and test cases were written for each file in the tests directory.