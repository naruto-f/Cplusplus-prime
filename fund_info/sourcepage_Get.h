//
// Created by 123456 on 2021/7/4.
//

#ifndef FUND_INFO_SOURCEPAGE_GET_H
#define FUND_INFO_SOURCEPAGE_GET_H

#define BUFFSIZE 1024


#include <iostream>

/* 可供选择的第二个参数的传入形式 */
enum {MODE_IP, MODE_URL};

/*
 * 函数功能：使用socket从指定url获取该url的网页源码
 * 参数url_str : 网页的域名或ip地址的字符串形式
 * 参数mode : 传入url_str的模式, 可选参数①MODE_IP ②MODE_URL
 */
std::string sourcepage_Get_By_Url(const char *url_str, unsigned mode);

#endif //FUND_INFO_SOURCEPAGE_GET_H
