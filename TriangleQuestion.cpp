#include "TriangleQuestion.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 默认构造：初始化数据成员为确定的值（3、4、5 为合法三角形）
TriangleQuestion::TriangleQuestion()
    : m_id(0), m_a(3), m_b(4), m_c(5), m_ok(true),
      m_p(0), m_s(0), m_up(0), m_us(0), m_utype(0), m_done(false)
{
    calc(); // 对象创建后自动计算正确答案
}

// 重载构造：按指定参数构造对象，并做合法性验证
TriangleQuestion::TriangleQuestion(int id, double a, double b, double c)
    : m_id(id), m_a(a), m_b(b), m_c(c), m_ok(isTri(a, b, c)),
      m_p(0), m_s(0), m_up(0), m_us(0), m_utype(0), m_done(false)
{
    if (!m_ok)
    {
        cout << "提示：边长 " << a << "、" << b << "、" << c
             << " 不能构成三角形，本题标记为无效。" << endl;
    }
    calc();
}

// 合法性验证：边长大于 0 且任意两边之和大于第三边
bool TriangleQuestion::isTri(double a, double b, double c)
{
    return (a > 0 && b > 0 && c > 0) &&
           (a + b > c) && (a + c > b) && (b + c > a);
}

void TriangleQuestion::setId(int id)
{
    m_id = id;
}

// 修改边长：先验证合法性，验证通过才修改，并重新计算正确答案
bool TriangleQuestion::setSide(double a, double b, double c)
{
    if (!isTri(a, b, c))
    {
        cout << "错误：边长 " << a << "、" << b << "、" << c
             << " 不能构成三角形，修改失败。" << endl;
        return false;
    }
    m_a = a;
    m_b = b;
    m_c = c;
    m_ok = true;
    calc();
    return true;
}

// 录入用户答案（周长、面积）
void TriangleQuestion::setAns(double p, double s)
{
    m_up = p;
    m_us = s;
    m_done = true;
}

// 录入用户判断的三角形类型（编号 1-5）
void TriangleQuestion::setType(int t)
{
    if (t >= 1 && t <= 5)
    {
        m_utype = t;
    }
}

int    TriangleQuestion::getId()   const { return m_id; }
double TriangleQuestion::getA()    const { return m_a; }
double TriangleQuestion::getB()    const { return m_b; }
double TriangleQuestion::getC()    const { return m_c; }
bool   TriangleQuestion::isOk()    const { return m_ok; }
bool   TriangleQuestion::isDone()  const { return m_done; }

// 求周长
double TriangleQuestion::perimeter() const
{
    return m_ok ? (m_a + m_b + m_c) : 0.0;
}

// 求面积：海伦公式
double TriangleQuestion::area() const
{
    if (!m_ok)
    {
        return 0.0;
    }
    double s = (m_a + m_b + m_c) / 2.0;
    return sqrt(s * (s - m_a) * (s - m_b) * (s - m_c));
}

// 判断类型：等边 / 等腰直角 / 等腰 / 直角 / 一般
string TriangleQuestion::type() const
{
    if (!m_ok)
    {
        return "（边长不合法）";
    }
    const double eps = 1e-6;
    bool eq  = (fabs(m_a - m_b) < eps) && (fabs(m_b - m_c) < eps);
    bool iso = eq || (fabs(m_a - m_b) < eps) ||
               (fabs(m_a - m_c) < eps) || (fabs(m_b - m_c) < eps);

    // 找最长边，用勾股定理判断是否直角
    double mx = m_a, o1 = m_b, o2 = m_c;
    if (m_b > mx) { mx = m_b; o1 = m_a; o2 = m_c; }
    if (m_c > mx) { mx = m_c; o1 = m_a; o2 = m_b; }
    bool rt = fabs(mx * mx - (o1 * o1 + o2 * o2)) < eps;

    if (eq)        return "等边三角形";
    if (iso && rt) return "等腰直角三角形";
    if (iso)       return "等腰三角形";
    if (rt)        return "直角三角形";
    return "一般三角形";
}

// 判断类型编号：1等边 2等腰 3等腰直角 4直角 5一般
int TriangleQuestion::typeId() const
{
    const string t = type();
    if (t == "等边三角形")     return 1;
    if (t == "等腰三角形")     return 2;
    if (t == "等腰直角三角形") return 3;
    if (t == "直角三角形")     return 4;
    return 5; // 一般三角形
}

// 类型编号转名称
const char* TriangleQuestion::typeName(int id)
{
    switch (id)
    {
    case 1: return "等边三角形";
    case 2: return "等腰三角形";
    case 3: return "等腰直角三角形";
    case 4: return "直角三角形";
    case 5: return "一般三角形";
    default: return "未判断";
    }
}

// 计算并保存正确答案
void TriangleQuestion::calc()
{
    m_p = perimeter();
    m_s = area();
}

// 判分：类型、周长、面积三项都与正确答案一致（周长面积允许 1% 相对误差）才判对
bool TriangleQuestion::check() const
{
    if (!m_done || !m_ok)
    {
        return false;
    }
    bool okT = (m_utype == typeId());
    bool okP = fabs(m_up - m_p) <= m_p * 0.01;
    bool okS = fabs(m_us - m_s) <= m_s * 0.01;
    return okT && okP && okS;
}

// 输出题目（不含答案与类型，供学生作答）
void TriangleQuestion::show() const
{
    cout << "第 " << m_id << " 题：三边长 "
         << fixed << setprecision(2)
         << m_a << "、" << m_b << "、" << m_c << endl;
    cout << "    请判断该三角形的类型，并计算其周长与面积。" << endl;
}

// 输出正确答案与用户答案（类型、周长、面积）
void TriangleQuestion::showAns() const
{
    cout << "    正确答案：" << type() << "，周长 = " << fixed << setprecision(2)
         << m_p << "，面积 = " << m_s << endl;
    if (m_done)
    {
        cout << "    你的答案：" << typeName(m_utype)
             << "，周长 = " << m_up
             << "，面积 = " << m_us
             << "（" << (check() ? "回答正确" : "回答错误") << "）" << endl;
    }
}
