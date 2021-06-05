//
// Created by 123456 on 2021/5/3.
//

#include "QueryResult.h"

std::shared_ptr<std::vector<std::string>> QueryResult::get_file() const
{
    return file;
}

std::set<QueryResult::line_no>::iterator QueryResult::begin() const
{
    return lines->begin();
}

std::set<QueryResult::line_no>::iterator QueryResult::end() const
{
    return lines->end();
}

