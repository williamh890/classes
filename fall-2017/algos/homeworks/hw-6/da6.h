// da6.h
// William Horn
// Nov 8, 2017
// Code for cs311 assigment 6

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

// reverseList
// Reverse a linked list in place
// Post:
//  head's nodes will be reversed
// No-throw Guarantee
// Exception Neutral
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

// LLMap
// Key value structure using with a linked list
template<typename KeyType, typename ValType>
class LLMap {
public:
    // Class types
    using KVType = std::pair<KeyType, ValType>;
    using NodeType = LLNode2<KVType>;
    using NodePtrType = std::shared_ptr<NodeType>;

    using size_type = std::size_t;

private:
    NodePtrType head; // Head of the LL

public:
    // Ctor
    // Post: Head is nullptr of NodePtrType
    // No-Throw Guarantee
    // Exception Neutral
    LLMap() noexcept {};

    // Deleted Functions
    LLMap(const LLMap & other) = delete;
    LLMap(const LLMap && other) = delete;
    LLMap& operator=(const LLMap & other) = delete;
    LLMap& operator=(const LLMap && other) = delete;

    // size
    // No-Throw Guarantee
    // Exception Neutral
    size_type size() const noexcept {
        NodePtrType curr = head;
        size_t n = 0;

        while (curr) {
            curr = curr->_next;
            ++n;
        }

        return n;
    }

    // empty
    // Checks if the map is empty
    // No-Throw Guarantee
    // Exception Neutral
    bool empty() const noexcept {
        return !head;
    }


    // find (const)
    // Find a value in the map
    // Post:
    //      pointer to data if found,
    //      else nullptr if not
    // No-Throw Guarantee
    // Exception Neutral
    const ValType * find(KeyType key) const noexcept {
        NodePtrType  curr = head;

        while (curr) {
            if (curr->_data.first == key) {
                return &(curr->_data.second);
            }

            curr = curr->_next;
        }

        return nullptr;
    }

    // find (non const)
    ValType * find(KeyType key) noexcept {
        NodePtrType curr = head;

        while (curr) {
            if (curr->_data.first == key) {
                return &(curr->_data.second);
            }

            curr = curr->_next;
        }

        return nullptr;
    }

    // insert
    // post:
    //   if key exists data will be replaced
    //   else no data will be erased
    // Strong Guarantee
    // Exception Neutral
    void insert(KeyType key, ValType val) {
        // Make first node if empty
        if (empty()) {
            head = std::make_shared<NodeType>(std::make_pair(key, val));
            return;
        }

        NodePtrType curr = head;

        while (curr->_next) {
            // Replace if key exists
            if (curr->_data.first == key) {
                curr->_data.second = val;
                return;
            }

            curr = curr->_next;
        }

        // Make a new node at the end
        curr->_next = std::make_shared<NodeType>(std::make_pair(key, val));
    }

    // erase
    // erase key if it exists
    // No-Throw Guarantee
    // Exception Neutral
    void erase(KeyType key) noexcept {
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

    // traverse
    // call a function on every key/val pair in list
    // Strong Guarantee
    // Exception Neutral
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
