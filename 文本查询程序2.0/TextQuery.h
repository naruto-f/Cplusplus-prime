//
// Created by 123456 on 2021/5/3.
//

#ifndef TEXT_TEXTQUERY_H
#define TEXT_TEXTQUERY_H



#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <assert.h>
#include "QueryResult.h"
#include "DebugDelete.h"


class QueryResult;
class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream & is);
    QueryResult query(const std::string &) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};



#endif //TEXT_TEXTQUERY_H
