#pragma once

#include <iostream>
#include <string>

// 学生类：封装单个学生的数据和行为
class Student {
private:
    std::string id_;   // 学号
    std::string name_; // 姓名
    int age_;          // 年龄
    float score_;      // 成绩

public:
    // 功能：默认构造一个学生对象（学号、姓名为空，年龄、成绩为 0）
    Student();
    // 功能：根据学号、姓名、年龄、成绩构造学生对象
    Student(const std::string& id, const std::string& name, int age, float score);

    // 功能：获取学号
    const std::string& getId() const;
    // 功能：获取姓名
    const std::string& getName() const;
    // 功能：获取年龄
    int getAge() const;
    // 功能：获取成绩
    float getScore() const;

    // 功能：设置学号
    void setId(const std::string& id);
    // 功能：设置姓名
    void setName(const std::string& name);
    // 功能：设置年龄
    void setAge(int age);
    // 功能：设置成绩
    void setScore(float score);

    // 功能：判断当前学生是否匹配关键字（学号或姓名包含该关键字）
    bool matches(const std::string& keyword) const;

    // 功能：以一行表格的格式显示当前学生的信息
    void display() const;
};