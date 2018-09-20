#include "build.hpp"

#include<algorithm>
#include <numeric>
using std::accumulate;
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <unordered_set>
using std::unordered_set;


int getTollFor(const Bridges & bridges) noexcept {
    for (auto b1 = begin(bridges); b1 != bridges.end(); ++b1) {
        for (auto b2 = begin(bridges); b2 != bridges.end(); ++b2) {
            if (b1 != b2 && b1->e <= b2->e)  {
                if (b1->e == b2->e || b1->w == b2->w)
                    return -1;
                if (b1->e < b2->e && b1->w > b2->w)
                    return -1;
            }
        }
    }

    auto toll = 0;
    for (const auto & bridge : bridges) {
        toll += bridge.toll;
    }

    return toll;
}


vector<Bridges> findBridgeSets(const vector<vector<int> > & bridges) noexcept {
    vector<Bridges> bridgeSubsets{{}};

    for (const auto & bridge: bridges) {
        vector<Bridges> subsetTemp = bridgeSubsets;

        for (int i = (int)subsetTemp.size() - 1; i >= 0; --i) {
            subsetTemp[i].push_back(Bridge(bridge[0], bridge[1], bridge[2]));
            bridgeSubsets.push_back(subsetTemp[i]);
        }
    }

    return bridgeSubsets;
}

void print(const vector<Bridges> &bridgeSubsets) {
    for (const auto & bridges: bridgeSubsets) {
        for (const auto & bridge: bridges) {
            cout << bridge.e << " " << bridge.w << " " << bridge.toll << endl;
        }
        cout << std::endl;
    }
}




int build(int w, int e, const vector<vector<int> > & bridges) {
    auto subsets = findBridgeSets(bridges);
    auto bestToll = 0;

    for (auto i = 0; i < subsets.size(); ++i) {
        auto toll = getTollFor(subsets[i]);

        bestToll = std::max(bestToll, toll);
    }

    return bestToll;
}

