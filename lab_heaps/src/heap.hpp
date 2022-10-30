
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const //note we are 0-indexing, correct
{
    // @TODO Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const //correct
{
    // @TODO Update to return the index of the left child.
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const //correct
{
    // @TODO Update to return the index of the right child.
    return currentIdx * 2 + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const //correct
{
    // @TODO Update to return the index of the parent.
    return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const //correct
{
    // @TODO Update to return whether the given node has a child
    return hasALeftChild(currentIdx);
}

template <class T, class Compare>
bool heap<T, Compare>::hasALeftChild(size_t currentIdx) const //correct
{
    // @TODO Update to return whether the given node has a child
    if (leftChild(currentIdx) < _elems.size()) return true;
    return false;
}

template <class T, class Compare>
bool heap<T, Compare>::hasARightChild(size_t currentIdx) const //correct
{
    // @TODO Update to return whether the given node has a child
    if (rightChild(currentIdx) < _elems.size()) return true;
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const //assume has children
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t left_child_idx = leftChild(currentIdx);
    if (!hasARightChild(currentIdx)) {
        return left_child_idx;
    }
    size_t right_child_idx = rightChild(currentIdx);
    if (higherPriority(_elems[left_child_idx], _elems[right_child_idx])) {
        return left_child_idx;
    }
    return right_child_idx;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (hasAChild(currentIdx)) {
        size_t smallerChildIndex = maxPriorityChild(currentIdx);
        if (higherPriority(_elems[smallerChildIndex], _elems[currentIdx])) {
            std::swap(_elems[currentIdx], _elems[smallerChildIndex]);
            heapifyDown(smallerChildIndex);
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
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    for (size_t i = 0; i < elems.size(); i++) {
        _elems.push_back(elems[i]);
    }
    //std::cout << _elems.size() << std::endl;
    //std::cout << parent(_elems.size() - 1) << std::endl;
    size_t maxIndex = parent(_elems.size() - 1);
    if (maxIndex == 0) {
        heapifyDown(0);
    } else {
        for (int k = maxIndex; k >= 0; k--) {
            heapifyDown(k);
            //std::cout << "k = " << k << ", maxIndex = " << maxIndex << std::endl;
        }
    }
    
    
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (empty()) {
        return T();
    }
    std::swap(_elems[root()], _elems[_elems.size() - 1]);
    T elem = _elems[_elems.size() - 1];
    _elems.pop_back();
    heapifyDown(root());
    return elem;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (empty()) {
        return T();
    }
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    
    if (higherPriority(_elems[idx], elem)) {
        _elems[idx] = elem;
        heapifyDown(idx);
    } else {
        _elems[idx] = elem;
        heapifyUp(idx);
    }
    
    

}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if (_elems.size() == 0) return true;
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
