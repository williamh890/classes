#ifndef BUILD_HPP
#define BUILD_HPP

#include<vector>


struct Bridge {
    const int e, w, toll;
    Bridge(const std::vector<int> & b): e(b[0]), w(b[1]), toll(b[2]) {}
    Bridge() = default;
};

using Bridges = std::vector<Bridge>;

int build(int w, int e, const std::vector<std::vector<int> > & bridges);

#endif // BUILD_HPP
