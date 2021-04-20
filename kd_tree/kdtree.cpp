/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 * Copied from mp_mosaics
 */

#include <utility>
#include <algorithm>
#include <iostream>

#include "kdtree.h"
#include "../encounter.h"

using namespace std;
using namespace encounters;

KDTree::KDTree() {
  root = NULL;
  size = 0;
}

bool KDTree::smallerDimVal(const Point<2>& first,
                                const Point<2>& second, int curDim) const
{
    if (first[curDim] == second[curDim]) {
      return first < second;
    }
    return first[curDim] < second[curDim];
}

bool KDTree::shouldReplace(const Point<2>& target,
                                const Point<2>& currentBest,
                                const Point<2>& potential) const {
    double potDist = squaredDistance(target, potential);
    double curDist = squaredDistance(target, currentBest);
    return potDist < curDist || (potDist == curDist && potential < currentBest);
}

KDTree::KDTree(const vector<encounter*> &newPoints) {
    if (newPoints.size() != 0) {
      addSection(root, newPoints, 0, newPoints.size() - 1, 0);
      size = newPoints.size();
    } else {
      root = NULL;
      size = 0;
    }
}

vector<encounter*> KDTree::sort(const vector<encounter*> &source, int start, int end, int level) {
  if (start == end) {
    return vector<encounter*>({source.at(start)});
  } else if (start > end) {
    return vector<encounter* >();
  }

  int mid = (end + start)/2;
  vector<encounter*> left = sort(source, start, mid, level);
  vector<encounter*> right = sort(source, mid+1, end, level);
  vector<encounter*> sorted;
  sorted.reserve(left.size() + right.size());

  vector<encounter*>::iterator it_left = left.begin();
  Point<2> currLeft = Point<2>((*it_left)->location.first, (*it_left)->location.second);
  vector<encounter*>::iterator it_right = right.begin();
  Point<2> currRight = Point<2>((*it_right)->location.first, (*it_right)->location.second);

  while (it_left != left.end() && it_right != right.end()) {
    if (smallerDimVal(currLeft, currRight, level % 2)) {
      sorted.push_back(*it_left);
      ++it_left;
      currLeft = Point<2>((*it_left)->location.first, (*it_left)->location.second);
    } else {
      sorted.push_back(*it_right);
      currRight = Point<2>((*it_right)->location.first, (*it_right)->location.second);
      ++it_right;
    }
  }

  sorted.insert(sorted.end(), it_left, left.end());
  sorted.insert(sorted.end(), it_right, right.end());

  return sorted;
}

KDTree::KDTree(const KDTree &other) {
  _copy(other);
}

const KDTree& KDTree::operator=(const KDTree& rhs) {
  if (&rhs != this) {
    _destroy();
    _copy(rhs);
  }

  return *this;
}

KDTree::~KDTree() {
  _destroy();
}

int KDTree::findNearestNeighbor(const Point<2>& query) const {
  KDTreeNode* nearest = findNearestNeighbor(root, query, 0);
  if (nearest) {
    return nearest->val;
  }
  
  return -1;
}

KDTree::KDTreeNode* KDTree::findNearestNeighbor(KDTreeNode* current, const Point<2>& query, size_t level) const {
  if (current->left == NULL && current->right == NULL) {
    return current;
  }

  KDTreeNode *primary;
  KDTreeNode *secondary;
  KDTreeNode *nearest = current;
  if (smallerDimVal(query, current->point, level % 2)) {
    primary = current->left;
    secondary = current->right;
  } else {
    primary = current->right;
    secondary = current->left;
  }

  if (primary) {
    KDTreeNode *potential = findNearestNeighbor(primary, query, level + 1);
    if (shouldReplace(query, nearest->point, potential->point)) {
      nearest = potential;
    }
  }

  double radius = squaredDistance(query, nearest->point);
  double splitDist = abs(current->point[level % 2] - query[level % 2]);

  if (radius >= splitDist && secondary) {
    KDTreeNode *potential = findNearestNeighbor(secondary, query, level + 1);
    if (shouldReplace(query, nearest->point, potential->point)) {
      nearest = potential;
    }
  }

  return nearest;
}

void KDTree::addSection(KDTreeNode *&subroot, const vector<encounter*>& newPoints, int start, int end, int level) {

  if (start == end) {
    subroot = new KDTreeNode(newPoints.at(start)->location, newPoints.at(start)->id);
    return;
  } else if (start > end) {
    return;
  }

  vector<encounter*> orderedPoints = sort(newPoints, start, end, level);
  size_t mid = (orderedPoints.size() - 1)/2;
  subroot = new KDTreeNode(orderedPoints.at(mid)->location, orderedPoints.at(mid)->id);
  if (mid != 0 ) {
    addSection(subroot->left, orderedPoints, 0, mid -1, level+1);
  }
  addSection(subroot->right, orderedPoints, mid + 1, orderedPoints.size() - 1, level+1);
  return;
}

void KDTree::_copy(const KDTree &other) {
  vector<encounter*> newPoints;
  size = newPoints.size();
  if (newPoints.size() == 0) {
    root = NULL;
    return;
  }
  _copy(other.root, newPoints);
  addSection(this->root, newPoints, 0, newPoints.size() - 1, 0);
}

void KDTree::_copy(const KDTreeNode *current, vector<encounter*>& newPoints) const {
  if (current == NULL) {
    return;
  }
  
  _copy(current->left, newPoints);
  newPoints.push_back(new encounter(date(), current->point[0], current->point[1], current->val));
  _copy(current->right, newPoints);
}

void KDTree::_destroy() {
  _destroy(root);
  size = 0;
}

void KDTree::_destroy(const KDTreeNode *current) {
  if (current == NULL) {
    return;
  }

  _destroy(current->left);
  _destroy(current->right);
  delete current;
  current = NULL;
}

double KDTree::squaredDistance(const Point<2> &first, const Point<2> &second) const {
  double dist = 0;
  for (int index = 0; index < 2; index++) {
    dist += pow(first[index] - second[index], 2);
  }
  return pow(dist, 0.5);
}