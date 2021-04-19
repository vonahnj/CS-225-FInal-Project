#include "kdtree.h"

namespace encounters {
    KDTree::KDTree() {
        size_ = 0;
        root_ = NULL;
    }

    KDTree::KDTree(vector<encounter*> &encounters) {
        if (encounters.size() != 0) {
            addSection(root_, encounters, 0, encounters.size() - 1, 0);
            size_ = encounters.size();
        } else {
            root_ = NULL;
            size_ = 0;
        }
    }

    KDTree::~KDTree() {
        _destroy(root_);
        size_ = 0;
    }

    bool KDTree::smallerDimVal(const encounter* first, const encounter* second, int curDim) const {
        if (curDim == 0) {
            if (first->location.first == second->location.first) {
                return first < second;
            }
            return first->location.first < second->location.first;
        } else {
            if (first->location.second == second->location.second) {
                return first < second;
            }
            return first->location.second < second->location.second;
        }
    }

    void KDTree::addSection(KDTreeNode *&subroot, vector<encounter*> & newPoints, int start, int end, int level) {
        if (start == end) {
            subroot = new KDTreeNode(newPoints.at(start));
            return;
        } else if (start > end) {
            return;
        }

        vector<encounter*> orderedPoints = sort(newPoints, level);
        size_t mid = (orderedPoints.size() - 1)/2;
        subroot = new KDTreeNode(orderedPoints.at(mid));
        if (mid != 0 ) {
            addSection(subroot->left_, orderedPoints, 0, mid -1, level+1);
        }
        addSection(subroot->right_, orderedPoints, mid + 1, orderedPoints.size() - 1, level+1);
        return;
    }

    vector<encounter*> KDTree::sort(vector<encounter*> &source, int level) {
        if (source.size() <= 1) {
            return source;
        }

        int mid = source.size()/2;
        vector<encounter*> firstHalf(source.begin(), source.begin() + mid);
        vector<encounter*> secondHalf(source.begin() + mid, source.end());

        vector<encounter*> left = sort(firstHalf, level);
        vector<encounter*> right = sort(secondHalf, level);
        vector<encounter*> sorted;

        vector<encounter*>::iterator it_left = left.begin();
        vector<encounter*>::iterator it_right = right.begin();

        while (it_left != left.end() && it_right != right.end()) {
            if (smallerDimVal(*it_left, *it_right, level % 2)) {
                sorted.push_back(*it_left);
                ++it_left;
            } else {
                sorted.push_back(*it_right);
                ++it_right;
            }
        }

        sorted.insert(sorted.end(), it_left, left.end());
        sorted.insert(sorted.end(), it_right, right.end());

        return sorted;
    }

    encounter* KDTree::findNearestNeighbor(const encounter* query) const {
        return findNearestNeighbor(root_, query, 0);
    }

    encounter* KDTree::findNearestNeighbor(const KDTreeNode* current, const encounter* query, size_t level) const {
        if (current->left_ == NULL && current->right_ == NULL) {
            return current->value_;
        }

        KDTreeNode *primary;
        KDTreeNode *secondary;
        encounter* nearest = current->value_;
        if (smallerDimVal(query, current->value_, level % 2)) {
            primary = current->left_;
            secondary = current->right_;
        } else {
            primary = current->right_;
            secondary = current->left_;
        }

        if (primary) {
            encounter* potential = findNearestNeighbor(primary, query, level + 1);
            if (shouldReplace(query, nearest, potential)) {
            nearest = potential;
            }
        }

        double radius = dist(*query, *nearest);
        double splitDist = abs(current->value_->location.first - query->location.first);
        if (level % 2 == 1) {
            splitDist = abs(current->value_->location.second - query->location.second);
        }

        if (radius >= splitDist && secondary) {
            encounter* potential = findNearestNeighbor(secondary, query, level + 1);
            if (shouldReplace(query, nearest, potential)) {
            nearest = potential;
            }
        }

        return nearest;
    }

    bool KDTree::shouldReplace(const encounter* target, const encounter* currentBest, const encounter* potential) const {
        double potDist = dist(*target, *potential);
        double curDist = dist(*target, *currentBest);
        return potDist < curDist || (potDist == curDist && potential->location < currentBest->location);
    }

    void KDTree::_destroy(const KDTreeNode *current) {
        if (current == NULL) {
            return;
        }

        _destroy(current->left_);
        _destroy(current->right_);
        delete current->value_;
        delete current;
        current = NULL;
    }

    vector<encounter*> KDTree::getTraversalById() const {
        vector<encounter*> traversal(size_, NULL);
        getTraversalById(root_, traversal);
    }

    void KDTree::getTraversalById(KDTreeNode *subroot, vector<encounter*> &traversal) const {
        if (subroot->left_) getTraversalById(subroot->left_, traversal);
        if (subroot->right_) getTraversalById(subroot->right_, traversal);

        if (subroot) {
            traversal.at(subroot->value_->id) = subroot->value_;
        }
    }
} // namespace encounters