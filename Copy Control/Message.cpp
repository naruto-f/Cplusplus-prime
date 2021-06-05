//
// Created by 123456 on 2021/5/7.
//

#include "Message.h"

void Message::save(Folder &f) {
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f) {
    folders.erase(&f);
    f.remMsg(this);
}


void Message::add_to_Folders(const Message &mes) {
    for(auto f : mes.folders)
    {
        f->addMsg(this);
    }
}

void Message::remove_from_Folders() {
    for(auto f : folders)
    {
        f->remMsg(this);
    }
}

Message::Message(const Message &mes) : content(mes.content), folders(mes.folders) {
    add_to_Folders(mes);   //add_to_Folders(*this);应该也行
}

Message::~Message() {
    //string和set类型的对象在析构函数函数体结束后会由析构函数自动销毁
    remove_from_Folders();
}

Message &Message::operator=(const Message &m) {
    //拷贝赋值运算符通常综合了拷贝构造函数和析构函数的功能
    //为了解决自赋值问题，先将所有指向左侧运算对象的Folder中删除左侧运算对象
    remove_from_Folders();
    content = m.content;
    folders = m.folders;
    add_to_Folders(m);
    return *this;   //别忘了这步！！！ 切记
}

void swap(Message &left, Message &right) {
    //分别对left和right进行两次扫描
    using std::swap;
    for(auto f : left.folders)
    {
        f->remMsg(&left);
    }
    for(auto f : right.folders)
    {
        f->remMsg(&right);
    }
    swap(left.content, right.content);
    swap(left.folders, right.folders);
    for(auto f : left.folders)
    {
        f->addMsg(&left);
    }
    for(auto f : right.folders)
    {
        f->addMsg(&right);
    }
}

std::string Message::getMsg() {
    return content;
}

void Message::remFol(Folder *f) {
    folders.erase(f);
}

void Message::addFol(Folder *f) {
    folders.insert(f);
}



