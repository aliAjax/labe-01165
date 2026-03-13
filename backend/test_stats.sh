#!/bin/bash
# 测试统计报表功能
cd /Users/ali/Desktop/moreWork/GSD/label-01165/backend

# 编译
make

# 测试统计报表功能 - 先初始化测试数据，然后测试报表
echo "测试月度报表功能..."
echo -e "7\n6\n1\n2025\n1\n0\n0\n" | ./utility_system 2>&1 | tail -50

echo -e "\n\n测试季度报表功能..."
echo -e "7\n6\n2\n2025\n1\n0\n0\n" | ./utility_system 2>&1 | tail -50

echo -e "\n\n测试年度报表功能..."
echo -e "7\n6\n3\n2025\n0\n0\n" | ./utility_system 2>&1 | tail -50

echo -e "\n\n测试完成！"
