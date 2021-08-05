//
// Created by 123456 on 2021/7/4.
//

#include "init_sqlite3_db.h"


int init_sqlite3_db(const char *db_name) {
    sqlite3 *db_file = nullptr;

    int res = sqlite3_open(db_name, &db_file);
    if (res != SQLITE_OK) {
        std::cout << "打开数据库失败 ！" << std::endl;
        return -1;
    } else {
        std::cout << "打开数据库成功 ！" << std::endl;
    }

    /* stmt是要执行语句的句柄 */
    sqlite3_stmt *stmt = nullptr;
    const char *creat_table = "create table fund_info(fund_id text primary key not null,fund_name text not null,Unit_net_worth text not null,Cumulative_net_worth text not null,'near_three_month(%)' text not null,'near_six_month(%)' text not null,'near_one_year(%)' text not null,'since_this_year(%)' text not null,'since_begin_year(%)' text not null)";
    res = sqlite3_prepare_v2(db_file, creat_table, -1, &stmt, nullptr);
    if (res != SQLITE_OK) {
        std::clog << "创建数据库表语句不合法 ！" << std::endl;
        return -1;
    } else {
        std::clog << "创建数据库表语句OK ！" << std::endl;
        //执行该创建数据库表语句
        sqlite3_step(stmt);
    }

    //清理语句句柄，准备执行下一个语句
    sqlite3_finalize(stmt);

    //关闭数据库
    if (db_file)
    {
        sqlite3_close_v2(db_file);
        db_file = nullptr;
    }
    return 0;
}
