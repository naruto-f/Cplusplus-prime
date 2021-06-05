//
// Created by 123456 on 2021/5/29.
//

#ifndef C___PRIME_15__LIMIT_QUOTE_H
#define C___PRIME_15__LIMIT_QUOTE_H

#include "Disc_quote.h"

class Limit_quote : public Disc_quote{
public:
    Limit_quote() = default;
    Limit_quote(std::string &bno, double p, std::size_t max, double b)
    : Disc_quote(bno, p, max, b) {}

    double net_price(std::size_t n) const override;
    void debug() const override;
};


#endif //C___PRIME_15__LIMIT_QUOTE_H
