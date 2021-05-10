# CS 225 Data Structures
## Results (ahqiu2-pzy2-jvonahn2-merchia2)

## Final Deliverables
  1. [Traversals](#traversals)
  2. [Spanning Tree](#spanning-tree)
  3. [Shortest Path Algorithm](#shortest-path-algorithm)
  4. [Centrality Algorithm](#centrality-algorithm)

Each section of a deliverable will cover the following topics in order: 
1. Runtime
2. Discoveries
3. Proof of Correctness

### Traversals
1. Runtime

    **Runtime: O(n + m)**

    **Proof for BFS:** 
        ![BFS Runtime Proof](images/BFS.jpg)
    **Proof for DFS:** 
        ![DFS Runtime Proof](images/DFS.jpg)

2. Discoveries

   * We learned how simple it was to count connected components using traversal generating methods. We used them to calibrate our optimal distance threshold to significantly decrease the number of connected components while not linking each node to every other node
   * By putting a counter in our DFS, we were able to determine that the graph isn't very deep and typically has a depth of 10-12 nodes regardless of starting point. This implies that the majority of encounters can be visited within 10-12 nodes of each other. 

3. Proof of Correctness

    A list of edges for a 312 item dataset was constructed and the BFS and DFS Traversal for each of them was calculated. This test is rather extensive and was costly to manually compute, however it was passed by the implementation in [test_traversals.cpp](tests/../../tests/test_traversals.cpp)

### Spanning Tree
1. Runtime
   
    **Runtime: O(m\*logm)**

    **Proof:**
    ![Spanning Tree Runtime Proof](images/SpanningTree.jpg)

2. Discoveries

    We discovered we could not run Dijkstras in the traditional runtime due to the way in which our min heap was implemented. This is because we realized we couldn't update the values in the min heap because this required us to know the index of the edge within the min heap. This was not information we had access to. Finding the edge to update it would require a find function with runtime O(n) which would unneccesarily increase our runtime. Instead we decided to push the edge if Dijstrakas calculations predicted it would lead to a shorter path. When we removed each edge, we checked to ensure that it matched the most recent edge pushed (the best one) by checking that it started at the current predicted parent. This check was in constant time and while it helped us avoid increasing our runtime to O(n), it caused us to increase the number of heap adds and removals. This resulted in a maximum increase in runtime from traditional dijstrakas by changing m\*log(n) to 2\*log(m) which was not the dominant term in our algorithm and could be discarded. However, it increased the number of iterations over the larger loop from n to m, changing the overall runtime from n\*log(m) to m\*log(m). 

3. Proof of Correctness

    We created a [google map](https://www.google.com/maps/d/u/0/edit?mid=1mdRbpRLo7sXlOq7Q9xYIfFJLHTtmq_Dd&usp=sharing) to visualize a smaller data set and ran a series of spanning tree algorithms over them and printed the resulting parent array to ensure it was correct. For all of the 6 resulting trees (one starting at each node), the parent array we calculated was identical to the manually computed parent array. We also ran similar tests on smaller data sets that did not require visualization and determined the spanning tree calculated by the program to be correct

### Shortest Path Algorithm

1. Runtime

    **Runtime: O(n + m\*logm)**

    **Proof:**
    ![Shortest Path Runtime Proof](images/ShortestPath.jpg)

2. Discoveries

    We initially anticipated that if we ran a shortest path algorithm and there were multiple nodes in the same exact location, the shortest path would visit all nodes in that location before continuing onwards. However, after computing a series of shortest paths, we realized this was not the case because if two nodes are in the same location, they will have the same set of edges. This means that when computing the spanning tree, after visiting the first node at that location, the neighboring nodes are already updated to the distances at that location. Therefore any visits to a different node at that location in the future will not result in any updates. Essentially, after visiting the first node at a given location, any other nodes in that location will have no descendants and the same parent. 

3. Proof of Correctness

    We created a [google map](https://www.google.com/maps/d/u/0/edit?mid=1mdRbpRLo7sXlOq7Q9xYIfFJLHTtmq_Dd&usp=sharing) to visualize a smaller data set and created a series of tests to ensure the manually computed shortest distance paths measured in google maps matched the paths found by the algorithm. We also ran similar tests on smaller data sets that did not require visualization and determined the shortest paths calculated by the program to be correct.

### Centrality Algorithm

1. Runtime

    **Runtime: O(n(n + m\*logm))**

    **Explanation:**
    The majority of the work done by this algorithm is calling the spanning tree algorithm on each node in the graph. This gives the algorithm a bare minimum running time of O(n\*m\*logm). The actual traversal of a spanning tree takes between n and n^2 time depending on the whether the graph is more dense or linear. Because of the dense nature of our graph (with the number of edges being greater than 100x the number of nodes), it is safe to assume that this running time will be quite close to O(n) for the spanning tree traversal. This is supported by runtime testing that has been performed on both the full data set and the large test data, in which runtimes agreed within 14% for O(n(n + m\*logm)), but were drastically off for O(n(n^2 + m\*logm)). This leaves us at a running time estimate of O(n(n + m\*logm)). 

2. Discoveries

    The Betweenness Centrality algorithm was more so an application and analysis of our previous algorithms than an independent function. For this reason, it became clear quickly that it was necessary for our Dijkstra's Algorithms to work exactly as specificed in order fo this algortihm to work. This led to us finding and fixing errors in our previous algorithms that may have gone unnoticed otherwise. In terms of the actual results of our data, 4 of 5 most central nodes for Illinois lie along I-55 in a cluster outside of Chicago. This makes sense to be a hotspot for UFO sightings, as I-55 is [the most traveled highway in Illinois](https://www.nbcchicago.com/news/local/study-illinois-interstates-5th-busiest-in-nation/1961351/), and the segment leaving Chicago is likely a heavily-traveled area.

3. Proof of Correctness

    We used our smallest set of testing data and manually calculated the centrality values of each node and confirmed that our algorithm was in agreement. In addition, we manually gave the algorithm specific sets of spanning trees to ensure that the trees were being interpreted as intended. Finally, we visually confirmed on a [google map](https://www.google.com/maps/d/u/0/edit?mid=1mdRbpRLo7sXlOq7Q9xYIfFJLHTtmq_Dd&usp=sharing) that our most central nodes were logically consistent with the layout of the graph.