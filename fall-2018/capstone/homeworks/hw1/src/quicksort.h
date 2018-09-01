#include <vector> // std::vector
#include <algorithm> // std::swap
#include <cstddef> // size_t
#include <iostream>

using IndexType = int;


template<class T>
IndexType partition(std::vector<T> & A, IndexType lo, IndexType hi) {
    auto pivot = A[hi];
    auto i = lo;

    for (auto j = lo; j < hi; ++j) {
        if (A[j] < pivot) {
            std::swap(A[i], A[j]);
            ++i;
        }
    }

    std::swap(A[i], A[hi]);

    return i;
}


template<class T>
void quicksort(std::vector<T> & A, IndexType lo, IndexType hi) {
    if (lo < hi) {
        auto p = partition(A, lo, hi);
        quicksort(A, lo, p - 1);
        quicksort(A, p + 1, hi);
    }
}
