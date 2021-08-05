//
// Created by 123456 on 2021/6/21.
//

#ifndef C___PRIME_19_CHAPTER_TOKEN_H
#define C___PRIME_19_CHAPTER_TOKEN_H


#include <iostream>

using namespace std;

class Token {
public:
    /* 自定义的默认构造函数 */
    Token() : tok(INT), ival(0) { }

    /* 拷贝构造函数*/
    Token(const Token &t) : tok(t.tok) { CopyUnion(t); }

    /* 拷贝赋值运算符 */
    Token& operator=(const Token &t);

    /* 移动构造函数 */
    Token(Token &&t) noexcept : tok(t.tok)
    {
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
    }

    /* 移动赋值运算符 */
    Token& operator=(Token &&t);

    /* 析构函数 */
    ~Token()
    {
        if(tok == STR)   //只有union中存放的是string类型的数据时才需要手动析构
        {
            sval.basic_string::~basic_string();
        }
    }

    /* 下面的赋值运算符负责设置union的不同成员 */
    Token& operator=(int i);

    Token& operator=(char c);

    Token& operator=(double b);

    Token& operator=(const std::string &s);

    /* 打印union中当前存储的值 */
    void print_cur();

private:
    /* 存放union中哪种类型的判别式 */
    enum {INT, CHAR, DBL, STR} tok;

    /* 匿名union */
    union {
        int ival;
        char cval;
        double dval;
        std::string sval;
    };

    /* 检查判别式，酌情拷贝union成员 */
    void CopyUnion(const Token &t);
};



#endif //C___PRIME_19_CHAPTER_TOKEN_H
