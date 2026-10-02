#ifndef TRIANGLE_QUESTION_H
#define TRIANGLE_QUESTION_H

#include <string>

/*
 * 三角形题目类（部分类）—— 实验一：类与对象
 * 数据成员：题目编号、三边长、是否合法、正确答案、用户答案等
 * 基本操作：初始化（默认/重载构造）、修改、获取、输出
 * 其他操作：合法性验证、求周长、求面积、判断类型、判分
 *
 * 命名说明：m_ 开头为私有成员；a/b/c 为三边；p=周长、s=面积；
 *          up/us=用户周长/面积；ok=合法；done=已作答
 */
class TriangleQuestion
{
private:
    int    m_id;    // 题目编号
    double m_a;     // 边 a
    double m_b;     // 边 b
    double m_c;     // 边 c
    bool   m_ok;    // 三边是否构成合法三角形
    double m_p;     // 正确答案：周长
    double m_s;     // 正确答案：面积
    double m_up;    // 用户答案：周长
    double m_us;    // 用户答案：面积
    int    m_utype; // 用户答案：三角形类型编号（0=未判断）
    bool   m_done;  // 是否已作答

public:
    TriangleQuestion();                              // 默认构造
    TriangleQuestion(int id, double a, double b, double c); // 重载构造

    static bool isTri(double a, double b, double c); // 合法性验证

    void setId(int id);                             // 修改编号
    bool setSide(double a, double b, double c);      // 修改边长（含验证）
    void setAns(double p, double s);                // 录入用户答案（周长、面积）
    void setType(int t);                            // 录入用户判断的三角形类型

    int    getId() const;                           // 获取编号
    double getA() const;
    double getB() const;
    double getC() const;
    bool   isOk() const;                            // 是否合法
    bool   isDone() const;                          // 是否已作答

    double perimeter() const;   // 求周长
    double area() const;        // 求面积
    std::string type() const;   // 判断类型（返回类型名称）
    int typeId() const;         // 判断类型（返回类型编号 1-5）
    static const char* typeName(int id); // 类型编号转名称
    void calc();                // 计算正确答案
    bool check() const;         // 判分（类型+周长+面积）
    void show() const;          // 输出题目（不含答案与类型）
    void showAns() const;       // 输出答案
};

#endif
