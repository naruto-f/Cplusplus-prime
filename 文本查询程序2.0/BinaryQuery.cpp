//
// Created by 123456 on 2021/5/31.
//

#include "BinaryQuery.h"

std::string BinaryQuery::rep() const {
    return "( " + left.rep() + " " + query_method + " " + right.rep() + " )";
}


