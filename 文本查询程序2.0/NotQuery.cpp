//
// Created by 123456 on 2021/5/31.
//

#include "NotQuery.h"
#include "Query.h"


QueryResult NotQuery::eval(const TextQuery &t) const {
    auto result = query.eval(t);
    auto begin = result.begin();
    auto end = result.end();
    auto res_line = std::make_shared<std::set<line_no>> ();
    auto size = result.get_file()->size();
    line_no i = 0;
    for(i = 0; i < size; ++i)
    {
        if(begin == end || *begin != i)
        {
            res_line->insert(i);
        }
        else if(begin != end)
        {
            ++begin;
        }
    }
    return QueryResult(rep(), res_line, result.get_file());
}

/* 使用了由构造函数的单个形参向类类型的隐式转换 */
inline Query operator~(const Query &q) {
    return std::shared_ptr<Query_base> (new NotQuery(q));
}


std::string NotQuery::rep() const {
    return "~( " + query.rep() + " )";
}
