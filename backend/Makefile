# 水电煤气管理系统 Makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = utility_system
SOURCES = main.cpp utility_system.cpp
HEADERS = utility_system.h

# 默认目标
all: $(TARGET)

# 链接
$(TARGET): main.o utility_system.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# 编译main.cpp
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

# 编译utility_system.cpp
utility_system.o: utility_system.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c utility_system.cpp

# 清理
clean:
	rm -f *.o $(TARGET)

# 运行
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
