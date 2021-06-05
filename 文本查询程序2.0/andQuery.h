//
// Created by 123456 on 2021/5/31.
//

#ifndef INC_2_0_ANDQUERY_H
#define INC_2_0_ANDQUERY_H

#include "BinaryQuery.h"
#include "Query.h"
#include <algorithm>

class andQuery : public BinaryQuery{
    friend Query operator &(const Query &                                                                                                                                                                                                                                                                    , const Query &);
    andQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "&") { }
    QueryResult eval(const TextQuery &text) const;
};


#endif //INC_2_0_ANDQUERY_H
