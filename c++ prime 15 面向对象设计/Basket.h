//
// Created by 123456 on 2021/5/30.
//

#ifndef C___PRIME_15__BASKET_H
#define C___PRIME_15__BASKET_H

#include <set>
#include <memory>
#include "Quote.h"

double print_total(std::ostream &os, const Quote &item, std::size_t n);
class Basket {
public:
    /* Basket类使用默认的构造函数和拷贝控制成员 */
    void add_item(const std::shared_ptr<Quote> &qu);   /* 向set中添加元素*/
    void add_item(const Quote &qu);
    void add_item(Quote &&qu);
    double total_recepit(std::ostream &os) const;
private:
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs);
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};


#endif //C___PRIME_15__BASKET_H
