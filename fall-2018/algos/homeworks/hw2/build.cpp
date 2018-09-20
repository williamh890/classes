#include "build.hpp"

#include<algorithm>
using std::max;
#include <vector>
using std::vector;

struct Bridge {
    const int w, e, toll;

    Bridge() = default;
    Bridge(const std::vector<int> & b): w(b[1]), e(b[0]), toll(b[2]) {}
};

using Bridges = std::vector<Bridge>;


inline bool haveDuplicateCity(const Bridge & b1, const Bridge & b2) noexcept {
    return b1.w == b2.w || b1.e == b2.e;
}


inline bool areCrossing(const Bridge & b1, const Bridge & b2) noexcept {
    return b1.w < b2.w && b1.e > b2.e;
}


int tollFor(const Bridges & bridges) noexcept {
    auto toll = 0;
    for (auto b1 = begin(bridges); b1 != bridges.end(); ++b1) {
        for (auto b2 = begin(bridges); b2 != bridges.end(); ++b2) {
            if (b1 == b2)  {
                continue;
            }

            if (haveDuplicateCity(*b1, *b2) || areCrossing(*b1, *b2))
                return -1;
        }

        toll += b1->toll;
    }
    return toll;
}


int bestTollFrom(const vector<Bridges> & subsets) {
    auto bestToll = 0;

    for (const auto & subset: subsets) {
        bestToll = max(
            bestToll,
            tollFor(subset)
        );
    }

    return bestToll;
}


vector<Bridges> allSubsetsOf(const Bridges & bridges) noexcept {
    vector<Bridges> bridgeSubsets{{}};

    for (const auto & bridge: bridges) {
        vector<Bridges> subsetTemp = bridgeSubsets;

        for (int i = (int)subsetTemp.size() - 1; i >= 0; --i) {
            subsetTemp[i].push_back(bridge);
            bridgeSubsets.push_back(subsetTemp[i]);
        }
    }

    return bridgeSubsets;
}


Bridges convert(const vector<vector<int> > & bridgeVecs) noexcept {
    Bridges bridges;
    for (const auto & bridgeVec : bridgeVecs ) {
        bridges.push_back(
            Bridge(bridgeVec)
        );
    }

    return bridges;
}


int build(int w, int e, const vector<vector<int> > & bridgeVecs) {
    auto bridges = convert(bridgeVecs);

    auto subsets = allSubsetsOf(bridges);

    return bestTollFrom(subsets);
}
