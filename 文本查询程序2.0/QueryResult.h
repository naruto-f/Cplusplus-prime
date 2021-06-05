//
// Created by 123456 on 2021/5/3.
//

#ifndef TEXT_QUERYRESULT_H
#define TEXT_QUERYRESULT_H



#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <memory>

class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f):
            sought(s), lines(p), file(f) { }
    std::shared_ptr<std::vector<std::string>> get_file() const;
    std::set<line_no>::iterator begin() const;
    std::set<line_no>::iterator end() const;
private:
    std::string sought;  //查询的单词
    std::shared_ptr<std::vector<std::string>> file;  //保存每一行的文本
    std::shared_ptr<std::set<line_no>> lines;    //记录行号
};



#endif //TEXT_QUERYRESULT_H
