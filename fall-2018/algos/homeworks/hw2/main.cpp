#include "build.hpp"

#include <iostream>
#include <cmath>        // for std::sqrt
#include <vector>        // for std::sqrt
using std::vector;

int m() {
   auto maxToll = build(3, 3, {
        { 0, 1, 3 },
        { 1, 1, 5 },
    });

   std::cout << maxToll << " == 5" << std::endl;

   maxToll = build(3, 3, {
        { 0, 1, 3 },
        { 1, 1, 5 },
        { 1, 2, 4 },
        { 2, 0, 8 },
        { 2, 2, 6 }
    });


   std::cout << maxToll << " == 11" << std::endl;
}

using Brg = std::vector<int>;

int main() {
    int i=0;
    while(i++ < 5) {
        std::cout << i << std::endl;
    int w = 20;
    int e = w;
    vector<Brg> bs;
    auto phi = (1+sqrt(5)/2);
    auto phipower = phi;

    for(auto i=0;i<w/2;++i) {
        if (fmod(1,phipower) > 0.5) {
            bs.push_back(Brg {  2*i,  2*i+1,  1 });
            bs.push_back(Brg {  2*i+1,  2*i,  2 });
        } else {
            bs.push_back(Brg {  2*i,  2*i+1,  2 });
            bs.push_back(Brg {  2*i+1,  2*i,  1 });
        }
        phipower *= phi;
    }

    build(w, e, bs);

}
}
