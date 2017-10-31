
#include "tssarray.h"
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
void printArray(const TSSArray<T> & arr) {
    for (auto i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main() {
    TSSArray<int> t;

    printArray(t);
    t.push_back(2);
    t.insert(t.begin() + 1,2);
    printArray(t);

    return 0;
}
