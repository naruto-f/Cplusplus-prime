//
// Created by 123456 on 2021/7/4.
//
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include "sourcepage_Get.h"

std::string sourcepage_Get_By_Url(const char *url_str, unsigned mode) {
    if(mode != MODE_IP && mode != MODE_URL)
    {
        std::cout << "参数选择错误 ！" << std::endl;
        return "";
    }
    /* 创建套接字并与server端建立连接 */
    auto lfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(lfd == -1)
    {
        std::cout << "套接字创建失败！" << std::endl;
        return "";
    }
    else{
        std::cout << "套接字创建成功！" << std::endl;
    }
    //const char *domain_name = "http://vip.stock.finance.sina.com.cn/fund_center/index.html#hbphall";
    struct sockaddr_in pin;
    unsigned short port = 443;
    if(mode == MODE_URL)
    {
        addrinfo *result;
        addrinfo hint;
        in_addr i_addr;
        int addrbuf;
        memset(&hint, 0, sizeof(struct addrinfo));
        hint.ai_family = AF_INET;
        hint.ai_flags = AI_PASSIVE;
        hint.ai_protocol = 0;
        hint.ai_socktype = SOCK_STREAM;
        int res_addr = getaddrinfo(url_str, "80", &hint, &result);
        if(res_addr != 0)
        {
            std::cout << "ip地址解析失败 ！" << std::endl;
            return "";
        } else{
            std::cout << "ip地址解析成功 ！" << std::endl;
        }
        auto cur_addr = (struct sockaddr_in *)(result->ai_addr);
        //int res1 = inet_pton(AF_INET, &cur_addr->sin_addr, &addrbuf);
        i_addr.s_addr = cur_addr->sin_addr.s_addr;
        pin.sin_addr.s_addr = inet_addr(inet_ntoa(i_addr));
        pin.sin_port = htons((*cur_addr).sin_port);
        freeaddrinfo(result);
    } else{
        pin.sin_addr.s_addr = inet_addr(url_str);
        pin.sin_port = htons(port);
    }
    pin.sin_family = AF_INET;

    auto res = connect(lfd, (struct sockaddr *)&pin, sizeof(pin));
    if(res == -1)
    {
        std::cout << "与网页对应服务器建立连接失败！" << std::endl;
        return "";
    } else{
        std::cout << "与网页对应服务器建立连接成功！" << std::endl;
    }

    /* 构造请求包头并发送, 使服务器返回网页源码 */
    std::string request_header = "";
//    request_header += "GET /fund_center/data/jsonp.php/IO.XSRV2.CallbackList['32sd$CbNssSUuKmO']/NetValueReturn_Service.NetValueReturnOpen?page=2&num=40&sort=form_year&asc=0&ccode=&type2=0&type3= HTTP/1.1\n";
//    request_header += "Host: vip.stock.finance.sina.com.cn\n";
//    request_header += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:84.0) Gecko/20100101 Firefox/84.0\n";
//    request_header += "Accept: */*\n";
//    //request_header += "Accept-Encoding: deflate\n";
//    request_header += "Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2\n";
//    request_header += "Connection: keep-alive\n";
//    request_header += "Referer: http://vip.stock.finance.sina.com.cn/fund_center/index.html\n";
//    //request_header += "Cookie: SINAGLOBAL=114.104.94.192_1616647546.421980; UOR=www.baidu.com,finance.sina.com.cn,; ULV=1625449909938:4:4:1:222.211.213.155_1625449841.786123:1625294003486; U_TRS1=0000009b.d6b85c19.60de6e6e.c1afb0fb; SGUID=1625190036524_55045121; __utma=269849203.1235634480.1625190038.1625190038.1625190038.1; __utmz=269849203.1625190038.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); UM_distinctid=17a64e000a12be-0d5b71d56d3f62-4c3f207e-e1000-17a64e000a213f; SR_SEL=1_511; FSINAGLOBAL=114.104.94.192_1616647546.421980; SUB=_2AkMXguHOf8NxqwJRmPEWy2vlaYV1ywrEieKh3hAVJRMyHRl-yD92qnMmtRB6PALPIakPSyKYceuBxrT-bZHFLmrycd8T; SUBP=0033WrSXqPxfM72-Ws9jqgMF55529P9D9WW8BPYNwvlUJ6M9svz6VyI.; Apache=222.211.213.155_1625449841.786123; MONEY-FINANCE-SINA-COM-CN-WEB5=\n";

    request_header += "GET / HTTP/1.1\n";
    request_header += "Host: www.baidu.com\n";
    request_header += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:84.0) Gecko/20100101 Firefox/84.0\n";
    request_header += "Accept: text/html\n";
    request_header += "Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2\n";
    request_header += "Accept-Encoding: deflate\n";
    request_header += "Connection: keep-alive\n";
    request_header += "Cookie: BAIDUID=CC2C275345D3195C9F8272D8F146D917:FG=1; BIDUPSID=CC2C275345D3195CBB3DD7775E3C5695; PSTM=1610709552; BDUSS=VVbDhiMTN4aU01RzE3TmlpTmtrblh3OUVGNmxIZ0xaMWZtd1JRTHA3MWxzMzVnSVFBQUFBJCQAAAAAAAAAAAEAAAAM0VGpu6i2vLr-y7W7sAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGUmV2BlJldgcU; __yjs_duid=1_abc5f1395156f6d3c2a96ec0e4d5d37e1620199550546; BD_UPN=13314752; COOKIE_SESSION=443_0_2_2_10_1_0_0_2_1_0_0_441_0_6_0_1625299760_0_1625299754%7C9%23868708_76_1621311132%7C9; BD_HOME=1; H_PS_PSSID=33763_34222_31254_34004_34135_26350_22158; sugstore=1; BA_HECTOR=a0850g240125218kvo1geacn10r\n";
    request_header += "Upgrade-Insecure-Requests: 1\n";
    request_header += "Cache-Control: max-age=0\n";

    //发送请求包头
    res = -10;
    while(res != request_header.size())
    {
        res = send(lfd, request_header.c_str(), request_header.size(), 0);
        if(res == -1)
        {
            std::cout << "发送失败! 即将重新发送！" << std::endl;
        }
        else if (res < request_header.size())
        {
            std::cout << "发送不完整！即将重新发送！" << std::endl;
        }
        else{
            std::cout << "发送成功！" << std::endl;
            break;
        }
    }

    //循环接收服务端返回的网页源码
    std::string html_source_page = "";
    char buf[BUFFSIZE];
    int recv_res = 1;
    while((recv_res = recv(lfd, &buf, BUFFSIZE, 0)) != -1)
    {
        if(recv_res > 0){
            html_source_page += buf;
            std::cout << "接收成功！" << std::endl;
            continue;
        }
        else if(recv_res == 0)
        {
            std::cout << "连接断开！" << std::endl;
            break;
        }
    }
    close(lfd);
    return html_source_page;
}
