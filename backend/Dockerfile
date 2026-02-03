# 高校水电煤气管理系统 Dockerfile
# 使用多阶段构建，支持 ARM64 和 AMD64 跨平台

# ============ 构建阶段 ============
FROM --platform=$BUILDPLATFORM alpine:3.19 AS builder

# 安装编译工具
RUN apk add --no-cache \
    g++ \
    make \
    musl-dev

# 设置工作目录
WORKDIR /app

# 复制源代码
COPY main.cpp utility_system.cpp utility_system.h Makefile ./

# 编译程序（静态链接以确保跨平台兼容）
RUN g++ -std=c++11 -static -o utility_system main.cpp utility_system.cpp

# ============ 运行阶段 ============
FROM alpine:3.19

# 添加标签
LABEL maintainer="Utility Management System"
LABEL description="高校水电煤气管理信息系统"
LABEL version="1.0"

# 安装运行时依赖（如果需要）
RUN apk add --no-cache libstdc++

# 创建非root用户
RUN addgroup -S appgroup && adduser -S appuser -G appgroup

# 设置工作目录
WORKDIR /app

# 从构建阶段复制可执行文件
COPY --from=builder /app/utility_system .

# 设置文件权限
RUN chmod +x utility_system && chown -R appuser:appgroup /app

# 切换到非root用户
USER appuser

# 设置默认命令
CMD ["./utility_system"]
