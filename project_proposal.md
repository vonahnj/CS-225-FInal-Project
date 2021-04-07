# CS 225 Data Structures
## Project Proposal (ahqiu2-pzy2-jvonahn2-merchia2)

1. **Leading Question** Given a location or time period, we would like to evaluate nearby UFO encounters or sightings and plot them on a map. 

2. **Dataset Acquistion and Processing** We propose using the [UFO Sightings Kaggle Dataset](https://www.kaggle.com/NUFORC/ufo-sightings). We will focus on the location given by latitude and longitude as well as the timestamps of each encounter in this dataset. This data is provided in a `*.csv` format, and we will cite this reference from [Geeks for Geeks](https://www.geeksforgeeks.org/csv-file-management-using-c/) to load the data into a KD-Tree keyed to latitude and longitude as well as an AVL Tree keyed to timestamps. The values of each node in the KD-Tree and AVL Tree will be a pointer to a struct holding the data for that encounter. For our graph structure, we propose that each column will represent a range of dates and the height of the columns will correspond with the frequency of encounters during that time period. We recognize that this data is large, and potentially error-ridden; thus, we will drop any records that don't contain all three of the required fields for our purposes (latitude, longitude, and timestamp) and/or any malformed records.

3. **Graph Algorithms** For our graph traversal, we propose to implement an inorder traversal for dates through the AVL Tree.
   
For one of our algorithms, we propose implementing a modified findNearestNeighbor algorithm which instead of simply seeking out the closest neighbor, returns a queried number of closest neighbors. For instance if you passed in a location and the number 4, you would get the 4 closest encounters to your location. 
   
For our other algorithms, we propose implementing a second modified findNearestNeighbor algorithm which instead of simply seeking out the closest neighbor or number of closest neighbors, it returns all encounters that occured within a given radius of the query. For example, if you passed in a location and 4, it would return all the locations within 4 miles. 

To help with graph creation, we will also create a way to find the closest timestamp to a given time using the AVL Tree so we can query start and end times before traversing our way from the start node to the end node.

1. **Timeline** 

   April 7 - sync to complete project proposal and team contract
   
   April 9 - submit project proposal and team contract
   
   April 12 - set up initial repository and Makefile
   
   April 15 - finish reading in data AVL Tree format and write simple tests to verify correctness
   
   April 19 - use traversal of AVL Tree to create KD Tree
   
   April 22 - write first modified findNearestNeighbor algorithim
   
   April 29 - write second modified findNearestNeighbor algorithim
   
   May 5 - write graph projection onto map and verify with tests
   
   May 7 - finish report
   
   May 9 - sync to record final presentation
   
   May 11 - finish editing presentation and submit