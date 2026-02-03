# Backend - 水电煤气管理系统

## 简介

这是高校水电煤气管理系统的后端服务，使用C++实现。

## 本地编译

```bash
# 使用 Make
make
./utility_system

# 手动编译
g++ -std=c++11 -o utility_system main.cpp utility_system.cpp
./utility_system

# 清理
make clean
```

## Docker 构建

```bash
# 构建镜像
docker build -t utility-management-system .

# 运行（交互模式）
docker run -it --rm utility-management-system

# 构建指定平台
docker build --platform linux/arm64 -t utility-management-system:arm64 .
docker build --platform linux/amd64 -t utility-management-system:amd64 .
```

## 文件说明

| 文件 | 说明 |
|------|------|
| `main.cpp` | 主程序入口 |
| `utility_system.h` | 头文件，包含所有类声明 |
| `utility_system.cpp` | 实现文件，包含所有类方法定义 |
| `Makefile` | 编译配置 |
| `Dockerfile` | Docker构建配置（支持ARM64/AMD64） |

## 类结构

```
User (抽象基类)
├── StaffUser (教工用户类)
└── StudentUser (学生用户类)

MeterRecord (抄表记录基类)
├── WaterMeterRecord (水表记录类)
├── ElectricMeterRecord (电表记录类)
└── GasMeterRecord (煤气表记录类)

PriceStandard (收费标准类)
UtilityManagementSystem (管理系统主类)
```
