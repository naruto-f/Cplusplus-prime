//
// Created by 123456 on 2021/5/31.
//

#ifndef INC_2_0_WORDQUERY_H
#define INC_2_0_WORDQUERY_H

#include "Query_base.h"
#include "Query.h"

class wordQuery : public Query_base {
    /* 和Query_base一样， wordQuery没有公有数据成员 */
    friend class Query;    /* 因为Query要使用wordQuery的构造函数，所以要将Query设为友元类 */
    wordQuery(const std::string &word) : query_word(word) { }
    QueryResult eval(const TextQuery &t) const;
    std::string rep() const;
    std::string query_word;
};


#endif //INC_2_0_WORDQUERY_H
