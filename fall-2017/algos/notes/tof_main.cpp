// tod_main.cpp
// William Horn
// Sep 6
// Simple main for time of day

#include "timeofday.h"

#include<iostream>
using std::cout;
using std::endl;


int main() {
    TimeOfDay t1;
    TimeOfDay t2(14, 13, 45);

    t2++;
    ++t2;
    --t2;
    t2--;
    cout << "t2" << t2 << endl;

    unsigned int h, m, s;
    t2.getTime(h, m, s);
    cout << "HMS from t2: " << h << ", " << m << ", " << s << endl;
    t2.setTime(0,0,0);

}
