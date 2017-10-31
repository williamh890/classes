// ssarray_compileall.cpp
// Glenn G. Chappell
// 18 Oct 2017
//
// For CS 311 Fall 2017
// Check Whether SSArray Package Compiles

#include "ssarray.h"  // For class SSArray
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <utility>
using std::move;


// use_all_SSArray
// Use all functionality of class SSArray.
// DO NOT ACTUALLY EXECUTE THIS FUNCTION; IT MAY DO NASTY THINGS!
void use_all_SSArray()
{
    int ii;      // For returned int values
    SSArray aa;  // For returned SSArray values

    // Member type size_type
    auto s = SSArray::size_type(9);

    // Member type value_type
    SSArray::value_type v;

    // Member type iterator
    SSArray::iterator it;

    // Member type const_iterator
    SSArray::const_iterator cit;

    // Default ctor
    const SSArray ca1;

    // Ctor from size
    SSArray a2(s);

    // Copy ctor
    SSArray a3(ca1);

    // Move ctor
    SSArray atmp1;
    SSArray a4(move(atmp1));

    // Dctor
    // Called when function exits

    // Copy op=
    aa = (a2 = ca1);

    // Move op=
    SSArray atmp2;
    aa = (a3 = move(atmp2));

    // Bracket op, non-const
    a2[s] = v;
    ii = a2[s];

    // Bracket op, const
    ii = ca1[s];

    // size
    s = ca1.size();

    // empty
    if(ca1.empty()) cout << "empty";

    // begin, non-const
    it = a2.begin();
    *it = v;
    ii = *it;

    // begin, const
    cit = ca1.begin();
    ii = *cit;

    // end, non-const
    it = a2.end()-1;
    *it = v;
    ii = *it;

    // end, const
    cit = ca1.end()-1;
    ii = *cit;

    // resize
    a2.resize(s);

    // insert
    it = a2.insert(it, v);

    // erase
    it = a2.erase(it);

    // push_back
    a2.push_back(v);

    // pop_back
    a2.pop_back();

    // swap
    a2.swap(a3);

    // So ii & aa are not flagged as unused
    cout << ii;
    cout << aa[0];
}


// Main program
// Pretend to call all functions in SSArray package. Print message.
int main()
{
    // Pretend to call use_all_SSArray, so compiler thinks we do.
    for (int i = 0; i < 6; i += 3)
    {
        if (i == 1)
            use_all_SSArray();  // Never called
    }

    // Inform the user what's up
    cout << endl;
    cout << "This program checks whether the SSArray package compiles."
         << endl;
    cout << "Calls to all package functions are compiled. However, when"
         << endl;
    cout << "this program is executed, no SSArray objects are actually"
         << endl;
    cout << "created, and no package functions are actually called."
         << endl;
    cout << endl;
    cout << "**********************************" << endl;
    cout << "* SSArray package compiles. Yay! *" << endl;
    cout << "**********************************" << endl;
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    while (cin.get() != '\n') ;

    return 0;
}

