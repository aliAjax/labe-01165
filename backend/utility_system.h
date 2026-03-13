#ifndef UTILITY_SYSTEM_H
#define UTILITY_SYSTEM_H

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;

// 用户类型枚举
enum class UserType {
    STUDENT,    // 学生
    STAFF       // 教工
};

// 收费标准类 - 存储水电煤气的收费标准
class PriceStandard {
private:
    double waterPriceStaff;      // 教工水费单价 (元/吨)
    double waterPriceStudent;    // 学生水费单价 (元/吨)
    double electricPriceStaff;   // 教工电费单价 (元/度)
    double electricPriceStudent; // 学生电费单价 (元/度)
    double gasPriceStaff;        // 教工煤气单价 (元/立方米)
    double gasPriceStudent;      // 学生煤气单价 (元/立方米)
    
    double studentFreeWater;     // 学生免费水量 (吨)
    double studentFreeElectric;  // 学生免费电量 (度)
    double studentFreeGas;       // 学生免费煤气量 (立方米)

public:
    PriceStandard();
    
    // 获取价格
    double getWaterPrice(UserType type) const;
    double getElectricPrice(UserType type) const;
    double getGasPrice(UserType type) const;
    
    // 获取学生免费额度
    double getFreeWater() const { return studentFreeWater; }
    double getFreeElectric() const { return studentFreeElectric; }
    double getFreeGas() const { return studentFreeGas; }
    
    // 设置价格
    void setWaterPrice(UserType type, double price);
    void setElectricPrice(UserType type, double price);
    void setGasPrice(UserType type, double price);
    void setFreeQuota(double water, double electric, double gas);
    
    // 显示收费标准
    void display() const;
};

// 用户基本信息类（抽象基类）
class User {
protected:
    string userId;       // 用户ID
    string name;         // 姓名
    string address;      // 住址/房间号
    string phone;        // 联系电话
    UserType userType;   // 用户类型

public:
    User(const string& id, const string& name, const string& addr, 
         const string& phone, UserType type);
    virtual ~User() = default;
    
    // 获取信息
    string getUserId() const { return userId; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    UserType getUserType() const { return userType; }
    
    // 纯虚函数 - 获取用户类型描述
    virtual string getTypeDescription() const = 0;
    
    // 纯虚函数 - 显示用户信息
    virtual void display() const = 0;
    
    // 虚函数 - 计算费用（考虑免费额度）
    virtual double calculateFee(double usage, double price, double freeQuota = 0) const;
};

// 教工用户信息类
class StaffUser : public User {
private:
    string department;   // 所属部门
    string staffId;      // 工号

public:
    StaffUser(const string& id, const string& name, const string& addr,
              const string& phone, const string& dept, const string& staffId);
    
    string getDepartment() const { return department; }
    string getStaffId() const { return staffId; }
    
    string getTypeDescription() const override { return "教工"; }
    void display() const override;
    
    // 教工无免费额度，直接按用量计费
    double calculateFee(double usage, double price, double freeQuota = 0) const override;
};

// 学生用户信息类
class StudentUser : public User {
private:
    string studentId;    // 学号
    string dormitory;    // 宿舍楼
    int grade;           // 年级

public:
    StudentUser(const string& id, const string& name, const string& addr,
                const string& phone, const string& stuId, const string& dorm, int grade);
    
    string getStudentId() const { return studentId; }
    string getDormitory() const { return dormitory; }
    int getGrade() const { return grade; }
    
    string getTypeDescription() const override { return "学生"; }
    void display() const override;
    
    // 学生有免费额度，超出部分按较高价格计费
    double calculateFee(double usage, double price, double freeQuota = 0) const override;
};

// 抄表记录基类
class MeterRecord {
protected:
    string meterId;          // 表ID
    string userId;           // 用户ID
    string lastReadDate;     // 上次抄表时间
    string currentReadDate;  // 本次抄表时间
    double lastReading;      // 上次抄表度数
    double currentReading;   // 本次抄表度数
    double usage;            // 本次使用度数
    double fee;              // 费用
    bool isPaid;             // 是否已缴费

public:
    MeterRecord(const string& meterId, const string& userId,
                const string& lastDate, const string& currentDate,
                double lastRead, double currentRead);
    virtual ~MeterRecord() = default;
    
    // 获取信息
    string getMeterId() const { return meterId; }
    string getUserId() const { return userId; }
    double getUsage() const { return usage; }
    double getFee() const { return fee; }
    bool getIsPaid() const { return isPaid; }
    string getLastReadDate() const { return lastReadDate; }
    string getCurrentReadDate() const { return currentReadDate; }
    
    // 设置费用和缴费状态
    void setFee(double amount) { fee = amount; }
    void setPaid(bool paid) { isPaid = paid; }
    
    // 纯虚函数 - 获取记录类型
    virtual string getRecordType() const = 0;
    
    // 纯虚函数 - 获取单位
    virtual string getUnit() const = 0;
    
    // 虚函数 - 显示记录
    virtual void display() const;
};

// 水表记录类
class WaterMeterRecord : public MeterRecord {
public:
    WaterMeterRecord(const string& meterId, const string& userId,
                     const string& lastDate, const string& currentDate,
                     double lastRead, double currentRead);
    
    string getRecordType() const override { return "水表"; }
    string getUnit() const override { return "吨"; }
};

// 电表记录类
class ElectricMeterRecord : public MeterRecord {
public:
    ElectricMeterRecord(const string& meterId, const string& userId,
                        const string& lastDate, const string& currentDate,
                        double lastRead, double currentRead);
    
    string getRecordType() const override { return "电表"; }
    string getUnit() const override { return "度"; }
};

// 煤气表记录类
class GasMeterRecord : public MeterRecord {
public:
    GasMeterRecord(const string& meterId, const string& userId,
                   const string& lastDate, const string& currentDate,
                   double lastRead, double currentRead);
    
    string getRecordType() const override { return "煤气表"; }
    string getUnit() const override { return "立方米"; }
};

// 统计数据结构
struct UsageStats {
    double totalUsage;      // 总用量
    double totalFee;        // 总费用
    int recordCount;        // 记录条数
    
    UsageStats() : totalUsage(0), totalFee(0), recordCount(0) {}
};

// 水电煤气管理系统类
class UtilityManagementSystem {
private:
    vector<User*> users;                    // 用户列表
    vector<MeterRecord*> waterRecords;      // 水表记录
    vector<MeterRecord*> electricRecords;   // 电表记录
    vector<MeterRecord*> gasRecords;        // 煤气表记录
    PriceStandard priceStandard;            // 收费标准
    
    // 辅助函数
    User* findUserById(const string& userId);
    string generateMeterId(const string& prefix);
    string getCurrentDate();
    bool parseDate(const string& dateStr, int& year, int& month, int& day);
    int getQuarter(int month);
    
    // 创建记录的辅助函数
    WaterMeterRecord* createWaterRecord(const string& meterId, const string& userId, 
                                        const string& lastDate, const string& currentDate,
                                        double lastRead, double currentRead);
    ElectricMeterRecord* createElectricRecord(const string& meterId, const string& userId, 
                                              const string& lastDate, const string& currentDate,
                                              double lastRead, double currentRead);
    GasMeterRecord* createGasRecord(const string& meterId, const string& userId, 
                                    const string& lastDate, const string& currentDate,
                                    double lastRead, double currentRead);
    
    // 统计辅助函数
    void collectStatsByPeriod(const vector<MeterRecord*>& records, int year, int month, 
                              int quarter, bool isMonthly, bool isQuarterly, UsageStats& stats);
    void displayStatsTable(const string& title, const UsageStats& waterStats, 
                           const UsageStats& electricStats, const UsageStats& gasStats);
    
public:
    UtilityManagementSystem();
    ~UtilityManagementSystem();
    
    // 用户管理
    void addStaffUser();
    void addStudentUser();
    void displayAllUsers();
    void searchUser();
    
    // 抄表录入
    void addWaterRecord();
    void addElectricRecord();
    void addGasRecord();
    
    // 费用计算
    void calculateAllFees();
    void calculateUserFees(const string& userId);
    
    // 费用查询
    void queryUserFees();
    void queryAllFees();
    
    // 缴费管理
    void payFee();
    void displayUnpaidList();
    
    // 收费标准管理
    void displayPriceStandard();
    void modifyPriceStandard();
    
    // 初始化测试数据
    void initTestData();
    
    // 统计报表
    void showStatisticsMenu();
    void generateMonthlyReport();
    void generateQuarterlyReport();
    void generateAnnualReport();
    void generateUserMonthlyReport();
    void generateUserAnnualReport();
    
    // 主菜单
    void run();
    void showMainMenu();
    void showUserMenu();
    void showRecordMenu();
    void showQueryMenu();
    void showPaymentMenu();
};

#endif // UTILITY_SYSTEM_H
