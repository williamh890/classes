
#ifndef DA6_H
#define DA6_H

#include "llnode2.h"
// For LLNode2
#include <memory>
// For std::shared_ptr
// For std::make_shared
#include <utility>
// For std::pair
// For std::swap
#include <iostream>
// For testing

template<typename ValType>
void reverseList(std::shared_ptr<LLNode2<ValType> > & head) {

    if (isEmpty(head))  {
        return;
    }

    // Reverse the list
    std::shared_ptr<LLNode2<ValType> > reversed = nullptr;
    std::shared_ptr<LLNode2<ValType> > pivot = nullptr;

    while(head != nullptr) {
        pivot = head;
        head = head->_next;
        pivot->_next = reversed;
        reversed = pivot;
    }

    head = reversed;
}

template<typename KeyType, typename ValType>
class LLMap {
public:
    // Class types
    using KVType = std::pair<KeyType, ValType>;
    using NodeType = LLNode2<KVType>;
    using NodePtrType = std::shared_ptr<NodeType>;

    using size_type = std::size_t;

private:
    std::shared_ptr<LLNode2<KVType> > head;

public:
    // Ctor
    LLMap() {};

    // Deleted Functions
    LLMap(const LLMap & other) = delete;
    LLMap(const LLMap && other) = delete;

    size_type size() const {
        NodePtrType curr = head;
        size_t n = 0;

        while (curr) {
            curr = curr->_next;
            ++n;
        }

        return n;
    }

    bool empty() const {
        return !head;
    }


    const ValType * find(KeyType key) const {
        NodePtrType  curr = head;

        while (curr) {
            if (curr->_data.first == key) {
                return &(curr->_data.second);
            }

            curr = curr->_next;
        }

        return nullptr;
    }

    ValType * find(KeyType key) {
        NodePtrType curr = head;

        while (curr) {
            if (curr->_data.first == key) {
                return &curr->_data.second;
            }

            curr = curr->_next;
        }

        return nullptr;
    }

    void insert(KeyType key, ValType val) {
        if (empty()) {
            head = std::make_shared<NodeType>(std::make_pair(key, val));
            return;
        }

        NodePtrType curr = head;

        while (curr->_next) {
            if (curr->_data.first == key) {
                curr->_data.second = val;
                return;
            }

            curr = curr->_next;
        }

        curr->_next = std::make_shared<NodeType>(std::make_pair(key, val));
    }

    void erase(KeyType key) {
        if (empty()) {
            return;
        }

        NodePtrType curr = head;
        NodePtrType prev = nullptr;

        while (curr && curr->_data.first != key) {
            prev = curr;
            curr = curr->_next;
        }

        // If first Node
        if (!prev && curr->_data.first == key) {
            head = head->_next;
        }
        else {
            prev->_next = curr->_next;;
        }
    }

    template <typename FuncType>
    void traverse(FuncType func) {
        NodePtrType curr = head;

        while (curr) {
            func(curr->_data.first, curr->_data.second);
            curr = curr->_next;
        }
    }

};




#endif
