//
// Created by 123456 on 2021/5/31.
//

#ifndef INC_2_0_BINARYQUERY_H
#define INC_2_0_BINARYQUERY_H

#include "Query_base.h"
#include "Query.h"

//接收两个运算对象的抽象基类
class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : left(l), right(r), query_method(s) { }

    /* 不覆盖Query_base的eval函数，直接继承，仍然是纯虚函数 */
    std::string rep() const;

    Query left, right;   /* 左右侧运算对象 */
    std::string query_method;  /* 运算符名称 */
};


#endif //INC_2_0_BINARYQUERY_H
