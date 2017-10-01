// da3.cpp
// William Horn
// 24 Sep 2017
//
// For CS 311 Fall 2017
// Source for Assignment 3 Functions

#include "da3.h"       // For Assignment 3 prototypes & templates
#include <functional>
using std::function;


void callBetween(const function<void()> & start,
                 const function<void()> & middle,
                 const function<void()> & finish)
{
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


int gcd(int a,
        int b)
{
    if (a == 0) return b;
    if ( a > b ) return gcd(b, a);
    return gcd(b % a, a);
}

