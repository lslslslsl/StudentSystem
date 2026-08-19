#include "StudentManager.h"

#include <algorithm>
#include <fstream>

// 功能：构造函数，初始化为空（无学生、不分配内存）
StudentManager::StudentManager() {}

// 功能：从 students.dat 文件加载学生数据到内存
int StudentManager::loadFromFile() {
    std::ifstream infile("students.dat");
    if (!infile.is_open()) {
        std::cerr << "Error: Failed to open file students.dat" << std::endl;
        return -1;
    }
    // 清空当前学生数据
    students_.clear();
    int count = 0;
    infile >> count;
    for (int i = 0; i < count; ++i) {
        std::string id,name;
        int age;
        float score;
        infile >> id >> name >> age >> score;
        students_.push_back(Student(id,name,age,score));
    }
    infile.close();
    return static_cast<int>(students_.size());
}

// 功能：从内存中保存学生数据到 students.dat 文件
bool StudentManager::saveToFile() const {
    std::ofstream outfile("students.dat");
    if (!outfile.is_open()) {
        std::cerr << "Error: Failed to open file students.dat" << std::endl;
        return false;
    }
    outfile << students_.size() << std::endl;
    for (const Student& s : students_) {
        outfile << s.getId() << " " 
                << s.getName() << " " 
                << s.getAge() << " " 
                << s.getScore() << "\n";
    }
    outfile.close();
    return true;
}

// 功能：判断是否存在指定学号的学生
bool StudentManager::hasId(const std::string& id) const {
    for (const Student& s : students_) {
        if (s.getId() == id) {
            return true;
        }
    }
    return false;
}

// 功能：按关键字查找第一个匹配学生的索引，未找到返回 -1
int StudentManager::findIndex(const std::string& keyword) const {
    for (int i = 0;i < students_.size();i++) {
        if (students_[i].matches(keyword)) {
            return i;
        }
    }
    return -1;
}

// 功能：返回所有匹配关键字的学生索引
std::vector<int> StudentManager::searchIndexes(const std::string& keyword) const {
    std::vector<int> indexes;
    for (int i = 0;i < students_.size();i++) {
        //matches函数是判断学生是否匹配关键字的函数,如果是true,就添加到索引数组中,返回的是索引数组的引用
        if (students_[i].matches(keyword)) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

// 功能：添加一名学生，学号重复返回 false，否则返回 true
bool StudentManager::addStudent(const Student& student) {
    if (hasId(student.getId())) {
        return false;
    }
    students_.push_back(student);
    return true;
}

// 功能：按索引删除一名学生
bool StudentManager::deleteStudent(int index) {
    if (index < 0 || index >= students_.size()) {
        return false;
    }
    students_.erase(students_.begin() + index);
    return true;
}

// 功能：按索引修改一名学生
void StudentManager::updateStudent(int index, const Student& student) {
    if (index < 0 || index >= students_.size()) {
        std::cerr << "Error: Invalid index for update" << std::endl;
        return;
    }
    students_[index] = student;
}

// 功能：按指定依据（年龄/成绩）和方式（升序/降序）对学生排序
bool StudentManager::sortStudents(SortBy by, SortOrder order) {
    if (by == SortBy::Age) {
        //lambda表达式里是捕获列表，里面是空表示不捕获任何变量，使用不可修改变量的引用进行比较，如果是true，就交换位置，否则就不交换
        std::sort(students_.begin(), students_.end(), [](const Student& a, const Student& b) {
            return a.getAge() < b.getAge();
        });
        //上面提前把年龄排序了，所以这里只需要判断是否需要反转即可。
        if (order == SortOrder::Descending) {
            std::reverse(students_.begin(), students_.end());
        }
    } else if (by == SortBy::Score) {
        std::sort(students_.begin(), students_.end(), [](const Student& a, const Student& b) {
            return a.getScore() < b.getScore();
        });
        if (order == SortOrder::Ascending) {
            std::reverse(students_.begin(), students_.end());
        }   
    }
    return true;
}

// 功能：获取学生个数
std::size_t StudentManager::size() const {
    return students_.size();
}

// 功能：按索引获取学生
const Student& StudentManager::getStudent(int index) const {
    return students_[index];
}