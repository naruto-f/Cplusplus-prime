#include "init_sqlite3_db.h"
#include "sourcepage_Get.h"

int main() {
    /*     初始化数据库fund_info
    const char *db_name = "/mnt/c/Users/123456/CLionProjects/fund_info/fund_info";
    int res = init_sqlite3_db(db_name);
    if(res == -1)
    {
        std::cout << "数据库初始化失败！" << std::endl;
    }  */

    std::string html_page = sourcepage_Get_By_Url("112.34.113.2", MODE_IP);
    std::cout << "html page : " << "\n" << html_page << std::endl;
    return 0;
}

// "vip.stock.finance.sina.com.cn/fund_center/index.html#hbphall",
