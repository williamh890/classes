#include "contigsum.hpp"

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

int main() {
    auto vals = vector<int>{ 5, -2, 1, 12, 10, -1, 3, 4, 8, 11,
                           6, -5, -7, -3, 9, 7, 0, -4, -6, 2 };

    cout << contigSum(begin(vals), end(vals)) << endl;

    return 0;
}
