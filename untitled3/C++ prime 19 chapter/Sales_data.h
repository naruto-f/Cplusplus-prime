//
// Created by 123456 on 2021/6/24.
//

#ifndef C___PRIME_19_CHAPTER_SALES_DATA_H
#define C___PRIME_19_CHAPTER_SALES_DATA_H

#include <iostream>
#include <functional>
#include "isbn_mismatch.h"

class Sales_data {
    friend std::istream& operator>>(std::istream& is, Sales_data &item);
    friend std::ostream& operator<<(std::ostream& os, const Sales_data &item);
    friend Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);
    friend bool operator==(const Sales_data &lhs, const Sales_data &rhs);
    friend class std::hash<Sales_data>;
public:
    Sales_data(const std::string &s, unsigned n, double price) : bookno(s), units_sold(n), revenue() { }
    Sales_data() : Sales_data(" ", 0, 0) { }
    Sales_data(const std::string &s) : Sales_data(s, 0, 0) { }
    Sales_data(std::istream &is);
    Sales_data& operator=(const std::string &s);
    Sales_data& operator+=(const Sales_data &rhs);
    Sales_data& operator-=(const Sales_data &rhs);

    std::string isbn() const { return bookno; }
    bool higher_avg_price(double ref_price) { return ave_price() > ref_price; }
private:
    inline double ave_price() const;

    std::string bookno;
    unsigned units_sold = 0;
    double revenue = 0.0;
};


#endif //C___PRIME_19_CHAPTER_SALES_DATA_H
