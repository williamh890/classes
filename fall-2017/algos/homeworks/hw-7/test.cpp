#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

#include "treesort.h"

int main() {
    TreeNode<int> root(12);
    vector<int> x{1,2,3,4,5};

    root.make(x.begin(), x.end());

    root.traverse();
}
