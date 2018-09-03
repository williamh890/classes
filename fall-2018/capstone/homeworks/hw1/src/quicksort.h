#include <vector> // std::vector
#include <algorithm> // std::swap

using IndexType = int;


template<class T>
IndexType partition(std::vector<T> & A, IndexType lo, IndexType hi) {
    auto pivot = A[lo];
    auto i = lo - 1;
    auto j = hi + 1;

    while (true) {
        do { ++i; } while(A[i] < pivot);
        do { --j; } while(A[j] > pivot);

        if (i >= j) {
            return j;
        }

        std::swap(A[i], A[j]);
    }
}


template<class T>
void quicksort(std::vector<T> & A, IndexType lo, IndexType hi) {
    if (lo < hi) {
        auto p = partition(A, lo, hi);
        quicksort(A, lo, p);
        quicksort(A, p + 1, hi);
    }
}
