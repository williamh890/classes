// product.h
// William Horn
// Sep 6, 2017
// prototypes of product class for hw-1 CS311

#ifndef PRODUCT_H
#define PRODUCT_H

#include<string> // string
#include<iostream> // ostream


class Product {
    public:
        Product(std::string name="", int sales=0);

        ~TimeOfDay() = default;
        TimeOfDay(const TimeOfDay & other) = default;
        TimeOfDay & operator=(const TimeOfDay & other) = default;
        TimeOfDay & operator=(TimeOfDay && other) = default;

        std::string getName() const;
        int getSales() const;

        void setName(std::string newName);
        void setSales(int newSales);

        std::string toString() const;

        bool operator==(const Product & other) const;
        bool operator!=(const Product & other) const;

        Product & operator++();
        Product operator++(int dummy);

        Product & operator--();
        Product operator--(int dummy);

    private:
        void checkSales(int sales) const;

        std::string _name;
        int _sales;
};

std::ostream& operator<<(std::ostream& out, const Product & p);

#endif // PRODUCT_H
