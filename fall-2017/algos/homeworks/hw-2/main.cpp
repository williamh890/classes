
#include "ksarray.h"
#include<iostream>
using std::cout;
using std::endl;
#include<utility>
using std::move;


int main() {

    KSArray<int> a(3);
    a[1] = 1;
    KSArray<int> b{ 5 };
    b[3] = 100;
    a = move(b);
    cout << a[1] << endl;
    cout << a.size() << endl;
    cout << "exiting..." << endl;
}
