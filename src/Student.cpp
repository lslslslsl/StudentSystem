#include "Student.h"

#include <iomanip>

Student::Student() : id_(), name_(), age_(0), score_(0.0f) {}
Student::Student(const std::string& id, const std::string& name, int age, float score)
    : id_(id), name_(name), age_(age), score_(score) {}

// 功能：获取学号
const std::string& Student::getId() const { return id_; }
// 功能：获取姓名
const std::string& Student::getName() const { return name_; }
// 功能：获取年龄
int Student::getAge() const { return age_; }
// 功能：获取成绩
float Student::getScore() const { return score_; }

// 功能：设置学号
void Student::setId(const std::string& id) { id_ = id; }
// 功能：设置姓名
void Student::setName(const std::string& name) { name_ = name; }
// 功能：设置年龄
void Student::setAge(int age) { age_ = age; }
// 功能：设置成绩
void Student::setScore(float score) { score_ = score; }

// 功能：判断当前学生是否匹配关键字（学号或姓名包含该关键字）
bool Student::matches(const std::string& keyword) const {
    return id_.find(keyword) != std::string::npos 
        || name_.find(keyword) != std::string::npos;
}

// 功能：以一行表格的格式显示当前学生的信息
void Student::display() const {
    std::cout << std::left << std::setw(15) << id_
              << std::setw(15) << name_
              << std::setw(15) << age_
              << std::setw(15) << score_ << std::endl;
}