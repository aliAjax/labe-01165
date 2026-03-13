#include "utility_system.h"
#include <iostream>

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    
    UtilityManagementSystem system;
    
    // 初始化测试数据
    std::cout << "初始化测试数据..." << std::endl;
    system.initTestData();
    
    // 测试统计功能
    std::cout << "\n\n=== 测试统计报表功能 ===" << std::endl;
    
    // 手动调用统计函数
    std::cout << "\n--- 2025年1月统计 ---" << std::endl;
    UsageStats waterStats, electricStats, gasStats;
    
    // 需要访问私有成员，这里通过调用菜单模拟
    // 让我们创建一个测试输入
    std::cout << "\n请手动运行 ./utility_system 并选择菜单 6 -> 1 来测试月度报表" << std::endl;
    
    return 0;
}
