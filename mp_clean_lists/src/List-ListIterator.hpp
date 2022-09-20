
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in MP2.1
    ListNode* position_;
    ListNode* tail_;

  public:
    ListIterator() : position_(NULL) { tail_ = NULL;}
    ListIterator(ListNode* x, ListNode* prev) : position_(x), tail_(prev) {}
    ListIterator(ListNode* x) : position_(x){
        ListNode* currNode = x;
        tail_ = NULL;
        while (currNode != NULL && currNode -> next != NULL) {
            currNode = currNode -> next;
        }
        tail_ = currNode;
    }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP2.1
        position_ = position_ -> next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in MP2.1
        ListNode* temp = position_;
        position_ = position_->next;
        return ListIterator(temp);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP2.1
        if (position_ == NULL) {
            position_ = tail_;
        }
        else {
            position_ = position_ -> prev;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP2.1
        ListNode* temp = position_;
        if (position_ == NULL) {
            position_ = tail_;
        }
        else {
            position_ = position_->prev;
        }
        return ListIterator(temp);
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in MP2.1
        ListNode* a = position_;
        ListNode* b = rhs.position_;
        return (a != b);
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
