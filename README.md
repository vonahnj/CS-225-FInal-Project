# ahqiu2-pzy2-jvonahn2-merchia2

## [Project Proposal](documents/project_proposal.md)
## [Contract](documents/contract.md)


## Locations
1. Major Code
   * data_reader.h and data_reader.cpp
     * Read Data from CSV File
     * Create Nodes on the heap and link in O(n<sup>2</sup>)
   * encounter.h and encounter.cpp
     * Define encounter node content and data stored in edges
     * Create distance method to determine distance between latitude and longitudinal coordinates in kilometers
     * Write comparision methods between edges to allow for sorting
   * graph.h and graph.cpp 
     * Store graph data
     * Implementation of graph algorithms
     * Implementation of iterators
     * Free up memory to prevent memory leaks
   * traversals.h and traversals.cpp
     * Determine order for BFS and DFS traversals
   * main.cpp
     * Location of executable to run algorithms on the code from the command line
   * /tests
     * Folder that holds test files and test data
   * /kdtree and /heap
     * Folders holding assignments from mp_mosaics and lap_heaps that have been modified slightly to take encounters and edges instead of raw data

2. Data
   * main data with all information = data.csv
   * shorter testing data = tests/test_data/*.csv

3. Results
   * The results of running this code appear where the user specifies in the command line 

## How to Build/Run Executables

#### Building
1. Ensure you have the necessary software downloaded and set up. The software necessary is the same as the software required for CS 225 at UIUC. Instructions on how to set up this software can be found [here](https://courses.engr.illinois.edu/cs225/sp2021/resources/own-machine/) 
2. Clone this repository by running: 
    `git clone https://github-dev.cs.illinois.edu/cs225-sp21/ahqiu2-pzy2-jvonahn2-merchia2.git`
3. Run: 
   `make`

#### Running
There are two options as to how you can run executables on this machine. You can use the executable to run either a centrality or a shortest path algorithm

Both options will require you to first enter the location of your data and the desired output location. 

**Centrality Algorithm**
Syntax: 
`./encounters [DATA_FILE] [OUTPUT_FILE] [NUM_DESIRED_CENTRAL_NODES]`

Example: 
`./encounters data.csv output.txt 10`
executes such that if you enter the following command, the data from data.csv will be read and the 10 most central nodes will be written to output.txt

**Shortest Path Algorithm**
Syntax: 
`./encounters [DATA_FILE] [OUTPUT_FILE] [START_LATITUDE] [START_LONGITUDE] [END_LATITUDE] [END_LONGITUDE]`

Example: 
`./encounters data.csv output.txt 40.6936111 -89.5888889 41.5094444 -90.5786111`
executes such that if you enter the following command, the data from data.csv will be read and the nodes you must visit to take the shortest path from (40.6936111, -89.5888889) to (41.5094444, -90.5786111) will be written to output.txt. If there is no way to make the trip without going more than 50 kilometers without encountering an encounter location, there will be no output in the file

#### Defining Input Data
Your data location must be the first argument in the executable
If interacting directly with the code, the data location must be inputted as a string into the constructor of the Graph.

Data must be entered in a CSV file with the following columns in this order 
> datetime,city,state,country,shape,duration (seconds),duration (hours/min),comments,date posted,latitude,longitude
such that a valid row reads:
> 10/10/1993 22:00,peoria,il,us,light,8,8 seconds,"AHHH Super Scary Alien!",10/11/2005,40.6936111,-89.5888889

The state listed **must be il** because the data_reader only processes encounters listed in illinois. It will ignore any data for which the state is undefined, the state is not "il", there are the wrong number of columns, or the latitude/longitude are 0.

#### Defining Output Location
Your output location must be the second argument in the executable. 
See [Running](running) for more details

## How to Build/Run Test Suite
1. If you have not already done so, ensure you have done the first two steps defined in [Building](building)
2. Run: 
   `make test`

### Test Descriptions

#### test_betweenness.cpp
* 

#### test_datareader.cpp
* Tests to ensure that DataReader reads all valid records
* Tests to ensure that DataReader links the correct nodes
* Tests to ensure that DataReader ignores erroneous records and gibberish
  
#### test_dijstrakas.cpp
* Tests getShortestPathDijk to ensure it gets the shortest path from different data sets. 
* Tests with a small cycle and unconnected node as well as the points visualized [here](https://www.google.com/maps/d/u/0/edit?mid=1mdRbpRLo7sXlOq7Q9xYIfFJLHTtmq_Dd&usp=sharing)  

#### test_encounters.cpp
* Tests to ensure distance calculator is approximately correct
* Tests the comparision operators for edges
* Tests the == operator for encounters

#### test_kdtree.cpp
* Ensures findNearestNeighbor works correctly despite minor alterations to codebase so it accepts encounters. Tests are not exhaustive as most of the functionality is identical to the ones tested by mp_mosaics

#### test_traversals.cpp
* Ensures nodes are visited in the correct order for BFS and DFS traversals. Tests are run based on multiple different starting points on each data set
* The traversals are each run on two sets of data. A small set of 4 nodes and a larger set of 312 nodes