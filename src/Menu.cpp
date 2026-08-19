#include "Menu.h"

#include <iomanip>
#include <iostream>
#include <limits>

// 功能：构造函数，加载已有数据
Menu::Menu() {
    int count = manager_.loadFromFile();
    if (count > 0) {
        std::cout << "Loaded " << count << " students from file.dat" << std::endl;
    } else {
        std::cout << "No students loaded from file.dat" << std::endl;
    }
}

// 功能：运行主循环（显示菜单并响应用户选择）
//菜单交互
void Menu::run() {
    while (true) {
        showMenu();
        int choice;
        std::cin >> choice;

        // 输入非数字时避免死循环
        if (std::cin.fail()) {
            std::cout << "无效的选择，请重新输入。\n\n";
            clearInput();
            continue;
        }
        switch (choice) {
            case 1: handleAdd(); break;
            case 2: handleDisplay(); break;
            case 3: handleSearch(); break;
            case 4: handleSort(); break;
            case 5: handleDelete(); break;
            case 6: handleModify(); break;
            case 0:
                std::cout << "再见！\n";
                return;
            default:
                std::cout << "无效的选择，请重新输入。\n\n";
        }
    }
}

// 功能：显示主菜单选项
void Menu::showMenu() const {
    std::cout << "===== 学生管理系统 =====\n";
    std::cout << "1. 添加学生\n";
    std::cout << "2. 查看所有学生\n";
    std::cout << "3. 搜索学生\n";
    std::cout << "4. 排序学生\n";
    std::cout << "5. 删除学生\n";
    std::cout << "6. 修改学生\n";
    std::cout << "0. 退出\n";
    std::cout << "请输入选择：";
}

// 功能：清空输入缓冲区的错误状态，防止非法输入导致死循环
void Menu::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Menu::readAge() {
    int age;
    while (true) {
        std::cout << "请输入年龄 (0-150)：";
        std::cin >> age;
        if (std::cin.fail()) {
            std::cout << "输入无效，请输入一个整数！\n";
            clearInput();
            continue;
        }
        if (age >= 0 && age <= 150) return age;
        std::cout << "年龄不合法（必须在 0-150 之间），请重新输入！\n";
    }
}

// 功能：交互读取成绩（必须是数字）
float Menu::readScore() {
    float score;
    while (true) {
        std::cout << "请输入成绩：";
        std::cin >> score;
        if (std::cin.fail()) {
            std::cout << "输入无效，请输入一个数字分数！\n";
            clearInput();
            continue;
        }
        return score;
    }
}

// 功能：以表格形式打印所有学生
void Menu::printAll() const {
    if (manager_.size() == 0) {
        std::cout << "没有学生信息\n\n";
        return;
    }
    std::cout << "--------------------------------------------------\n";
    std::cout << std::left
              << std::setw(15) << "ID"
              << std::setw(15) << "姓名"
              << std::setw(15) << "年龄"
              << std::setw(15) << "成绩" << std::endl;
    std::cout << "--------------------------------------------------\n";
    for (std::size_t i = 0; i < manager_.size(); ++i) {
        manager_.getStudent(i).display();
    }
    std::cout << "--------------------------------------------------\n\n";
}

// 功能：处理"添加学生"交互
void Menu::handleAdd() {
    std::string id, name;
    std::cout << "请输入学号：";
    std::cin >> id;
    if (manager_.hasId(id)) {
        std::cout << "学号重复，添加失败！\n\n";
        return;
    }
    std::cout << "请输入姓名：";
    std::cin >> name;
    int age = readAge();
    float score = readScore();

    manager_.addStudent(Student(id, name, age, score));
    if (manager_.saveToFile()) {
        std::cout << "添加成功！\n\n";
    } else {
        std::cout << "文件保存失败！\n\n";
    }
}

// 功能：处理"查看所有学生"交互
void Menu::handleDisplay() const {
    printAll();
}

// 功能：处理"搜索学生"交互
void Menu::handleSearch() const {
    std::string keyword;
    std::cout << "请输入要搜索的学生信息：";
    std::cin >> keyword;

    std::vector<int> indexes = manager_.searchIndexes(keyword);
    if (indexes.empty()) {
        std::cout << "没有找到匹配的学生信息。\n\n";
        return;
    }
    for (int i : indexes) {
        manager_.getStudent(i).display();
    }
    std::cout << "\n";
}

// 功能：处理"排序学生"交互
void Menu::handleSort() {
    int incriterion, inorder;
    std::cout << "请选择排序依据 (0: 年龄, 1: 成绩)：";
    std::cin >> incriterion;
    std::cout << "请选择排序方式 (0: 升序, 1: 降序)：";
    std::cin >> inorder;
    SortBy criterion = static_cast<SortBy>(incriterion);
    SortOrder order = static_cast<SortOrder>(inorder);
    if (manager_.sortStudents(criterion, order)) {
        std::cout << "排序成功！\n\n";
    } else {
        std::cout << "排序失败！\n\n";
    }
}

// 功能：处理"删除学生"交互
void Menu::handleDelete() {
    if (manager_.size() == 0) {
        std::cout << "当前没有学生信息！\n\n";
        return;
    }

    std::string keyword;
    std::cout << "请输入要删除的学生姓名或学号：";
    std::cin >> keyword;

    int index = manager_.findIndex(keyword);
    if (index == -1) {
        std::cout << "未找到该学生。\n\n";
        return;
    }

    std::cout << "找到该学生，信息如下，请确认\n";
    manager_.getStudent(index).display();
    std::cout << "确认删除请输入1，否则输入0：";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        manager_.deleteStudent(index);
        if (manager_.saveToFile()) {
            std::cout << "删除成功！\n\n";
        } else {
            std::cout << "文件保存失败！\n\n";
        }
    } else {
        std::cout << "已取消。\n\n";
    }
}

// 功能：处理"修改学生"交互
void Menu::handleModify() {
    if (manager_.size() == 0) {
        std::cout << "当前没有学生信息！\n\n";
        return;
    }

    std::string keyword;
    std::cout << "请输入要修改的学生姓名或学号：";
    std::cin >> keyword;

    int index = manager_.findIndex(keyword);
    if (index == -1) {
        std::cout << "未找到该学生。\n\n";
        return;
    }

    std::cout << "找到该学生，信息如下，请确认\n";
    manager_.getStudent(index).display();
    std::cout << "确认修改该学生信息吗？(1: 确认, 0: 取消)：";
    int choice;
    std::cin >> choice;
    if (choice != 1) {
        std::cout << "已取消修改。\n\n";
        return;
    }

    std::string id, name;
    int age;
    float score;
    std::cout << "请输入新的学生信息 (id, name, age, score)：";
    std::cin >> id >> name >> age >> score;

    manager_.updateStudent(index, Student(id, name, age, score));
    if (manager_.saveToFile()) {
        std::cout << "修改成功！\n\n";
    } else {
        std::cout << "文件保存失败！\n\n";
    }
}