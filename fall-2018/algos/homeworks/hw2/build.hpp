#ifndef BUILD_HPP
#define BUILD_HPP

#include<vector>


struct Bridge {
    const int e, w, toll;
    Bridge(int e, int w, int t): e(e), w(w), toll(t) {}
    Bridge() = default;
};

using Bridges = std::vector<Bridge>;

int build(int w, int e, const std::vector<std::vector<int> > & bridges);

#endif // BUILD_HPP
