# CS 225 Data Structures
## Project Proposal (ahqiu2-pzy2-jvonahn2-merchia2)

1. **Leading Question** Given a location or time period, we would like to evaluate nearby UFO encounters or sightings and plot them on a map. 

2. **Dataset Acquistion and Processing** We propose using the [UFO Sightings Kaggle Dataset](https://www.kaggle.com/NUFORC/ufo-sightings). We will focus on the location given by latitude and longitude as well as the timestamps of each encounter in this dataset. This data is provided in a `*.csv` format, and we will cite this reference from [Geeks for Geeks](https://www.geeksforgeeks.org/csv-file-management-using-c/) to load the data into a graph where the nodes represent the locations of the encounters while there are two sets of colored edges. One color of edges represent two encounters occuring within a week of each other while the other connects any nodes that fall within a given radius of the other. We recognize that this data is large, and potentially error-ridden; thus, we will drop any records that don't contain all three of the required fields for our purposes (latitude, longitude, and timestamp) and/or any malformed records.

3. **Graph Algorithms** For our graph traversal, we propose to implement a traversal which starts at the earliest recorded encounter and parses acounters by time stamp from earliest to latest.
   
For one of our algorithm, we propose implementing an algorithm which finds the shortest route between two given nodes with the maximum number of encounters between them.
   
For our other algorithms, we propose implementing a midpoints algorithm which given two encounters, will return the set of encounters which falls between them. For instance, if given two encounters, imagine a rectangle where the two encounters fall on opposite ends of the diagonal. The algorithm will return all encounters falling within the rectangle that also temporally occurred between the two nodes. 

4. **Timeline** 

   April 7 - sync to complete project proposal and team contract
   
   April 9 - submit project proposal and team contract
   
   April 12 - set up initial repository and Makefile
   
   April 15 - finish reading in data to graph and write simple tests to verify correctness
   
   April 19 - write traversal of graph and simple tests to verify correctness
   
   April 22 - write first algorithm and write tests to verify correctness
   
   April 29 - write second algorithm and write tests to verify correctness
   
   May 5 - write graph projection onto map and verify with tests
   
   May 7 - finish report
   
   May 9 - sync to record final presentation
   
   May 11 - finish editing presentation and submit