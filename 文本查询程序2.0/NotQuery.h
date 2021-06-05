//
// Created by 123456 on 2021/5/31.
//

#ifndef INC_2_0_NOTQUERY_H
#define INC_2_0_NOTQUERY_H

#include "Query_base.h"
#include "Query.h"

class NotQuery : public Query_base{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) { }
    QueryResult eval(const TextQuery &t) const;
    std::string rep() const;
    Query query;
};


#endif //INC_2_0_NOTQUERY_H
