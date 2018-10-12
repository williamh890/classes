#include "inversions.hpp"

#include <iostream>
using std::cout;
using std::endl;
#include <vector>

int main() {
    std::vector<int> v;
    const int N = 5;
    for (int i = 0; i < N; ++i)
    {
        std::cout << N-i << " ";
        std::cout << N-i << " ";
        v.push_back(N-i);
        v.push_back(N-i);
    } cout << endl;
    size_t ans = size_t(N*(N-1)*2);    // Correct result

    cout << inversions(v.begin(), v.end()) << " " << ans << endl;
}
