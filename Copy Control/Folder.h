//
// Created by 123456 on 2021/5/8.
//

#ifndef COPY_CONTROL_FOLDER_H
#define COPY_CONTROL_FOLDER_H

#include "Message.h"

//电子邮件的消息目录
class Message;
class Folder {
    //friend class Message;
public:
    Folder()=default;
    void remMsg(Message *);
    void addMsg(Message *);
    void showMsg();
private:
    std::set<Message*> MsgFolder;
};



#endif //COPY_CONTROL_FOLDER_H
