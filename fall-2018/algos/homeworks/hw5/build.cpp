// build.cpp
// William Horn
// 25/11/2018
// HW5: Dynamic Programming

#include "build.hpp"

#include <vector>
using std::vector;
#include <algorithm>
using std::max;


using Cities = vector<vector<int>>;
using Connections = vector<vector<int>>;

const int NULL_BRIDGE = -1;
const int WEST = 0;
const int EAST = 1;
const int TOLL = 2;

int toll(int, int, Cities&, Connections&);

int build(int w, int e, const vector<Bridge> & bridges) {
    Cities cities(w, vector<int>(e, NULL_BRIDGE));
    Connections connections(w, vector<int>(e, 0));

    for (const auto &b: bridges) {
        connections[b[WEST]][b[EAST]] = max(
            connections[b[WEST]][b[EAST]],
            b[TOLL]
        );
    }

    return toll(w - 1, e - 1, cities, connections);
}


int toll(int w, int e, Cities & cities, Connections & connections) {
    if (cities[w][e] != NULL_BRIDGE) {
        return cities[w][e];
    }

    auto here = connections[w][e];
    int result;

    if (w == 0 and e == 0) {
        result = here;
    } else if (w == 0) {
        result = max(
            here,
            toll(w, e - 1, cities, connections)
        );
    } else if (e == 0) {
        result = max(
            here,
            toll(w - 1, e, cities, connections)
        );
    } else {
        result = max({
            here + toll(w - 1, e - 1, cities, connections),
            toll(w - 1, e, cities, connections),
            toll(w, e - 1, cities, connections)
        });
    }

    cities[w][e] = result;
    return result;
};
