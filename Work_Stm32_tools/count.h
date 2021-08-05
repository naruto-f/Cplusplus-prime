//
// Created by 123456 on 2021/6/19.
//

#ifndef WORK_STM32_TOOLS_COUNT_H
#define WORK_STM32_TOOLS_COUNT_H

#include <iostream>
#include <fstream>
#include <vector>

void count(std::ifstream &is, std::ofstream &os, std::string fun);
void count_for_all(std::ofstream &os, size_t n, size_t sw_size, std::vector<std::string> &v);

#endif //WORK_STM32_TOOLS_COUNT_H
