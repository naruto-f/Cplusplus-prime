//
// Created by 123456 on 2021/6/21.
//

#include "Token.h"

Token &Token::operator=(int i) {
    if(tok == STR)
    {
        sval.basic_string::~basic_string();
    }
    tok = INT;
    ival = i;
    return *this;
}

Token &Token::operator=(char c) {
    if(tok == STR)
    {
        sval.basic_string::~basic_string();
    }
    tok = CHAR;
    cval = c;
    return *this;
}

Token &Token::operator=(double b) {
    if(tok == STR)
    {
        sval.basic_string::~basic_string();
    }
    tok = DBL;
    dval = b;
    return *this;
}

Token &Token::operator=(const string &s) {
    if(tok == STR)   /* 如果存储的是string， 可以直接赋值 */
    {
        sval = s;
    }
    else{
        new(&sval) string(s);
    }
    tok = STR;
    return *this;
}

void Token::CopyUnion(const Token &t) {
    switch (t.tok) {
        case Token::INT :
            ival = t.ival;
            break;
        case Token::CHAR :
            cval = t.cval;
            break;
        case Token::DBL :
            dval = t.dval;
            break;
        case Token::STR :
            new(&sval) string(t.sval);
            break;
    }
}

Token &Token::operator=(const Token &t) {
    /* 如果左侧存放的是string, 右侧不是，则释放string的空间 */
    if(tok == STR && t.tok != STR)
    {
        sval.std::string::~string();
    }

    /* 如果两侧存放的都是string, 则可以直接赋值 无须构造一个新的string */
    if(tok == STR && t.tok == STR)
    {
        sval = t.sval;
    }
    else{
        CopyUnion(t);
    }
    tok = t.tok;
    return *this;
}

Token &Token::operator=(Token &&t) {
    switch (t.tok) {
        case Token::INT :
            ival = t.ival;
            break;
        case Token::CHAR :
            cval = t.cval;
            break;
        case Token::DBL :
            dval = t.dval;
            break;
        case Token::STR :
            sval = std::move(t.sval);
            break;
    }
    tok = t.tok;
    return *this;
}

void Token::print_cur() {
    switch (tok) {
        case Token::INT :
            cout << ival << endl;
            break;
        case Token::CHAR :
            cout << cval << endl;
            break;
        case Token::DBL :
            cout << dval << endl;
            break;
        case Token::STR :
            cout << sval << endl;
            break;
    }
}
