/**
 * @file list.cpp
 * Doubly Linked List (MP 2).
 */
#include <iostream>
template <class T>
List<T>::List() { 
  // @TODO: graded in MP2.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP2.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP2.1
  //std::cout << tail_ -> data << std::endl;
  return List<T>::ListIterator(tail_->next, tail_);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP2.1
  ListNode* currNode = head_;
  ListNode* next = NULL;
  while (currNode != NULL) {
    next = currNode->next;
    delete currNode;
    currNode = next;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP2.1
  ListNode * newNode = new ListNode(ndata);

  if (tail_ == NULL) {
    head_ = tail_ = newNode;
    newNode -> next = NULL;
    newNode -> prev = NULL;
  } else {
     newNode -> next = head_;
     newNode -> prev = NULL;
     head_ -> prev = newNode;
     head_ = newNode;
  }
  
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP2.1
  ListNode * newNode = new ListNode(ndata);
  if (head_ == NULL) {
    head_ = tail_ = newNode;
    newNode -> next = NULL;
    newNode -> prev = NULL;
  } else {
     newNode -> prev = tail_;
     newNode -> next = NULL;
     tail_ -> next = newNode;
     tail_ = newNode;
  }

  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) { // not working properly
  /// @todo Graded in MP2.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      if(curr->prev != NULL) curr->prev->next = NULL;
      curr->prev = NULL;
  }
  //tail_ = curr -> prev;
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() { 
  // @todo Graded in MP2.1
  ListNode* curr = head_;
  //0 or 1 or 2 elements
  if (curr == NULL || curr -> next == NULL || curr -> next -> next == NULL) return;
  
  int mod = (size() % 3);
  int iterations = size() - mod;
  if (mod == 0) tail_ = tail_ -> prev -> prev;
  //std::cout << "iterations: " << iterations << endl;
  for (int i = 1; i <= iterations; i++) {
     //std::cout << i << std::endl;
     if (i == 1) head_ = curr -> next;
     if (i % 3 == 0) {
       curr = curr -> next;
       continue;
     }
     ListNode* before = curr -> prev;
     ListNode* after = curr -> next;
     curr -> next = after -> next;
     if (after -> next != NULL) after -> next -> prev = curr;
     if (before != NULL) before -> next = after;
     after -> prev = before;
     after -> next = curr;
     curr -> prev = after;
  }

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP2.2
  if (startPoint == endPoint) return;
  ListNode* beforeStartPoint = startPoint -> prev; 
  ListNode* afterEndPoint = endPoint -> next; 
  ListNode* currNode = startPoint; 
  if (startPoint == head_ && endPoint != tail_) {
     int counter = 0;
     while (currNode != afterEndPoint) {
       counter++;
       currNode = currNode -> next;
     }
     T* arr = new T[counter];
     int i = counter;
     while (currNode != startPoint) {
       currNode = currNode -> prev;
       arr[--i] = currNode -> data;
     }
     while (currNode != afterEndPoint) {
       ListNode* next = currNode -> next;
       delete currNode;
       currNode = next;
       head_ = next;
       length_--;
     }
     for (int i = 0; i < counter; i++) {
       insertFront(arr[i]);
     }
     delete[] arr;
     startPoint = head_;
     endPoint = head_;
     for (int i = 0; i < counter - 1; i++) {
        endPoint = endPoint -> next;
     }
     return;
  }
  while (currNode != afterEndPoint) {
    ListNode* next = currNode -> next; 

    if (currNode == startPoint) {
       currNode -> next = afterEndPoint;
    } else {
       currNode -> next = currNode -> prev;
    }
    if (currNode == endPoint) {
       currNode -> prev = beforeStartPoint;
    } else {
       currNode -> prev = next;
    }
    currNode = next;
  }
  if (beforeStartPoint != NULL) beforeStartPoint -> next = endPoint;
  if (afterEndPoint != NULL) afterEndPoint -> prev = startPoint;
  ListNode* temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP2.2
  if (n == 0) return;
  if (n >= length_) {
    reverse(head_, tail_);
    return;
  }
  ListNode* leftPoint = head_;
  ListNode* rightPoint = head_;
  for (int i = 1; (i < n) && (rightPoint != NULL); i++) {
     rightPoint = rightPoint -> next;
  }
  
  while (rightPoint != NULL) {
    
    reverse(leftPoint, rightPoint); 
    
    for (int i = 1; (i <= n) && (rightPoint != NULL); i++) {
      leftPoint = leftPoint -> next;
      rightPoint = rightPoint -> next;
    }
  }
  int rem = length_ % n;
  leftPoint = tail_;
  for (int i = rem - 1; i > 0; i--) {
     leftPoint = leftPoint -> prev;
  }
  reverse(leftPoint, tail_);
  
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) { //seg fault occurs
    // set up the current list
    //std::cout << "Hi1" << std::endl;
    head_ = merge(head_, otherList.head_); //seg fault occurs
    //std::cout << "Hi2" << std::endl;
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP2.2
  if (first == NULL) return second;
  if (second == NULL) return first;
  
  ListNode* startNode;
  startNode = first;
  if (first -> data < second -> data) {
     startNode = first;
     first = first -> next;
  } else {
    startNode = second;
    second = second -> next;
  }
  
  ListNode* currNode = startNode;

  while (first != NULL && second != NULL) {
     if (first -> data < second -> data) {
       currNode -> next = first;
       first = first -> next;
     } else {
       currNode -> next = second;
       second = second -> next;
     }
     currNode = currNode -> next;
  }

  if (first == NULL) currNode -> next = second;
  else currNode -> next = first;
  
  return startNode;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP2.2
  if (start == NULL || chainLength == 1) return start;

  ListNode* middle = split(start, chainLength / 2);

  start = mergesort(start, chainLength / 2);
  middle = mergesort(middle, chainLength - chainLength / 2);

  return merge(start, middle);
  

}
