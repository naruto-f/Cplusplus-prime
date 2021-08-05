//
// Created by 123456 on 2021/6/24.
//

#ifndef C___PRIME_19_CHAPTER_ISBN_MISMATCH_H
#define C___PRIME_19_CHAPTER_ISBN_MISMATCH_H

/* 头文件exception定义了最通用的异常类：只是报告异常的发生，而不提供任何其他信息 */
/* 头文件stdexcept还定义了logic_error, runtime_error等异常类, 而且可以提供额外信息 */
#include <stdexcept>

class isbn_mismatch : std::logic_error{
public:
    explicit isbn_mismatch(const std::string &s) : std::logic_error(s) { }
    isbn_mismatch(const std::string &s, const std::string left_isbn, const std::string right_isbn)
    : std::logic_error(s), left(left_isbn), right(right_isbn) { }

    const std::string left, right;
};


#endif //C___PRIME_19_CHAPTER_ISBN_MISMATCH_H
