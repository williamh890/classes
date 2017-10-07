// da3.cpp
// William Horn
// 24 Sep 2017
//
// For CS 311 Fall 2017
// Source for Assignment 3 Functions

#include "da3.h"       // For Assignment 3 prototypes & templates
#include <functional>
using std::function;
#include <utility>
using std::swap;


// (see header for docs)
void callBetween(const function<void()> & start,
                 const function<void()> & middle,
                 const function<void()> & finish) {
    start();
    try {
        middle();
    }
    catch(...) {
        finish();
        throw;
    }
    finish();
}

// gcd_worker
// pre: a > b
// pos gcd will be returned
int gcd_worker(int a, int b) {
    if (a == 0)
        return b;
    else
        return gcd(b % a, a);
}


// (see header for docs)
int gcd(int a, int b) {
    if ( a > b )
        swap(a,b);

    return gcd_worker(a,b);

}


