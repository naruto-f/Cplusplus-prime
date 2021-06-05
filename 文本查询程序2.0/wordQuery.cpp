//
// Created by 123456 on 2021/5/31.
//

#include "wordQuery.h"

std::string wordQuery::rep() const {
    return query_word;
}

QueryResult wordQuery::eval(const TextQuery &t) const {
    return t.query(query_word);
}
