//
// Created by 123456 on 2021/5/3.
//

#include "TextQuery.h"

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string text;
    line_no n = 0;   //记录第几行-1
    while(getline(is, text))
    {
        file->push_back(text);
        std::string word;
        std::istringstream iss(text);
        while(iss >> word)
        {
            auto& line = wm[word];   //line是一个shared_ptr<set<line_no>>
            if(!line)
            {
                line.reset(new std::set<line_no>);
            }
            line->insert(n);   //当一行出现多次时，除第一次其他什么次不做插入操作
        }
        ++n;
    }
}


QueryResult TextQuery::query(const std::string &sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto res = wm.find(sought);
    if(res == wm.end())
    {
        return QueryResult(sought, nodata, file);
    }
    else
    {
        return QueryResult(sought, res->second, file);
    }
}
