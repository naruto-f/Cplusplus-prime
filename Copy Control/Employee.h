//
// Created by 123456 on 2021/5/5.
//

#ifndef COPY_CONTROL_EMPLOYEE_H
#define COPY_CONTROL_EMPLOYEE_H

#include <iostream>
#include <string>


class Employee {
public:
    Employee(std::string &name) : Eee_name(name), number(q++) { }
    Employee(const Employee &emp) : Eee_name(emp.Eee_name), number(q++) { }
    Employee &operator=(Employee &);
    void show_num();
private:
    static int q;
    std::string Eee_name;
    int number;
};


#endif //COPY_CONTROL_EMPLOYEE_H
