//
// Created by 123456 on 2021/5/7.
//

#ifndef COPY_CONTROL_MESSAGE_H
#define COPY_CONTROL_MESSAGE_H

#include <iostream>
#include <set>
#include "Folder.h"

//电子邮件的消息类
class Folder;
class Message {
    //friend class Folder;
    friend void swap(Message &, Message &);   //自定义swap的好处就是减少不必要额拷贝，节约开销
public:
    explicit Message(const std::string &s = "") : content(s) { }  //使用explicit防止隐式转换
    Message(const Message&);   //拷贝构造函数
    Message& operator=(const Message &);  //拷贝赋值运算符
    ~Message();

    //从指定Folder集合中添加/删除本Message
    void save(Folder &);
    void remove(Folder &);
    std::string getMsg();
private:
    std::string content;   //实际消息文本
    std::set<Folder*> folders;   //包含本Message的

    //将本Message添加到指向参数m的Folder中
    void add_to_Folders(const Message&m);

    //从folders的每个Folder中删除本Message
    void remove_from_Folders();
    void addFol(Folder *);
    void remFol(Folder *);
};


#endif //COPY_CONTROL_MESSAGE_H
