#include "QuestionBank.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 默认构造：名称与成绩数据均初始化为确定值
QuestionBank::QuestionBank()
    : m_name("未命名题库"), m_ans(0), m_ok(0), m_avg(0.0)
{
}

// 重载构造：指定题库名称
QuestionBank::QuestionBank(const string& name)
    : m_name(name), m_ans(0), m_ok(0), m_avg(0.0)
{
}

void   QuestionBank::setName(const string& name) { m_name = name; }
string QuestionBank::getName() const { return m_name; }
int    QuestionBank::getNum()  const { return (int)m_qs.size(); } // vector 动态长度
int    QuestionBank::getAns()  const { return m_ans; }
int    QuestionBank::getOk()   const { return m_ok; }
double QuestionBank::getAvg()  const { return m_avg; }

// 内部工具：生成不重复题号
int QuestionBank::nextId() const
{
    int max = 0;
    for (int i = 0; i < (int)m_qs.size(); ++i)
    {
        if (m_qs[i].getId() > max)
        {
            max = m_qs[i].getId();
        }
    }
    return max + 1;
}

// 加题：参数为 TriangleQuestion 对象引用 —— 依赖关系（use-a）
// 题目对象被存入题库的 vector 容器成员 —— 组合关系（has-a）
bool QuestionBank::add(const TriangleQuestion& q)
{
    if (!q.isOk())
    {
        cout << "错误：该题三边不能构成三角形，拒绝加入。" << endl;
        return false;
    }
    m_qs.push_back(q); // STL vector：动态追加题目对象（组合成员）
    cout << "成功：题目已加入题库《" << m_name << "》，当前共 "
         << m_qs.size() << " 题。" << endl;
    return true;
}

// 按三边加题：先验证合法性，再自动编号构造题目对象并入库
bool QuestionBank::add(double a, double b, double c)
{
    if (!TriangleQuestion::isTri(a, b, c))
    {
        cout << "错误：边长 " << a << "、" << b << "、" << c
             << " 不能构成三角形，添加失败。" << endl;
        return false;
    }
    TriangleQuestion q(nextId(), a, b, c);
    return add(q); // 复用上面的重载版本（依赖关系调用）
}

// 删题：找到编号为 id 的题目，用 vector 迭代器删除
bool QuestionBank::del(int id)
{
    for (vector<TriangleQuestion>::iterator it = m_qs.begin(); it != m_qs.end(); ++it)
    {
        if (it->getId() == id)
        {
            m_qs.erase(it); // STL vector：erase 删除指定元素并自动前移
            cout << "成功：第 " << id << " 题已删除。" << endl;
            return true;
        }
    }
    cout << "未找到：没有编号为 " << id << " 的题目。" << endl;
    return false;
}

// 查题：返回对象指针 —— 依赖关系（use-a）
TriangleQuestion* QuestionBank::find(int id)
{
    for (int i = 0; i < (int)m_qs.size(); ++i)
    {
        if (m_qs[i].getId() == id)
        {
            return &m_qs[i];
        }
    }
    return nullptr;
}

// 输出指定题
void QuestionBank::showOne(int id) const
{
    for (int i = 0; i < (int)m_qs.size(); ++i)
    {
        if (m_qs[i].getId() == id)
        {
            m_qs[i].show();
            return;
        }
    }
    cout << "未找到：没有编号为 " << id << " 的题目。" << endl;
}

// 输出全部题目
void QuestionBank::showAll() const
{
    cout << "========== 题库《" << m_name << "》 ==========" << endl;
    cout << "题目数量：" << m_qs.size() << endl;
    if (m_qs.empty())
    {
        cout << "（题库为空）" << endl;
        return;
    }
    for (int i = 0; i < (int)m_qs.size(); ++i)
    {
        m_qs[i].show();
    }
    cout << "============================================" << endl;
}

// 练习：逐题显示题目、录入用户答案、判分并累计成绩与平均分
void QuestionBank::practice()
{
    if (m_qs.empty())
    {
        cout << "提示：题库为空，请先加题再练习。" << endl;
        return;
    }
    cout << "========== 开始练习 ==========" << endl;
    for (int i = 0; i < (int)m_qs.size(); ++i)
    {
        m_qs[i].show();

        // 先让用户判断三角形类型（题目不直接显示类型）
        int t = 0;
        cout << "    请判断该三角形属于什么类型（输入数字）：" << endl;
        cout << "      1. 等边三角形    2. 等腰三角形    3. 等腰直角三角形" << endl;
        cout << "      4. 直角三角形    5. 一般三角形" << endl;
        cout << "    请输入你的判断：";
        cin >> t;
        m_qs[i].setType(t); // 录入用户判断的类型

        double p = 0.0, s = 0.0;
        cout << "请输入你计算的周长：";
        cin >> p;
        cout << "请输入你计算的面积：";
        cin >> s;

        m_qs[i].setAns(p, s); // 录入用户答案
        m_ans++;

        if (m_qs[i].check())
        {
            m_ok++;
            cout << ">>> 第 " << m_qs[i].getId() << " 题回答正确！" << endl;
        }
        else
        {
            cout << ">>> 第 " << m_qs[i].getId() << " 题回答错误。" << endl;
        }
        m_qs[i].showAns();
        cout << "----------------------------------------" << endl;
    }
    // 更新平均分（正确率，百分制）
    m_avg = (m_ans == 0) ? 0.0 : (double)m_ok / m_ans * 100.0;
    cout << "本次练习结束，共完成 " << m_qs.size() << " 道题。" << endl;
}

// 输出成绩与平均分
void QuestionBank::showScore() const
{
    cout << "========== 成绩统计 ==========" << endl;
    cout << "题库名称：" << m_name << endl;
    cout << "已做题目数：" << m_ans << " 题" << endl;
    cout << "答对题目数：" << m_ok << " 题（成绩）" << endl;
    cout << "平均分（正确率）：" << fixed << setprecision(2) << m_avg << " 分" << endl;
    cout << "==============================" << endl;
}

// 清空成绩
void QuestionBank::clearScore()
{
    m_ans = 0;
    m_ok = 0;
    m_avg = 0.0;
    cout << "成功：成绩记录已清空。" << endl;
}
