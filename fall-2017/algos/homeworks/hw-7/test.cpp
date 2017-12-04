#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

#include "treesort.h"

int main() {
    vector<int> x{9,3,2,1,5};

    treesort(x.begin(), x.end());

    for (auto v : x) {
        cout << v << endl;
    }
}
