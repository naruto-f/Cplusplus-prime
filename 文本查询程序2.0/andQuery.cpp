//
// Created by 123456 on 2021/5/31.
//

#include "andQuery.h"

inline Query operator&(const Query &l, const Query &r) {
    return std::shared_ptr<Query_base> (new andQuery(l, r));
}

QueryResult andQuery::eval(const TextQuery &text) const {
    auto l = left.eval(text);
    auto r = right.eval(text);
    auto ret_line = std::make_shared<std::set<line_no>>();
    /* 使用标准库函数set_intersection将两个范围的交集写入一个目的迭代器内 */
    std::set_intersection(l.begin(), l.end(),
                          r.begin(), r.end(),
                          std::inserter(*ret_line, ret_line->begin()));
    return QueryResult(rep(), ret_line, l.get_file());
}


