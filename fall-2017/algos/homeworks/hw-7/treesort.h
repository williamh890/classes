// treesort.h
// William Horn
// 15 Nov 2017
//
// For CS 311 Fall 2017
// Header for function template treesort
// There is no associated source file.

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <iostream>

#include <cstddef>
// For size_t
#include <type_traits>
// For std::remove_reference
#include <algorithm>
// For std::swap
#include <iterator>
// For std::distance
#include <memory>
// For std::shared_ptr
// For std::make_shared

// Keep helpers local to file
namespace {
    // Node
    // helper struct for treesort function
    template<typename ValType>
    struct Node {
        ValType _data;
        std::shared_ptr<Node> _lChild;
        std::shared_ptr<Node> _rChild;
    };


    // insert
    // Inserts value into sub-tree pointed to by curr
    // post: curr will have toInserted added to it.
    template <typename ValType>
    std::shared_ptr<Node<ValType>>
    insert(ValType toInsert, std::shared_ptr<Node<ValType>> & curr) {
        // base case
        if (!curr) {
            curr = std::make_shared<Node<ValType>>();
            curr->_data = toInsert;
            return curr;
        }

        if (toInsert < curr->_data) {
            curr->_lChild = insert(toInsert, curr->_lChild);
        } else {
            curr->_rChild = insert(toInsert, curr->_rChild);
        }

        return curr;
    }


    // traverse
    // pre: number of nodes in the tree == iter range
    // post: it will point to a sorted range length == number of nodes in tree
    template <typename ValType, typename FDIter>
    void traverse(std::shared_ptr<Node<ValType>> curr, FDIter & it) {
        if (curr->_lChild) {
            traverse(curr->_lChild, it);
        }

        *it = curr->_data;
        ++it;

        if (curr->_rChild) {
            traverse(curr->_rChild, it);
        }
    }
}


// treesort
// Sort a given range using Treesort.
// Pre:
//     FDIters point to a valid range
// Requirements on Types:
//     iter value type must have a < operator, copy ctor and assignment op
// Exception safety guarantee:
//     Exception Neutral
template<typename FDIter>
void treesort(FDIter first, FDIter last) {
    size_t size = std::distance(first, last);

    if (size < 2) {
        return;
    }

    using ValType = typename std::remove_reference<decltype(*first)>::type;
    using NodeType = Node<ValType>;

    std::shared_ptr<NodeType> root = nullptr;

    for (auto it = first; it != last; ++it) {
       insert(*it, root);
    }

    traverse(root, first);
}

#endif //#ifndef FILE_TREESORT_H_INCLUDED

