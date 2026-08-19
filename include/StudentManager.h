#pragma once

#include <string>
#include <vector>

#include "Student.h"

// 排序依据与排序方式（枚举类，避免魔法数字）
enum class SortBy { Age, Score };
enum class SortOrder { Ascending, Descending };

// 学生管理类：负责学生集合的增删改查、排序与文件读写
// 内部使用 new / delete 动态管理学生数组，并遵守"三法则"
// （析构函数 + 拷贝构造函数 + 赋值运算符），避免内存泄漏和浅拷贝问题。
class StudentManager {
private:
    std::vector<Student> students_;

public:
    // 功能：构造函数，初始化为空（无学生、不分配内存）
    StudentManager();

    // 功能：从 students.dat 文件加载学生数据，返回加载条数；文件不存在返回 -1
    int loadFromFile();
    // 功能：将学生数据保存到 students.dat 文件，成功返回 true
    bool saveToFile() const;

    // 功能：判断是否存在指定学号的学生
    bool hasId(const std::string& id) const;
    // 功能：按关键字查找第一个匹配学生的索引，未找到返回 -1
    int findIndex(const std::string& keyword) const;
    // 功能：返回所有匹配关键字的学生索引
    std::vector<int> searchIndexes(const std::string& keyword) const;

    // 功能：添加一名学生，学号重复返回 false
    bool addStudent(const Student& s);
    // 功能：按索引删除一名学生（索引有效性由调用方保证）
    bool deleteStudent(int index);
    // 功能：按索引修改一名学生
    void updateStudent(int index, const Student& student);
    // 功能：按指定依据（年龄/成绩）和方式（升序/降序）对学生排序
    bool sortStudents(SortBy by, SortOrder order);

    // 功能：获取学生个数
    std::size_t size() const;
    // 功能：按索引获取学生（索引有效性由调用方保证）
    const Student& getStudent(int index) const;
};