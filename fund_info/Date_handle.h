//
// Created by 123456 on 2021/7/4.
//

#ifndef FUND_INFO_DATE_HANDLE_H
#define FUND_INFO_DATE_HANDLE_H

#include <iostream>
#include <regex>
#include <vector>
#include <sqlite3.h>


/* 函数功能 : 类似于python的切片操作
 * 参数str : 要进行截取的string类型的字符串
 * 参数left : 开始截取的字符串中的字符下标
 * 参数right : 截取的最后一个字符的尾后位置
 * 参数mode : 截取的模式，从左向右或从右向左，可选参数1, -1, 1为从左向右截取, -1为从右向左截取
 */
std::string cut_string(std::string str, int left, int right, int mode = 1);
void data_handle_to_db(std::string &sourcepage);

#endif //FUND_INFO_DATE_HANDLE_H
