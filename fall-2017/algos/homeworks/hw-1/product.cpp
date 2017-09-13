// product.cpp
// William Horn
// Sep 6, 2017
// definitions of product class for hw-1 CS311

#include "product.h" // For Product

#include<string>
using std::string;
#include<iostream>
using std::cout;
using std::ostream;
using std::endl;
#include<sstream>
using std::ostringstream;
#include<stdexcept>
using std::runtime_error;

// **********************************************************************
// class Product - Member Definitions
// **********************************************************************


// Product::Product
// (See header for docs.)
Product::Product(string name, int sales) : _name(name) {
    setSales(sales);
}


// Product::checkSales
// (See header for docs.)
void Product::checkSales(int possible_sales) const {
    if (possible_sales < 0) {
        ostringstream out;
        out << "Sales can not be negative, given '" << possible_sales << "'.";
        throw runtime_error(out.str());
    }
}


// Product::getName
// (See header for docs.)
string Product::getName() const {
    return _name;
}


// Product::getSales
// (See header for docs.)
int Product::getSales() const {
    return _sales;
}


// Product::setName
// (See header for docs.)
void Product::setName(string newName){
    _name = newName;
};


// Product::setSales
// (See header for docs.)
void Product::setSales(int newSales) {
    checkSales(newSales);
    _sales = newSales;
};


// Product::toString
// (See header for docs.)
string Product::toString() const {
    ostringstream out;
    out << _name << " (sales: " << _sales << ")";

    return out.str();
};


// Product::operator==
// (See header for docs.)
bool Product::operator==(const Product & other) const {
    return this->_name == other._name && this->_sales == other._sales;
};


// Product::operator!=
// (See header for docs.)
bool Product::operator!=(const Product & other) const {
    return !(*this == other);
};


// Product::operator++
// (See header for docs.)
Product& Product::operator++() {
    _sales++;
    return *this;
}


// Product::operator++
// (See header for docs.)
Product Product::operator++(int) {
    Product tmp(*this);
    operator++();
    return tmp;
}


// Product::operator--
// (See header for docs.)
Product& Product::operator--() {
    if (_sales <= 0) {
        _sales = 0;
    }
    else {
        _sales--;
    }

    return *this;
}


// Product::operator--
// (See header for docs.)
Product Product::operator--(int) {
    Product tmp(*this);
    operator--();

    return tmp;
}

// **********************************************************************
// class Product - Definitions of accociated global operators
// **********************************************************************


// operator<<
// (See header for docs.)
ostream& operator<<(ostream& out, const Product & p) {
   return out << p.toString();
}

