// product.cpp
// William Horn
// Sep 6, 2017
// definitions of product class for hw-1 CS311

#include "product.h"

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


Product::Product(string name, int sales) : _name(name) {
    checkSales(sales);
    _sales = sales;
}


void Product::checkSales(int possible_sales) const {
    if (possible_sales < 0) {
        ostringstream out;
        out << "Sales can not be negative, given '" << possible_sales << "'.";
        throw runtime_error(out.str());
    }
}


string Product::getName() const {
    return _name;
}


int Product::getSales() const {
    return _sales;
}


void Product::setName(string newName){
    _name = newName;
};


void Product::setSales(int newSales) {
    checkSales(newSales);
    _sales = newSales;
};


string Product::toString() const {
    ostringstream out;
    out << _name << " (sales: " << _sales << ")";

    return out.str();
};


bool Product::operator==(const Product & other) const {
    return this->_name == other._name && this->_sales == other._sales;
};


bool Product::operator!=(const Product & other) const {
    return !(*this == other);
};


Product& Product::operator++() {
    _sales++;
    return *this;
}


Product Product::operator++(int) {
    Product tmp(*this);
    operator++();
    return tmp;
}


Product& Product::operator--() {
    _sales--;
    return *this;
}


Product Product::operator--(int) {
    Product tmp(*this);
    operator--();
    return tmp;
}


ostream& operator<<(ostream& out, const Product & p) {
   return out << p.toString();
}
