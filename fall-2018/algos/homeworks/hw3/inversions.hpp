// inversions.hpp
// William Horn
// 08-12-2018
// Algos HW3

#ifndef INVERSIONS_HPP
#define INVERSIONS_HPP

#include <vector>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <type_traits>


template <typename RAIter>
size_t stableMerge(const RAIter first, const RAIter middle, const RAIter last) {
    using ValueType = typename std::remove_reference<decltype(*first)>::type;

    std::vector<ValueType> buffer(std::distance(first, last));

    auto out = begin(buffer);
    RAIter in1 = first, in2 = middle;

    size_t totalJumps = 0;

    while (in1 != middle && in2 != last) {
        if (*in2 < *in1) {
            totalJumps += distance(in1, middle);
            *out++ = *in2++;
        } else {
            *out++ = *in1++;
        }
    }

    std::copy(in1, middle, out);
    std::copy(in2, last, out);

    std::copy(begin(buffer), end(buffer), first);

    return totalJumps;
}


template <typename RAIter>
size_t mergeSort(const RAIter first, const RAIter last) {
    const size_t size = std::distance(first, last);

    if (size <= 1)
        return 0;

    const auto middle = first + size/2;

    return
        mergeSort(first, middle) +
        mergeSort(middle, last) +
        stableMerge(first, middle, last);
}


template<typename RAIter>
size_t inversions(RAIter first, RAIter last) {
    return mergeSort(first, last);
};

#endif // INVERSIONS_HPP
