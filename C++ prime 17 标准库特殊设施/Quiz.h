//
// Created by 123456 on 2021/6/10.
// 功能介绍 : 使用一个bitset保存和修改一个学生一次考试每题的解答情况的模板类
//

#ifndef C_PRIME_17_标准库特殊设施_QUIZ_H
#define C_PRIME_17_标准库特殊设施_QUIZ_H

#include <iostream>
#include <bitset>
#include <utility>

template <std::size_t> class Quiz;

template<std::size_t M>
std::size_t grade(Quiz<M> const& cur, Quiz<M> const& correct);

template<std::size_t M>
std::ostream& operator<<(std::ostream& os, Quiz<M> const& cur);

template <std::size_t N>
class Quiz
{
public:
    Quiz() = default;
    Quiz(const std::string &s) : grade_bitarray(s) { }

    /* 计算成绩 */
    template<std::size_t M>
    friend std::size_t grade(Quiz<M> const& cur, Quiz<M> const& correct);

    /* 声明为友元的输出运算符 */
    template<std::size_t M>
    friend std::ostream& operator<<(std::ostream& os, Quiz<M> const& cur);

    /* 更新成绩 */
    void update_grade(std::pair<std::size_t, bool> &p);
private:
    std::bitset<N> grade_bitarray;
};

template<std::size_t M>
std::size_t grade(Quiz<M> const& cur, Quiz<M> const& correct)
{
    auto result = cur.grade_bitarray ^ correct.grade_bitarray;
    result.flip();
    return result.count();
}

template<std::size_t M>
std::ostream& operator<<(std::ostream& os, Quiz<M> const& cur)
{
    os << cur.grade_bitarray;
}

template<std::size_t N>
void Quiz<N>::update_grade(std::pair<std::size_t, bool> &p) {
    grade_bitarray.set(p.first, p.second);
}

#endif //C_PRIME_17_标准库特殊设施_QUIZ_H
