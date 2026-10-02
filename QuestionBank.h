#ifndef QUESTION_BANK_H
#define QUESTION_BANK_H

#include <string>
#include <vector>
#include "TriangleQuestion.h"

/*
 * 题库类（整体类）—— 实验二：组合关系、依赖关系
 * 组合关系：把三角形题目对象容器 std::vector 作为成员（has-a / contains-a）
 * 依赖关系：add(const TriangleQuestion&) 以对象引用为参数、
 *           find() 返回对象指针（use-a）
 * 基本操作：初始化（默认/重载构造）、修改、获取、输出；
 * 其他操作：加题、删题、查题、练习判分、成绩与平均分统计
 *
 * 命名说明：m_name=题库名称；m_qs=题目容器（STL vector，组合成员）；
 *          m_ans=已做题目数；m_ok=答对题目数；m_avg=平均分
 */
class QuestionBank
{
private:
    std::string m_name;                          // 题库名称
    std::vector<TriangleQuestion> m_qs;          // 所有题目（组合：STL vector 对象容器）
    int         m_ans;                           // 已做题目数
    int         m_ok;                            // 答对题目数（成绩）
    double      m_avg;                           // 平均分（正确率，百分制）

    int nextId() const;          // 生成不重复题号

public:
    QuestionBank();                              // 默认构造
    QuestionBank(const std::string& name);       // 重载构造：指定题库名称

    void   setName(const std::string& name);     // 修改题库名称
    std::string getName() const;                 // 获取题库名称
    int    getNum() const;                       // 获取题目数量
    int    getAns() const;                       // 获取已做题目数
    int    getOk() const;                        // 获取答对题目数
    double getAvg() const;                       // 获取平均分
    void   showAll() const;                      // 输出全部题目

    bool add(const TriangleQuestion& q);         // 加题（依赖：对象引用参数）
    bool add(double a, double b, double c);      // 按三边加题（自动编号）
    bool del(int id);                            // 删题
    TriangleQuestion* find(int id);              // 查题（返回对象指针）
    void showOne(int id) const;                  // 输出指定题
    void practice();                             // 练习：逐题作答、判分
    void showScore() const;                      // 输出成绩与平均分
    void clearScore();                           // 清空成绩
};

#endif
