// product.h
// William Horn
// Sep 6, 2017
//
// prototypes of product class for hw-1 CS311

#ifndef PRODUCT_H
#define PRODUCT_H

#include<string> // string
#include<iostream> // ostream

// **********************************************************************
// class Product - Class Definition
// **********************************************************************

// class Product
// Product: name, sales
// Invariants:
//      sales >= 0
class Product {
    public:
        // ********* Ctors, dctor, op= *********

        // Ctor
        // Sets name and sales uses default vales if name and sales
        // not passed or if just name is passed
        // Pre: more than just sales gets passed
        // Post: name and sales will both be set
        Product(std::string name="", int sales=0);

        // Big Five: using automatically written functions.
        ~Product() = default;
        Product(const Product & other) = default;
        Product(Product && other) = default;
        Product & operator=(const Product & other) = default;
        Product & operator=(Product && other) = default;

        // ************ Operators *************

        // op==
        // Pre: None
        // Post:
        //      only returns true if name and sales are both the same
        //      between the two products
        bool operator==(const Product & other) const;

        // op!=
        // Pre: None
        // Post:
        //      only true if name or sales are not the same
        //      between the two products
        bool operator!=(const Product & other) const;

        // op++ [pre]
        // Pre: None
        // Post:
        //      Sales is increamented by 1.
        //      Return is *this.
        Product & operator++();

        // op++ [post]
        // Pre: None
        // Post:
        //      Sales is increamented by 1.
        //      Return is the former value of *this.
        Product operator++(int dummy);

        // op-- [pre]
        // Pre: None
        // Post:
        //      Sales is decreased by 1, the value will not go below 0
        //      Return is *this.
        Product & operator--();

        // op-- [post]
        // Pre: None
        // Post:
        //      Sales is decreased by 1, the value will not go below 0
        //      Return is the former value of *this.
        Product operator--(int dummy);


        // ********* Member Functions ***********

        // getName
        // Pre: None
        // Post: Returns the _name property as a string
        std::string getName() const;

        // getSales
        // Pre: None
        // Post:
        //      a non negative integer that is the number
        //      of sales will be returned
        int getSales() const;

        // setName
        // Pre: None
        // Post:
        //      the name will be set to the value of newName
        void setName(std::string newName);

        // setSales
        // Pre: None
        // Post:
        //      sales will be set to the new value, if that value
        //      is negative, an error will be thrown
        void setSales(int newSales);

        // toString
        // Pre: None
        // Post:
        //      string containing class data will be return in the
        //      form
        //          <name> (sales: <sales>)
        std::string toString() const;

    private:
        // ********* Private Member Functions ************
        //
        // checkSales
        // Make sure that a sales value is valid
        // Pre: None
        // Post:
        //      will throw and error if sales is negative
        void checkSales(int sales) const;

        // *******  Data Members ************

        std::string _name;  //Name of the products
        int _sales;         // Number of sales (non-negative)
};

std::ostream& operator<<(std::ostream& out, const Product & p);

#endif // PRODUCT_H
