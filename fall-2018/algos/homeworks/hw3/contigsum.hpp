// contigsum.hpp
// William Horn
// 08-11-2018
// Algorithms HW3


#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

#include <iterator>
#include <algorithm>
#include <iostream>

struct RunningValues {
    const int gcs = 0;
    const int gcsWithLeft = 0;
    const int gcsWithRight = 0;
    const int sum = 0;

    RunningValues() = default;

    RunningValues(int gcs, int left, int right, int sum) :
        gcs(gcs), gcsWithLeft(left), gcsWithRight(right), sum(sum) {}

    RunningValues operator+(const RunningValues & r) const {
        return RunningValues(
            std::max({gcs, r.gcs, gcsWithRight + r.gcsWithLeft}),
            std::max(gcsWithLeft, sum + r.gcsWithLeft),
            std::max(r.gcsWithRight, r.sum + gcsWithRight),
            sum + r.sum
        );
    }
};


template<typename RAIter>
RunningValues baseCase(const RAIter first, const int len) {
    if (len == 0)
        return RunningValues();

    const auto gcs = std::max(*first, 0);
    return RunningValues(gcs, gcs, gcs, *first);
}


template<typename RAIter>
RunningValues quickContigSum(const RAIter first, const RAIter last) {
    const auto len = std::distance(first, last);

    if (len < 2)
        return baseCase(first, len);

    const auto middle = first + len/2;

    return quickContigSum(first, middle) + quickContigSum(middle, last);
}


template<typename RAIter>
int contigSum(RAIter first, RAIter last) {
    return quickContigSum(first, last).gcs;
}

#endif
