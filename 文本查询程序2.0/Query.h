//
// Created by 123456 on 2021/5/31.
//

#ifndef INC_2_0_QUERY_H
#define INC_2_0_QUERY_H

#include <memory>
#include "Query_base.h"
#include "wordQuery.h"


class Query {
    friend Query operator ~(const Query &);
    friend Query operator &(const Query &, const Query &);
    friend Query operator |(const Query &, const Query &);
public:
    Query(const std::string &s);

    QueryResult eval(const TextQuery &t) const;
    std::string rep() const;
    //std::ostream& operator<<(std::ostream &os, const Query &q);
    //friend std::ostream& operator<<(std::ostream &os, const Query &query);
private:
    Query(const std::shared_ptr<Query_base> &q) : p(q) {}
    std::shared_ptr<Query_base> p;
};




#endif //INC_2_0_QUERY_H
