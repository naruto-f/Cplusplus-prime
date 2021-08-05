//
// Created by 123456 on 2021/6/19.
//
#include "CRC.h"
#include "count.h"
#include "Print_GPIO.h"

/* 用于存放要操作或修改的指令 */


int main()
{
    Task();
    std::string os_name = "/mnt/c/Users/123456/CLionProjects/Work_Stm32_tools/ini.txt";
    std::string is_name = "/mnt/c/Users/123456/CLionProjects/Work_Stm32_tools/TEST.txt";
    std::vector<std::string> command;
    std::ifstream is(is_name);
    std::ofstream os(os_name);
    std::string line;

    while(getline(is, line))
    {
        command.push_back(line);
    }

    //count(is, os, "set");
    //count_for_all(os, 9, 1, command);
    int 2u;

    is.close();
    os.close();
    return 0;
}