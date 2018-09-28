// build.cpp
// William Horn
// Sept 20, 2018
// CS 411 HW2

#include "build.hpp"

#include<algorithm>
#include<numeric>
#include<functional>
#include<iterator>
#include <vector>


struct Bridge {
    int w, e, toll;

    Bridge() = default;
    Bridge(const std::vector<int> & b): w(b[1]), e(b[0]), toll(b[2]) {}
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
    return b1.w < b2.w && b1.e > b2.e ||
        b1.w > b2.w && b1.e < b2.e;
}


bool validSubset(const Bridge & newBridge, const Bridges & bridges) noexcept {
    return std::none_of(begin(bridges), end(bridges),
        [&newBridge](const Bridge & bridge) -> bool {
        return
            haveDuplicateCity(bridge, newBridge) ||
            areCrossing(bridge, newBridge);
    });
}


int tollFor(const Bridges & bridges) noexcept {
    return std::accumulate(begin(bridges), end(bridges), 0,
        [](const int& total, const Bridge& bridge) {
            return total + bridge.toll;
    });
}


std::vector<Bridges> allValidSubsets(const Bridges & bridges) noexcept {
    auto subsets = std::vector<Bridges>{{}};

    for (const auto & bridge: bridges) {
        for (auto i = (int)subsets.size() - 1; i >= 0; --i) {
            if(!validSubset(bridge, subsets[i])) {
                continue;
            }

            auto validSubset = subsets[i];
            validSubset.push_back(bridge);
            subsets.push_back(validSubset);

        }
    }

    return subsets;
}


int bestToll(const std::vector<Bridges> & subsets) {
    std::vector<int> tolls;

    std::transform(begin(subsets), end(subsets), back_inserter(tolls),
        [](const Bridges & subset) -> int {
            return tollFor(subset);
    });

    return *std::max_element(begin(tolls), end(tolls), std::less<int>());
}


Bridges convert(const std::vector<std::vector<int> > & bridgeVecs) noexcept {
    Bridges bridges;

    std::transform(begin(bridgeVecs), end(bridgeVecs), back_inserter(bridges),
        [](const std::vector<int> & vec) -> Bridge {
            return Bridge(vec);
    });

    return bridges;
}


int build(int w, int e, const std::vector<std::vector<int> > & bridgeVecs) {
    auto bridges = convert(bridgeVecs);

    auto subsets = allValidSubsets(bridges);

    return bestToll(subsets);
}
