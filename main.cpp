#include <iostream>
#include <iomanip> 
#ifdef _WIN32
#include <windows.h> // SetConsoleOutputCP / SetConsoleCP，解决控制台中文乱码
#endif
#include "QuestionBank.h"

using namespace std;

// 主菜单
void showMenu()
{
    cout << "\n========= 简单几何图形题库系统（三角形） =========" << endl;
    cout << "  1. 查看题库全部题目" << endl;
    cout << "  2. 向题库增加题目" << endl;
    cout << "  3. 删除题库中的题目" << endl;
    cout << "  4. 查询指定题目" << endl;
    cout << "  5. 判断三角形类型（输入三边，输出周长、面积、类型）" << endl;
    cout << "  6. 开始练习（逐题作答并判分）" << endl;
    cout << "  7. 查看成绩与平均分" << endl;
    cout << "  0. 退出系统" << endl;
    cout << "===============================================" << endl;
    cout << "请选择菜单项：";
}

int main()
{
#ifdef _WIN32
    // 将控制台代码页切换为 UTF-8，确保程序输出的中文正常显示（修复乱码）
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // 生成题库对象
    QuestionBank bank("三角形几何题库");

    // 预置示例题目（题目对象存入题库对象数组 —— 组合关系）
    bank.add(3, 4, 5);    // 直角三角形
    bank.add(5, 5, 5);    // 等边三角形
    bank.add(6, 8, 10);   // 直角三角形
    bank.add(3, 3, 4);    // 等腰三角形
    bank.add(2, 2, 3);    // 等腰三角形

    // 依赖关系演示：单独构造题目对象，以对象引用传入 add()
    TriangleQuestion t(100, 7, 24, 25); // 直角三角形
    bank.add(t);

    // 不能构成三角形的三边会被拒绝
    cout << "\n[演示] 尝试添加不能构成三角形的边长 1、2、3：" << endl;
    bank.add(1, 2, 3);

    int choice = -1;
    while (true)
    {
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            bank.showAll(); // 输出全部题目
            break;
        case 2:
        {
            double a, b, c;
            cout << "请输入三条边长 a b c（空格分隔）：";
            cin >> a >> b >> c;
            bank.add(a, b, c); // 加题（自动编号）
            break;
        }
        case 3:
        {
            int id;
            cout << "请输入要删除的题目编号：";
            cin >> id;
            bank.del(id); // 删题
            break;
        }
        case 4:
        {
            // 依赖关系演示：查询返回对象指针，通过指针访问对象成员
            int id;
            cout << "请输入要查询的题目编号：";
            cin >> id;
            TriangleQuestion* p = bank.find(id);
            if (p != nullptr)
            {
                p->show();
                p->showAns();
            }
            else
            {
                cout << "未找到：没有编号为 " << id << " 的题目。" << endl;
            }
            break;
        }
        case 5:
        {
            // 实验一要求：判断三角形类型（同时输出周长、面积）
            double a, b, c;
            cout << "请输入三条边长 a b c（空格分隔）：";
            cin >> a >> b >> c;
            if (TriangleQuestion::isTri(a, b, c))
            {
                TriangleQuestion q(0, a, b, c); // 构造临时题目对象进行判断
                cout << fixed << setprecision(2);
                cout << "这三条边能构成" << q.type() << endl;
                cout << "周长 = " << q.perimeter() << "，面积 = " << q.area() << endl;
            }
            else
            {
                cout << "这三条边不能构成三角形。" << endl;
            }
            break;
        }
        case 6:
            bank.practice(); // 练习：录入答案、判分
            break;
        case 7:
            bank.showScore(); // 查看成绩与平均分
            break;
        case 0:
            cout << "感谢使用，再见！" << endl;
            return 0;
        default:
            cout << "输入无效，请重新选择（0-7）。" << endl;
            break;
        }
    }
    return 0;
}
