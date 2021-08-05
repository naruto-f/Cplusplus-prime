//
// Created by 123456 on 2021/6/11.
// 函数功能 : 统计指定文件中每一行的偏移量，注意每一行的不可见的换行符也算一个偏移字符
//

#include "line_offset_count.h"

int count()
{
    std::fstream inOut("test.txt", std::fstream::in | std::fstream::out | std::fstream::ate);
    if(!inOut) {
        std::cout << "Unable to open file !" << std::endl;
        return EXIT_FAILURE;
    }

    auto end_mark = inOut.tellp();
    inOut.seekg(0, std::fstream::beg);

    std::size_t cnt = 0;   /* 记录到当前读取行的偏移量 */
    string line;   /* 保存每一行 */

    while (inOut && inOut.tellg() != end_mark && getline(inOut, line))
    {
        cnt += line.size() + 1;
        auto mark = inOut.tellg();
        inOut.seekp(0, std::fstream::end);
        inOut << cnt;
        if(mark != end_mark)
        {
            inOut << " ";
        }
        inOut.seekg(mark);
    }
    inOut.seekp(0, std::fstream::end);
    inOut << "\n";
    return 0;
}


