#pragma once

#include <string>
#include <list>
#include <queue>

#include "encounter.h"
#include "kdtree/kdtree.h"

namespace encounters {
    /**
     * Graph object to represent the map of encounters.
     * Vertices will be the encounters, edges will link two encounters that
     * are close within some set distance threshold.
     */
    class Graph {
        public:

        /**
         * Traversal object, to allow for BFS/DFS traversal of the map of encounters.
         * The traversal will "hop" between encounters that are close to each other,
         * but BFS does the close ones first before "fanning" out, and DFS goes as
         * deep/far as possible.
         */
        class traversal {
            public:
            /**
             * Iterator object to "iterate" through a bfs/dfs traversal.
             */
            class iterator : public std::iterator<std::forward_iterator_tag, encounter> {
                public:
                /**
                 * Default/empty iterator, without initializations.
                 */
                iterator() {};

                /**
                 * Copy constructor of iterator
                 * @param iterator to copy from
                 */
                iterator(const iterator &other) : order(other.order) {}

                /**
                 * Initialize iterator from a queue of encounters, taken
                 * from either a BFS or a DFS traversal. The top of the queue
                 * is the first visited node, and the bottom is the last visited node.
                 * @param order (queue) to copy from
                 */
                iterator(const std::queue<encounter*> &desiredOrder) : order(desiredOrder) {}

                /**
                 * Copy assignment operator for iterator.
                 * @param iterator to copy from
                 * @return iterator to be copied to.
                 */
                const iterator& operator=(const iterator& rhs);

                /**
                 * Iterator increment operator, to
                 * access the next node in traversal.
                 * @return iterator after incrementation
                 */
                const iterator& operator++();

                /**
                 * Iterator dereference operator, which will return a
                 * pointer to an encounter from the current node.
                 * @return pointer to an encounter from the current node.
                 */
                const encounter* operator*();

                /**
                 * Returns a reference to the current node of traversal.
                 * @return reference to current node
                 */
                const encounter& operator->();

                /**
                 * Equality operator for virtual iterators.
                 * @param rhs - other iterator to compare to
                 * @return bool - if the iterators are equivalent
                 */
                virtual bool operator==(const iterator& rhs) const;

                /**
                 * Inequality operator for virtual iterators.
                 * @param rhs - other iterator to compare to
                 * @return bool - if the iterators are NOT equivalent
                 */
                virtual bool operator!=(const iterator& rhs) const;

                private:
                std::queue<encounter*> order;
            };
            /**
             * Returns the iterator to the start of the graph traversal.
             * @return the start of the graph traversal
             */
            Graph::traversal::iterator begin();

            /**
             * Returns the iterator to the end of the graph traversal.
             * @return the end of the graph traversal
             */
            Graph::traversal::iterator end();

            protected:
            std::queue<encounter*> master_;
        };

        class BFS : public traversal {
            public:
            /**
             * Create a new BFS traversal, given a starting point and a
             * graph (map of encounters)
             */
            BFS(const Graph &g, const std::pair<double, double> &start);
        };

        class DFS : public traversal {
            public:
            /**
             * Create a new DFS traversal, given a starting point and a
             * graph (map of encounters)
             */
            DFS(const Graph &g, const std::pair<double, double> &start);
        };

        /**
         * Constructs an empty Graph
         */
        Graph();

        /**
         * Constructs a Graph with encounter data from a csv file
         * Only adds the nodes, WITHOUT the edges as determined by distance.
         * @param file_name the path to the csv file holding the graph data
         */
        Graph(const std::string &file_name);

        /**
         * Deallocates the memory to prevent memory leaks
         */
        ~Graph();

        /**
         * Find the nearest point to a given location (in coordinates)
         * @param location a pair of (lat, lon)
         * @return index of the nearest neighbor to the given location.
         */
        int findNearestNeighbor(const std::pair<double, double> &location) const;

        /**
         * Get the node that corresponds to an index.
         * @param id - the index
         * @return encounter pointer at the requested index, or
         * NULL if the id is invalid
         */
        const encounter* getNode(int id) const;

        /**
         * Get the shortest path (Dijkstra's) from two COORDINATES start ==> end.
         * @param start - starting coordinate  of the Dijkstra traversal
         * @param end - ending coordinate of the traversal
         * @return list of encounters that represents the shortest path between
         * the start to the end. We use the nearest neighbor algorithm to figure
         * out the actual recorded points closest to the COORDINATES provided
         * by the user.
         */
        std::list<const encounter*> getShortestPathDijk(const std::pair<double, double> &start, const std::pair<double, double> &end);

        /**
         * Get the betwenness centrality index for each vertex, which tells us
         * for each vertex, how much shortest paths pass through that point
         * @return vector of doubles, each representing the normalized
         * betweenness index
         */
        vector<double> getBetweennessValues();

        /**
         * Get the number of nodes in our graph
         * @return int, # of nodes in graph
         */
        int getNodeCount();

        private:
        KDTree locations_;
        vector<encounter*> nodes_;

        /**
         * Get the spanning tree for a starting point.
         * @param start - the starting point of our dijkstra traversal
         * @return list that tells the index of the parent node of each vertex.
         * This info can help one piece together the shortest-path spanning tree.
         * In particular, vertices outside the start's
         * connected component are labeled w/ -2, and
         * the start vertex is labeled -1.
         */
        vector<int> getSpanningTreeDijk(int start);

        /**
         * Get the shortest path (Dijkstra's) from two points (INDICIES) start ==> end.
         * @param start - starting index of the Dijkstra traversal
         * @param end - ending index of the traversal
         * @return list of encounters that represents the shortest path between
         * the point represented by start index to the end index
         */
        std::list<const encounter*> getShortestPathDijk(int startIndex, int endIndex);
    };
} // namespace encounters
