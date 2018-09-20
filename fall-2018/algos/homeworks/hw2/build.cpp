// build.cpp
// William Horn
// Sept 20, 2018
// CS 411 HW2

#include "build.hpp"

#include<algorithm>
using std::max;
using std::swap;
#include <vector>
using std::vector;


struct Bridge {
    int w, e, toll;

    Bridge() = default;
    Bridge(const vector<int> & b): w(b[1]), e(b[0]), toll(b[2]) {}
    Bridge& operator=(const Bridge& other) noexcept {
        if (this != &other) {
            w = other.w;
            e = other.e;
            toll = other.toll;
        }

        return *this;
    }
};


using Bridges = std::vector<Bridge>;


inline bool haveDuplicateCity(const Bridge & b1, const Bridge & b2) noexcept {
    return b1.w == b2.w || b1.e == b2.e;
}


inline bool areCrossing(const Bridge & b1, const Bridge & b2) noexcept {
    return b1.w < b2.w && b1.e > b2.e;
}


bool validSubset(const Bridges & bridges) noexcept {
    for (auto b1 = begin(bridges); b1 != end(bridges); ++b1) {
        for (auto b2 = begin(bridges); b2 != end(bridges); ++b2) {
            if (b1 == b2) {
                continue;
            }

            if (haveDuplicateCity(*b1, *b2)) {
                return false;
            }

            if (areCrossing(*b1, *b2)) {
                return false;
            }
        }
    }

    return true;
}


int tollFor(const Bridges & bridges) noexcept {
    auto toll = 0;

    for (const auto & bridge : bridges) {
        toll += bridge.toll;
    }

    return toll;
}


int bestToll(const Bridges & bridges) noexcept {
    vector<Bridges> subsets{{}};
    vector<Bridges> newSubsets;

    auto bestToll = 0;

    for (const auto & bridge: bridges) {
        newSubsets = subsets;

        for (auto & newSubset : newSubsets) {
            newSubset.push_back(bridge);

            if(validSubset(newSubset)) {
                bestToll = max(
                    tollFor(newSubset),
                    bestToll
                );

                subsets.push_back(newSubset);
            }
        }
    }

    return bestToll;
}


Bridges convert(const vector<vector<int> > & bridgeVecs) noexcept {
    Bridges bridges;

    for (const auto & bridgeVec : bridgeVecs) {
        bridges.push_back(
            Bridge(bridgeVec)
        );
    }

    return bridges;
}


int build(int w, int e, const vector<vector<int> > & bridgeVecs) {
    auto bridges = convert(bridgeVecs);

    return bestToll(bridges);
}
