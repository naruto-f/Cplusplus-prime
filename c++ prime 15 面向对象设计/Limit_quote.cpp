//
// Created by 123456 on 2021/5/29.
//

#include "Limit_quote.h"

void Limit_quote::debug() const {
    Disc_quote::debug();
    std::cout << " max quantity = " << quantity << " "
              << " discount = " << discount << " ";
}

double Limit_quote::net_price(std::size_t n) const {
    if(quantity > n)
    {
        return price * (1 - discount) * n;
    }
    return n * price;
}
