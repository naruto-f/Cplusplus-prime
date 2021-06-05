//
// Created by 123456 on 2021/5/31.
//

#ifndef INC_2_0_QUERY_BASE_H
#define INC_2_0_QUERY_BASE_H

#include "TextQuery.h"
#include "QueryResult.h"

/* 所有查询类的抽象基类 */
class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no ;
    virtual ~Query_base() = default;
private:
    /* eval返回一个与当前Query匹配的QueryResult */
    virtual QueryResult eval(const TextQuery &t) const = 0;
    /* rep表示的是一个查询的string */
    virtual std::string rep() const = 0;
};


#endif //INC_2_0_QUERY_BASE_H
