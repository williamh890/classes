#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

#include <iterator>
#include <algorithm>
#include <iostream>

struct Values {
    int gcs = 0;
    int gcsWLeft = 0;
    int gcsWRight = 0;
    int sum = 0;

    Values() = default;
    Values(int gcs, int left, int right, int sum) :
        gcs(gcs), gcsWLeft(left), gcsWRight(right), sum(sum) {}

    Values operator+(const Values & r) {
        return Values(
            std::max({gcs, r.gcs, gcsWRight + r.gcsWLeft}),
            std::max(gcsWLeft, sum + r.gcsWLeft),
            std::max(r.gcsWRight, r.sum + gcsWRight),
            sum + r.sum
        );
    }
};

template<typename RAIter>
Values baseCase(RAIter first, int len) {
    if (len == 0)
        return Values();

    const auto gcs = std::max(*first, 0);
    return Values(gcs, gcs, gcs, *first);
}


template<typename RAIter>
Values contigSumVals(RAIter first, RAIter last) {
    const auto len = std::distance(first, last);

    if (len < 2)
        return baseCase(first, len);

    auto middle = first;
    std::advance(middle, len/2);

    return contigSumVals(first, middle) + contigSumVals(middle, last);
}


template<typename RAIter>
int contigSum(RAIter first, RAIter last) {
    return contigSumVals(first, last).gcs;
}

#endif
