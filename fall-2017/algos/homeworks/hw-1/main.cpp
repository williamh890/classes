
#include"product.h"

#include <iostream>
using std::cout;
using std::endl;


int main()
{
    Product p;
    Product p2("paper", 100);

    p.setName("board");
    p.setSales(10);

    p++;
    ++p;
    --p2;
    p2--;

    cout << p2 << ", " << p << endl;

    cout << (bool)(p2 == p) << ", " << (bool)(p != p2) << endl;

    return 0;
}
