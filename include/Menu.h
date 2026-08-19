#pragma once

#include "StudentManager.h"

// 菜单与交互类：负责全部界面交互（提示、输入校验、结果输出），
// 具体的业务操作通过调用 StudentManager 完成。
class Menu {
private:
    StudentManager manager_; // 持有学生管理对象

    // 功能：显示主菜单选项
    void showMenu() const;
    // 功能：清空输入缓冲区的错误状态，防止非法输入导致死循环
    void clearInput();
    // 功能：交互读取年龄（必须是 0-150 的整数）
    int readAge();
    // 功能：交互读取成绩（必须是数字）
    float readScore();
    // 功能：以表格形式打印所有学生
    void printAll() const;
    // 功能：处理"添加学生"交互
    void handleAdd();
    // 功能：处理"查看所有学生"交互
    void handleDisplay() const;
    // 功能：处理"搜索学生"交互
    void handleSearch() const;
    // 功能：处理"排序学生"交互
    void handleSort();
    // 功能：处理"删除学生"交互
    void handleDelete();
    // 功能：处理"修改学生"交互
    void handleModify();

public:
    // 功能：构造函数，加载已有数据
    Menu();
    // 功能：运行主循环（显示菜单并响应用户选择）
    void run();
};
