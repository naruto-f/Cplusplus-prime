//
// Created by 123456 on 2021/5/8.
//

#include "Folder.h"

void Folder::remMsg(Message *m) {
    MsgFolder.erase(m);
}

void Folder::addMsg(Message *m) {
    MsgFolder.insert(m);
}

void Folder::showMsg() {
    int i = 0;
    for(auto f : MsgFolder)
    {
        std::cout << i++ << ". " << (*f).getMsg() << std::endl;
    }
}
