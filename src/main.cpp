#include "Menu.h"

// 功能：程序入口，创建菜单对象并启动交互主循环
int main() {
    Menu menu;  // 构造时自动加载数据
    menu.run(); // 进入菜单交互
    return 0;
}