
#ifndef DA6_H
#define DA6_H

#include "llnode2.h"
// For LLNode2
#include <memory>
// For std::shared_ptr
#include <utility>
// For std::pair


template<typename ValType>
void reverseList(std::shared_ptr<LLNode2<ValType> > & head) {

}

template<typename KeyType, typename ValType>
class LLMap {
    public:

        // ************* Class Types ****************

        using KVType = std::pair<KeyType, ValType>;
        using NodeType = std::shared_ptr<LLNode2<KVType>>;

        using size_type = std::size_t;

        // **************** Ctor ********************
        // Ctor
        LLMap(): head(NodeType()){};

        LLMap(const LLMap & other) = delete;
        LLMap(const LLMap && other) = delete;

        // *********** Member Functions *************
        size_type size() const {
            return 0; // DUMMY
        }

        bool empty() const {
            return true; // DUMMY
        }

        ValType * find(KeyType key) const {
            return nullptr;
        }

        void insert(KeyType key, ValType val) {

        }

        void erase(KeyType key) {

        }

        template <typename FuncType>
        void traverse(FuncType func) {

        }


    private:
        std::shared_ptr<LLNode2<KVType> > head;
};




#endif
