//
// Created by 123456 on 2021/7/4.
//

#include "Date_handle.h"

int data_handle_to_db(std::string &sourcepage, const char *db_name)
{
    sqlite3 *conn = nullptr;
    int res = sqlite3_open(db_name, &conn);
    if (res != SQLITE_OK) {
        std::cout << "打开数据库失败 ！" << std::endl;
        return -1;
    } else {
        std::cout << "打开数据库成功 ！" << std::endl;
    }
    //用于遍历一个string中所有的正则表达式匹配字段的迭代器
    //std::sregex_iterator it;
    //std::sregex_iterator end_it;

    //存放匹配reg1的字符串
    std::vector<std::smatch> reg1_list;

    //存放匹配reg2的字符串
    std::vector<std::smatch> reg2_list;

    //存放匹配reg3的字符串
    std::vector<std::smatch> reg3_list;

    //存放匹配reg4的字符串
    std::vector<std::smatch> reg4_list;

    //存放匹配reg5的字符串
    std::vector<std::smatch> reg5_list;

    //存放匹配reg6的字符串
    std::vector<std::smatch> reg6_list;

    //存放基金代码的列表
    std::vector<std::string> fund_id_list;

    //存放基金名称的列表
    std::vector<std::string> fund_name_list;

    //存放单位净值的列表
    std::vector<std::string> Unit_net_worth_list;

    //存放累计净值的列表
    std::vector<std::string> Cumulative_net_worth_list;

    //存放近三个月(%)的列表
    std::vector<std::string> near_three_month_list;

    //存放近六个月(%)的列表
    std::vector<std::string> near_six_month_list;

    //存放近一年(%)的列表
    std::vector<std::string> near_one_year_list;

    //存放今年以来(%)的列表
    std::vector<std::string> since_this_year;

    //存放成立以来(%)的列表
    std::vector<std::string> since_begin_year;

    /* 使用正则表达式处理数据 */
    std::string reg1 = "href=\"http://biz.finance.sina.com.cn/suggest/lookup_n.php?.*?\" target=\"_blank\" title=\".*?\">";
    std::string reg2 = "<th class=\"r_20 colorize\">[0-9]{1}.[0-9]{4}</th>";
    std::string reg3 = "<th class=\"r_20\">[0-9]{1,5}.[0-9]{4}</th>";
    std::string reg6 = "<th class=\" r_20\">([-|0-9]{1,5}.[0-9]{4})|([-]{2})</th>";
    std::string reg4 = "<th class=\"sort_down r_20\">[0-9]{2}.[0-9]{4}</th>";
    std::string reg5 = "title=\"(.*?)\"";

    std::regex r1(reg1);
    std::regex r2(reg2);
    std::regex r3(reg3);
    std::regex r4(reg4);
    std::regex r5(reg5);
    std::regex r6(reg6);



    for(std::sregex_iterator it(sourcepage.begin(), sourcepage.end(), r1), end_it; it != end_it; ++it)
    {
        reg1_list.push_back(*it);
    }

    for(std::sregex_iterator it(sourcepage.begin(), sourcepage.end(), r2), end_it; it != end_it; ++it)
    {
        reg2_list.push_back(*it);
    }

    for(std::sregex_iterator it(sourcepage.begin(), sourcepage.end(), r3), end_it; it != end_it; ++it)
    {
        reg3_list.push_back(*it);
    }

    for(std::sregex_iterator it(sourcepage.begin(), sourcepage.end(), r4), end_it; it != end_it; ++it)
    {
        reg4_list.push_back(*it);
    }

    for(std::sregex_iterator it(sourcepage.begin(), sourcepage.end(), r6), end_it; it != end_it; ++it)
    {
        reg6_list.push_back(*it);
    }

    std::smatch temp;
    std::string s;
    for(auto r1_str : reg1_list)
    {
        s = r1_str.str();
        std::regex_search(s, temp, r5);
        fund_name_list.push_back(temp.str());
        fund_id_list.push_back(cut_string(r1_str.str(), 60, 66));
    }

    for(int j = 0; j < reg2_list.size(); ++j)
    {
        if(j % 2 == 0)
        {
            Unit_net_worth_list.push_back(cut_string(reg2_list[j].str(), 26, -5));
        } else{
            Cumulative_net_worth_list.push_back(cut_string(reg2_list[j].str(), 26, -5));
        }
    }

    for(int k = 0; k < reg3_list.size(); ++k)
    {
        if(k % 2 == 0)
        {
            near_three_month_list.push_back(cut_string(reg3_list[k].str(), 17, -5));
        } else{
            near_six_month_list.push_back(cut_string(reg3_list[k].str(), 17, -5));
        }
    }

    for(auto r4_str : reg4_list)
    {
        since_this_year.push_back(cut_string(r4_str.str(), 27, -5));
    }

    for(int z = 0; z < reg6_list.size(); ++z)
    {

    }

    std::string sql_insert = "";
    sqlite3_stmt *stmt = nullptr;
    for(int n = 0; n < fund_id_list.size(); ++n)
    {
        sql_insert = "insert into fund_info(fund_id, fund_name, Unit_net_worth, Cumulative_net_worth, 'near_three_month(%)', 'near_six_month(%)', 'near_one_year(%)', 'since_this_year(%)', 'since_begin_year(%)')values(?, ?, ?, ?, ?, ?, ?, ?, ?)";
        sqlite3_prepare_v2(conn, sql_insert.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, fund_id_list[n].c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, fund_name_list[n].c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, Unit_net_worth_list[n].c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, Cumulative_net_worth_list[n].c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, near_three_month_list[n].c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 6, near_six_month_list[n].c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 7, near_one_year_list[n].c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 8, since_this_year[n].c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 9, since_begin_year[n].c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    sqlite3_close(conn);
    return 0;
}

std::string cut_string(std::string str, int left, int right, int mode) {
    if(right > str.size() || left < 0)
    {
        return "0";
    }
    std::string res;
    if(right > 0)
    {
        for(int i = left; i < right; ++i)
        {
            res += str[i];
        }
    }
    if(right < 0)
    {
        for(int i = left; i < str.size() - abs(right); ++i)
        {
            res += str[i];
        }
    }
    return res;
}
