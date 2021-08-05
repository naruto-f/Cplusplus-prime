//
// Created by 123456 on 2021/6/18.
//

#include "Print_GPIO.h"

int print()
{

    int i = 0;
    std::string s1 = "{SW";
    std::string s2 = "_GPIO_Port,SW";
    std::string s3 = "_Pin,0},";
    for(i = 0; i < 101; ++i)
    {
        std::cout << s1 + std::to_string(i) + s2 + std::to_string(i) + s3 << std::endl;
    }


}


