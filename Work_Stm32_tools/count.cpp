//
// Created by 123456 on 2021/6/19.
//
#include "count.h"

void count(std::ifstream &is, std::ofstream &os, std::string fun)
{
    int i = 101;
    int j = 1;
    int delay = (fun == "get") ? 1000 : 5000;
    std::string s1 = "N";
    std::string s2 = "=";
    std::string s3 = " status";
    std::string s4 = ",";
    std::string s5 = (fun == "get") ? "get sw" : "set sw";
    std::string s6 = "H";
    std::string line;
    while(getline(is, line))
    {
        os << s1 + std::to_string(i++) + s2 + std::to_string(j) + s4 + s5 + std::to_string(j) + s3 + s4 + std::to_string(delay) << std::endl;
        os << s1 + std::to_string(j++) + s2 + s6 + s4 + line << std::endl;
        os << std::endl;
    }
}

/* 提醒 : 参数n只能设置为2或3！*/
void count_for_all(std::ofstream &os, size_t n, size_t sw_size, std::vector<std::string> &v) {
    if(n * sw_size > 99)
    {
        std::cout << "超出串口调试助手存放指令数量限制！！！" << std::endl;
        return;
    }
    if(n != 2 && n != 3)
    {
        std::cout << "参数n设置不符合要求！！！" << std::endl;
        return;
    }
    std::vector<std::string> fun_name = {"open sw", "get sw", "close sw"};
    std::vector<std::string> s3 = {"", " status", ""};
    int i = 101;
    int j = 1;
    int delay = 1000;
    std::string s1 = "N";
    std::string s2 = "=";
    std::string s4 = ",";
    std::string s6 = "H";
    std::string line;
    for(int k = 0; k < sw_size; ++k)
    {
        for(int l = 0; l < n; ++l)
        {
            os << s1 + std::to_string(i++) + s2 + std::to_string(j) + s4 + fun_name[l] + std::to_string(k + 1) + s3[l] + s4 + std::to_string(delay) << std::endl;
            os << s1 + std::to_string(j++) + s2 + s6 + s4 + v[l * sw_size + k] << std::endl;
            os << std::endl;
        }
    }

}

/*
int main()
{
    std::string os_name = "/mnt/c/Users/123456/CLionProjects/Work_Stm32_tools/ini.txt";
    std::string is_name = "/mnt/c/Users/123456/CLionProjects/Work_Stm32_tools/TEST.txt";
    std::ifstream is(is_name);
    std::ofstream os(os_name);
    count(is, os, "set");
    is.close();
    os.close();
    return 0;
}
*/

