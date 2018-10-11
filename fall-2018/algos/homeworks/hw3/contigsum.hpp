#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

#include <iterator>
#include <algorithm>
#include <iostream>

struct RunningValues {
    const int gcs = 0;
    const int gcsWLeft = 0;
    const int gcsWRight = 0;
    const int sum = 0;

    RunningValues() = default;
    RunningValues(int gcs, int left, int right, int sum) :
        gcs(gcs), gcsWLeft(left), gcsWRight(right), sum(sum) {}

    RunningValues operator+(const RunningValues & r) const {
        return RunningValues(
            std::max({gcs, r.gcs, gcsWRight + r.gcsWLeft}),
            std::max(gcsWLeft, sum + r.gcsWLeft),
            std::max(r.gcsWRight, r.sum + gcsWRight),
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
