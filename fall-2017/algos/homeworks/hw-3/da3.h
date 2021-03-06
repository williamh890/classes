// da3.h
// William Horn
// 24 Sep 2017
//
// For CS 311 Fall 2017
// Header for Assignment 3 Functions

#ifndef FILE_DA3_H_INCLUDED
#define FILE_DA3_H_INCLUDED
#include <cstddef>
using std::size_t;
#include <functional>
using std::function;
#include <iterator>
#include <set>


// **************************************************************** // *
// Begin DO-NOT-CHANGE section                                      // *
// Do not alter the lines below                                     // *
// **************************************************************** // *
                                                                    // *
                                                                    // *
// struct LLNode                                                    // *
// Linked List node, with client-specified value type               // *
// Intended Invariants (breakable, as data members are public):     // *
//     Either _next is nullptr, or _next points to an LLNode,       // *
//      allocated with new, owned by *this.                         // *
// Requirements on Types:                                           // *
//     ValueType must have a copy ctor and a dctor.                 // *
template <typename ValueType>                                       // *
struct LLNode {                                                     // *
    ValueType _data;  // Data for this node                         // *
    LLNode *  _next;   // Ptr to next node, or nullptr if none      // *
                                                                    // *
    // The following simplify creation & destruction                // *
                                                                    // *
    // 1- & 2-param ctor                                            // *
    // Pre:                                                         // *
    //     theNext, if passed, is either nullptr, or else it        // *
    //      points to an LLNode, allocated with new, with           // *
    //      ownership transferred to *this.                         // *
    // Post:                                                        // *
    //     _data == data.                                           // *
    //     If _next passed, then _next == next. Otherwise, _next    // *
    //      is nullptr.                                             // *
    explicit LLNode(const ValueType & data,                         // *
                    LLNode * next = nullptr)                        // *
        :_data(data),                                               // *
         _next(next)                                                // *
    {}                                                              // *
                                                                    // *
    // dctor                                                        // *
    // Pre: None.                                                   // *
    // Post: None. (_next delete'd)                                 // *
    ~LLNode()                                                       // *
    { delete _next; }                                               // *
};  // End struct LLNode                                            // *
                                                                    // *
                                                                    // *
// **************************************************************** // *
// End DO-NOT-CHANGE section                                        // *
// Do not alter the lines above                                     // *
// **************************************************************** // *

// (see def'n for docs)
template <typename ValueType>
ValueType lookUp(const LLNode<ValueType> * head,
                 size_t index) {

    size_t i = 0;

    while(head != nullptr && i < index) {
        head = head->_next;
        i++;
    }

    if (head == nullptr)
        throw std::out_of_range("out of range index given to linked list lookup");

    return head->_data;
}


// callBetween
// call a middle function with the garentee that finish will always run
// pre: finish will not throw
// post: if middle executes, finish will as well regardless if middle throws
void callBetween(const function<void()> & start,
                 const function<void()> & middle,
                 const function<void()> & finish);


// (see def'n for docs)
template <typename RAIter>
size_t uniqueCount(RAIter first,
                   RAIter last) {
    using valueType = typename std::iterator_traits<RAIter>::value_type;

    return std::set<valueType>(first, last).size();
}


// gcd
// claculate the gcd of 2 integers
// pre: none
// post: the gcd will be returned
int gcd(int a,
        int b);


#endif  //#ifndef FILE_DA3_H_INCLUDED

