#pragma once 

#include "encounter.h"
#include <vector>

namespace encounters {
    using std::vector;

    class KDTree {
        struct KDTreeNode {
            encounter* value_;
            KDTreeNode *left_;
            KDTreeNode *right_;

            KDTreeNode() : value_(NULL), left_(NULL), right_(NULL) {};
            KDTreeNode(encounter *value) : value_(value), left_(NULL), right_(NULL) {};
        };

        public: 
        KDTree();
        KDTree(vector<encounter*> &encounters);
        ~KDTree();
        bool smallerDimVal(const encounter* first, const encounter* second, int curDim) const;
        encounter* findNearestNeighbor(const encounter* query) const;
        vector<encounter*> getTraversalById() const;
        void getTraversalById(KDTreeNode *subroot, vector<encounter*> &traversal) const; 

        private: 
        KDTreeNode *root_;
        int size_;

        void addSection(KDTreeNode *&subroot, vector<encounter*> & newPoints, int start, int end, int level);
        vector<encounter*> sort(vector<encounter*> &source, int level);
        bool shouldReplace(const encounter* target, const encounter* currentBest, const encounter* potential) const;
        encounter* findNearestNeighbor(const KDTreeNode* current, const encounter* query, size_t level) const;

        void _destroy(const KDTreeNode *current);
    };

} // namespace encounters