/**
 * 高校水电煤气管理信息系统
 * 
 * 功能描述：
 * 1. 用户信息管理：支持教工和学生两种用户类型
 * 2. 水电煤气数据录入：录入各类表的抄表数据
 * 3. 费用计算与查询：
 *    - 教工：按用量直接计费
 *    - 学生：享有免费额度，超出部分按较高价格计费
 * 4. 缴费管理：支持缴费和查询未缴费名单
 * 
 * 设计特点：
 * - 使用继承和多态实现用户类层次结构
 * - 使用虚函数实现差异化费用计算
 * - 使用抽象基类实现统一的接口
 * 
 * 作者：AI助手
 * 日期：2026年2月
 */

#include "utility_system.h"
#include <iostream>

int main() {
    // 禁用输出缓冲，确保Docker环境下实时显示
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    
    // 创建管理系统实例
    UtilityManagementSystem system;
    
    // 运行系统
    system.run();
    
    return 0;
}
