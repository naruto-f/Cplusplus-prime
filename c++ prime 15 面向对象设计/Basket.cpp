//
// Created by 123456 on 2021/5/30.
//

#include "Basket.h"


bool Basket::compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) {
    return lhs->isbn() < rhs->isbn();
}

void Basket::add_item(const std::shared_ptr<Quote> &qu) {
    items.insert(qu);
}

double Basket::total_recepit(std::ostream &os) const {
    double sum = 0.0;
    auto iter = items.cbegin();
    for(iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
    {
        sum += print_total(os, **iter, items.count(*iter));
    }
    std::cout << "Total Sum : " << sum << std::endl;
    return sum;
}

void Basket::add_item(const Quote &qu) {
    items.insert(std::shared_ptr<Quote>(qu.clone()));
}

void Basket::add_item(Quote &&qu) {
    items.insert(std::shared_ptr<Quote>(std::move(qu).clone()));
}
