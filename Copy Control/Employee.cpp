//
// Created by 123456 on 2021/5/5.
//

#include "Employee.h"

/*
Employee::Employee(std::string &name) : Eee_name(name)
{
    number = q++;
}
 */
int Employee::q = 1;

void Employee::show_num()
{
    std::cout << Eee_name << "的编号是：" << number << std::endl;
}

Employee &Employee::operator=(Employee &e)
{
    Eee_name = e.Eee_name;
    number = e.number;
}