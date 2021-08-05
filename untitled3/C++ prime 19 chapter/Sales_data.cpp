//
// Created by 123456 on 2021/6/24.
//

#include "Sales_data.h"

Sales_data &Sales_data::operator=(const std::string &s) {
    *this = Sales_data(s);
    return *this;
}

Sales_data &Sales_data::operator+=(const Sales_data &rhs) {
     if(isbn() != rhs.isbn())
     {
         throw isbn_mismatch("wrong isbn !", isbn(), rhs.isbn());
     }
     units_sold += rhs.units_sold;
     revenue += rhs.revenue;
     return *this;
}

Sales_data &Sales_data::operator-=(const Sales_data &rhs) {
    if(isbn() != rhs.isbn())
    {
        throw isbn_mismatch("wrong isbn !", isbn(), rhs.isbn());
    }
    units_sold -= rhs.units_sold;
    revenue -= rhs.revenue;
    return *this;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data res = lhs;
    res += rhs;
    return res;
}

bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
    return (lhs.isbn() == rhs.isbn()) && (lhs.units_sold == rhs.units_sold) && (lhs.revenue == rhs.revenue);
}

inline double Sales_data::ave_price() const {
    if(units_sold)
    {
        return revenue / units_sold;
    }
    return 0;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.ave_price();
    return os;
}

std::istream &operator>>(std::istream &is, Sales_data &item) {
    double price = 0.0;
    is >> item.bookno >> item.units_sold >> price;
    if(is)
    {
        item.revenue = price * item.units_sold;
    }
    else{
        return Sales_data()
    }

}


