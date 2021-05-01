#include <iostream>
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // Update to return the index of the child with highest priority as defined by higherPriority()
    if (!hasAChild(currentIdx)) {
        return 0;
    }

    size_t rightIdx = rightChild(currentIdx);
    size_t leftIdx = leftChild(currentIdx);

    if (rightIdx >= _elems.size()) {
        return leftIdx;
    } else if (higherPriority(_elems.at(leftIdx), _elems.at(rightIdx))) {
        return rightIdx;
    }

    return leftIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::minPriorityChild(size_t currentIdx) const
{
    // Update to return the index of the child with highest priority as defined by higherPriority()
    if (!hasAChild(currentIdx)) {
        return 0;
    }

    size_t rightIdx = rightChild(currentIdx);
    size_t leftIdx = leftChild(currentIdx);

    if (rightIdx >= _elems.size()) {
        return leftIdx;
    } else if (higherPriority(_elems.at(leftIdx), _elems.at(rightIdx))) {
        return leftIdx;
    }

    return rightIdx;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // Implement the heapifyDown algorithm.
    if (hasAChild(currentIdx)) {
        size_t minChildIndex = minPriorityChild(currentIdx);
        if (higherPriority(_elems.at(minChildIndex), _elems.at(currentIdx))) {
            std::swap(_elems.at(currentIdx), _elems.at(minChildIndex));
            heapifyDown(minChildIndex);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for (const T &elem : elems) {
        _elems.push_back(elem);
    }

    
    for (size_t index = _elems.size()/2 + root(); index >= root(); --index) {
        heapifyDown(index);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // Remove, and return, the element with highest priority
    if (_elems.size() == root()) {
        return T();
    }

    T front = _elems.at(root());
    _elems.at(root()) = _elems.back();
    _elems.pop_back();
    heapifyDown(root());

    return front;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // Return, but do not remove, the element with highest priority
    if (_elems.size() == root()) {
        return T();
    }
    return _elems.at(root());
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    if (idx < root() || idx >= _elems.size()) {
        return;
    }

    T former = _elems.at(idx);
    _elems.at(idx) = elem;
    if (higherPriority(former, elem)) {
        heapifyDown(idx);
    } else {
        heapifyUp(idx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // Determine if the heap is empty
    return _elems.size() == root();
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
