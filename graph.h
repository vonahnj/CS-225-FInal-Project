#pragma once

#include <string>
#include <list>
#include <queue>

#include "encounter.h"
#include "kdtree/kdtree.h"

namespace encounters {
    class Graph {        
        public: 

        /**
         */
        class traversal {
            public: 
            /**
             */
            class iterator : public std::iterator<std::forward_iterator_tag, encounter> {
                public: 
                /**
                 */
                iterator() {}; 

                /**
                 */
                iterator(const iterator &other) : order(other.order) {}
                 
                /**
                 */
                iterator(const std::queue<encounter*> &desiredOrder) : order(desiredOrder) {}
 
                /**
                 */
                const iterator& operator=(const iterator& rhs);

                /**
                 */
                const iterator& operator++(); 

                /**
                 */
                const encounter* operator*();
                 
                /**
                 */
                const encounter& operator->();
                 
                /**
                 */
                virtual bool operator==(const iterator& rhs) const;
                 
                /**
                 */
                virtual bool operator!=(const iterator& rhs) const;
                
                private: 
                std::queue<encounter*> order;
            };
            /**
             */
            Graph::traversal::iterator begin();
            
            /**
             */
            Graph::traversal::iterator end();

            protected: 
            std::queue<encounter*> master_;
        };

        class BFS : public traversal {
            public: 
            /**
             */
            BFS(const Graph &g, const std::pair<double, double> &start);
        };

        class DFS : public traversal {
            public: 
            /**
             */
            DFS(const Graph &g, const std::pair<double, double> &start);
        };

        /**
         * Constructs an empy Graph
         */
        Graph();

        /**
         * Constructs a Graph with data from a csv file
         * @param file_name the path to the csv file holding the graph data
         */
        Graph(const std::string &file_name);

        /**
         * Deallocates the memory to prevent memory leaks
         */
        ~Graph();

        /**
         */
        int findNearestNeighbor(const std::pair<double, double> &location) const;

        /**
         */
        const encounter* getNode(int id) const;

        /**
         */
        std::list<const encounter*> getShortestPathDijk(const std::pair<double, double> &start, const std::pair<double, double> &end);

        /**
         */
        vector<double> getBetweennessValues();     
        int getNodeCount();   
        private:
        KDTree locations_;
        vector<encounter*> nodes_;

        /**
         */
        vector<int> getSpanningTreeDijk(int start);

        /**
         */
        std::list<const encounter*> getShortestPathDijk(int startIndex, int endIndex);
    };
} // namespace encounters