// treesort.h  INCOMPLETE
// Glenn G. Chappell
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


template <typename ValType>
class TreeNode {
    private:
        using value_type = ValType;
        using NodePtrType = std::shared_ptr<TreeNode>;

    public:
        // ctor
        TreeNode(value_type data): data_(data) {}

        // op<
        bool operator<(const TreeNode & other) {
            return data_ < other.data_;
        }

        // make
        // pre: FDIter value type == value_type
        template<typename FDIter>
        void make(FDIter first, FDIter last) {
            for(auto curr = first; curr != last; ++curr)  {
                insert(*curr);
            }
        }

        void insert(value_type toInsert) {

            if (toInsert < data_) {
                std::cout << " Inserting left: " << toInsert << std::endl;
                if (!lChild_) {
                    lChild_ = std::make_shared<TreeNode>(toInsert);
                    return;
                }

                insert(lChild_, toInsert);
            }

            else {
                if (!rChild_) {
                    std::cout << " Inserting right: " << toInsert << std::endl;
                    rChild_ = std::make_shared<TreeNode>(toInsert);
                    return;
                }

                insert(rChild_, toInsert);
            }
        }

        void traverse() {
            std::cout << "l: " << lChild_->data_ << ", r: " << rChild_->data_ << std::endl;
        }
    private:

        void insert(NodePtrType & curr, value_type & toInsert) {

            if (toInsert < curr->data_) {
                // Inserting in left node
                std::cout << " Inserting left: " << toInsert << std::endl;
                if (!curr->lChild_) {
                    curr->lChild_ = std::make_shared<TreeNode>(toInsert);
                    return;
                }

                insert(curr->lChild_, toInsert);
            }
            else {
                std::cout << " Inserting right: " << toInsert << std::endl;
                // Inserting in right child
                if (!curr->rChild_) {
                    curr->rChild_ = std::make_shared<TreeNode>(toInsert);
                    return;
                }

                // right child exists
                insert(curr->rChild_, toInsert);
            }
        }

    private:
        NodePtrType lChild_;
        NodePtrType rChild_;
        value_type data_;
};

template <typename ValType>
void insert(TreeNode<ValType> & root) {

}

template <typename ValType>
void traverse(TreeNode<ValType> & root) {

}

// treesort
// Sort a given range using Treesort.
// Pre:
//     ???
// Requirements on Types:
//     ???
// Exception safety guarantee:
//     ???
template<typename FDIter>
void treesort(FDIter first, FDIter last) {
    size_t size = std::distance(first, last);

    if (size < 2) {
        return;
    }

    using ValType = typename std::remove_reference<decltype(*first)>::type;

    TreeNode<ValType> root(*first);

    root.make(++first , last);
}


#endif //#ifndef FILE_TREESORT_H_INCLUDED

