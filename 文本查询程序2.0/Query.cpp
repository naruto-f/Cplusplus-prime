//
// Created by 123456 on 2021/5/31.
//

#include "Query.h"

QueryResult Query::eval(const TextQuery &t) const {
    return p->eval(t);
}

std::string Query::rep() const {
    return p->rep();
}

std::ostream &operator<<(std::ostream &os, const Query &query) {
    return os << query.rep();
}


inline Query::Query(const std::string &s) : p(new wordQuery(s)) { }



