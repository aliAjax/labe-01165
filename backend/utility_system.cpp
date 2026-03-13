#include "utility_system.h"
#include <sstream>
#include <algorithm>
#include <ctime>
#include <limits>
#include <fstream>

// 辅助函数：安全读取整数输入
int safeInputInt() {
    int value;
    while (!(cin >> value)) {
        if (cin.eof()) {
            cout << "\n输入流结束，程序退出。" << endl;
            exit(0);
        }
        cin.clear();  // 清除错误状态
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清除缓冲区
        cout << "输入无效，请输入数字: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清除剩余字符
    return value;
}

// 辅助函数：安全读取字符串输入
string safeInputString() {
    string value;
    cin >> value;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// 辅助函数：安全读取浮点数输入
double safeInputDouble() {
    double value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "输入无效，请输入数字: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// ==================== PriceStandard 类实现 ====================

PriceStandard::PriceStandard() {
    // 默认收费标准
    waterPriceStaff = 3.0;        // 教工水费 3.0元/吨
    waterPriceStudent = 4.5;      // 学生水费 4.5元/吨（超出免费额度部分）
    electricPriceStaff = 0.6;     // 教工电费 0.6元/度
    electricPriceStudent = 0.8;   // 学生电费 0.8元/度（超出免费额度部分）
    gasPriceStaff = 2.5;          // 教工煤气 2.5元/立方米
    gasPriceStudent = 3.0;        // 学生煤气 3.0元/立方米（超出免费额度部分）
    
    // 学生免费额度
    studentFreeWater = 3.0;       // 免费水量 3吨
    studentFreeElectric = 20.0;   // 免费电量 20度
    studentFreeGas = 5.0;         // 免费煤气 5立方米
}

double PriceStandard::getWaterPrice(UserType type) const {
    return (type == UserType::STAFF) ? waterPriceStaff : waterPriceStudent;
}

double PriceStandard::getElectricPrice(UserType type) const {
    return (type == UserType::STAFF) ? electricPriceStaff : electricPriceStudent;
}

double PriceStandard::getGasPrice(UserType type) const {
    return (type == UserType::STAFF) ? gasPriceStaff : gasPriceStudent;
}

void PriceStandard::setWaterPrice(UserType type, double price) {
    if (type == UserType::STAFF) {
        waterPriceStaff = price;
    } else {
        waterPriceStudent = price;
    }
}

void PriceStandard::setElectricPrice(UserType type, double price) {
    if (type == UserType::STAFF) {
        electricPriceStaff = price;
    } else {
        electricPriceStudent = price;
    }
}

void PriceStandard::setGasPrice(UserType type, double price) {
    if (type == UserType::STAFF) {
        gasPriceStaff = price;
    } else {
        gasPriceStudent = price;
    }
}

void PriceStandard::setFreeQuota(double water, double electric, double gas) {
    studentFreeWater = water;
    studentFreeElectric = electric;
    studentFreeGas = gas;
}

void PriceStandard::display() const {
    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    收费标准信息                           ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════╣" << endl;
    cout << "║ 项目          │ 教工单价          │ 学生单价(超额)       ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════╣" << endl;
    cout << "║ 水费          │ " << setw(8) << fixed << setprecision(2) << waterPriceStaff 
         << " 元/吨    │ " << setw(8) << waterPriceStudent << " 元/吨     ║" << endl;
    cout << "║ 电费          │ " << setw(8) << electricPriceStaff 
         << " 元/度    │ " << setw(8) << electricPriceStudent << " 元/度     ║" << endl;
    cout << "║ 煤气费        │ " << setw(8) << gasPriceStaff 
         << " 元/m³    │ " << setw(8) << gasPriceStudent << " 元/m³     ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════╣" << endl;
    cout << "║ 学生免费额度：                                            ║" << endl;
    cout << "║   水：" << setw(6) << studentFreeWater << " 吨  |  电：" << setw(6) << studentFreeElectric 
         << " 度  |  煤气：" << setw(6) << studentFreeGas << " m³  ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
}

// ==================== User 类实现 ====================

User::User(const string& id, const string& name, const string& addr, 
           const string& phone, UserType type)
    : userId(id), name(name), address(addr), phone(phone), userType(type) {}

double User::calculateFee(double usage, double price, double freeQuota) const {
    // 基类默认实现：直接计算费用
    return usage * price;
}

// ==================== StaffUser 类实现 ====================

StaffUser::StaffUser(const string& id, const string& name, const string& addr,
                     const string& phone, const string& dept, const string& staffId)
    : User(id, name, addr, phone, UserType::STAFF), 
      department(dept), staffId(staffId) {}

void StaffUser::display() const {
    cout << "┌────────────────────────────────────────┐" << endl;
    cout << "│ 用户类型: 教工                          │" << endl;
    cout << "├────────────────────────────────────────┤" << endl;
    cout << "│ 用户ID:   " << setw(28) << left << userId << " │" << endl;
    cout << "│ 姓名:     " << setw(28) << name << " │" << endl;
    cout << "│ 工号:     " << setw(28) << staffId << " │" << endl;
    cout << "│ 部门:     " << setw(28) << department << " │" << endl;
    cout << "│ 地址:     " << setw(28) << address << " │" << endl;
    cout << "│ 电话:     " << setw(28) << phone << " │" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
}

double StaffUser::calculateFee(double usage, double price, double freeQuota) const {
    // 教工无免费额度，直接按用量计费
    return usage * price;
}

// ==================== StudentUser 类实现 ====================

StudentUser::StudentUser(const string& id, const string& name, const string& addr,
                         const string& phone, const string& stuId, 
                         const string& dorm, int grade)
    : User(id, name, addr, phone, UserType::STUDENT),
      studentId(stuId), dormitory(dorm), grade(grade) {}

void StudentUser::display() const {
    cout << "┌────────────────────────────────────────┐" << endl;
    cout << "│ 用户类型: 学生                          │" << endl;
    cout << "├────────────────────────────────────────┤" << endl;
    cout << "│ 用户ID:   " << setw(28) << left << userId << " │" << endl;
    cout << "│ 姓名:     " << setw(28) << name << " │" << endl;
    cout << "│ 学号:     " << setw(28) << studentId << " │" << endl;
    cout << "│ 宿舍楼:   " << setw(28) << dormitory << " │" << endl;
    cout << "│ 年级:     " << setw(28) << grade << " │" << endl;
    cout << "│ 房间:     " << setw(28) << address << " │" << endl;
    cout << "│ 电话:     " << setw(28) << phone << " │" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
}

double StudentUser::calculateFee(double usage, double price, double freeQuota) const {
    // 学生有免费额度，超出部分按较高价格计费
    if (usage <= freeQuota) {
        return 0.0;  // 在免费额度内
    }
    return (usage - freeQuota) * price;  // 超出部分计费
}

// ==================== MeterRecord 类实现 ====================

MeterRecord::MeterRecord(const string& meterId, const string& userId,
                         const string& lastDate, const string& currentDate,
                         double lastRead, double currentRead)
    : meterId(meterId), userId(userId), 
      lastReadDate(lastDate), currentReadDate(currentDate),
      lastReading(lastRead), currentReading(currentRead),
      fee(0.0), isPaid(false) {
    usage = currentRead - lastRead;
    if (usage < 0) usage = 0;  // 防止负数
}

void MeterRecord::display() const {
    cout << "┌────────────────────────────────────────────┐" << endl;
    cout << "│ " << setw(10) << left << getRecordType() << " 记录                          │" << endl;
    cout << "├────────────────────────────────────────────┤" << endl;
    cout << "│ 表ID:       " << setw(30) << left << meterId << " │" << endl;
    cout << "│ 用户ID:     " << setw(30) << userId << " │" << endl;
    cout << "│ 上次抄表:   " << setw(30) << lastReadDate << " │" << endl;
    cout << "│ 本次抄表:   " << setw(30) << currentReadDate << " │" << endl;
    cout << "│ 上次度数:   " << setw(28) << fixed << setprecision(2) << lastReading 
         << getUnit() << " │" << endl;
    cout << "│ 本次度数:   " << setw(28) << currentReading << getUnit() << " │" << endl;
    cout << "│ 本次用量:   " << setw(28) << usage << getUnit() << " │" << endl;
    cout << "│ 应缴费用:   " << setw(30) << fee << "元 │" << endl;
    cout << "│ 缴费状态:   " << setw(30) << (isPaid ? "已缴费" : "未缴费") << " │" << endl;
    cout << "└────────────────────────────────────────────┘" << endl;
}

// ==================== WaterMeterRecord 类实现 ====================

WaterMeterRecord::WaterMeterRecord(const string& meterId, const string& userId,
                                   const string& lastDate, const string& currentDate,
                                   double lastRead, double currentRead)
    : MeterRecord(meterId, userId, lastDate, currentDate, lastRead, currentRead) {}

// ==================== ElectricMeterRecord 类实现 ====================

ElectricMeterRecord::ElectricMeterRecord(const string& meterId, const string& userId,
                                         const string& lastDate, const string& currentDate,
                                         double lastRead, double currentRead)
    : MeterRecord(meterId, userId, lastDate, currentDate, lastRead, currentRead) {}

// ==================== GasMeterRecord 类实现 ====================

GasMeterRecord::GasMeterRecord(const string& meterId, const string& userId,
                               const string& lastDate, const string& currentDate,
                               double lastRead, double currentRead)
    : MeterRecord(meterId, userId, lastDate, currentDate, lastRead, currentRead) {}

// ==================== UtilityManagementSystem 类实现 ====================

UtilityManagementSystem::UtilityManagementSystem() {}

UtilityManagementSystem::~UtilityManagementSystem() {
    // 释放所有用户对象
    for (auto user : users) {
        delete user;
    }
    // 释放所有记录对象
    for (auto record : waterRecords) {
        delete record;
    }
    for (auto record : electricRecords) {
        delete record;
    }
    for (auto record : gasRecords) {
        delete record;
    }
}

User* UtilityManagementSystem::findUserById(const string& userId) {
    for (auto user : users) {
        if (user->getUserId() == userId) {
            return user;
        }
    }
    return nullptr;
}

string UtilityManagementSystem::generateMeterId(const string& prefix) {
    static int counter = 1000;
    stringstream ss;
    ss << prefix << setw(6) << setfill('0') << ++counter;
    return ss.str();
}

string UtilityManagementSystem::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << (1900 + ltm->tm_year) << "-" 
       << setw(2) << setfill('0') << (1 + ltm->tm_mon) << "-"
       << setw(2) << setfill('0') << ltm->tm_mday;
    return ss.str();
}

void UtilityManagementSystem::addStaffUser() {
    cout << "\n===== 添加教工用户 =====" << endl;
    cout << "请输入用户ID: ";
    string id = safeInputString();
    
    if (findUserById(id) != nullptr) {
        cout << "错误：该用户ID已存在！" << endl;
        return;
    }
    
    cout << "请输入姓名: ";
    string name = safeInputString();
    cout << "请输入住址/房间号: ";
    string addr = safeInputString();
    cout << "请输入联系电话: ";
    string phone = safeInputString();
    cout << "请输入所属部门: ";
    string dept = safeInputString();
    cout << "请输入工号: ";
    string staffId = safeInputString();
    
    users.push_back(new StaffUser(id, name, addr, phone, dept, staffId));
    cout << "教工用户添加成功！" << endl;
}

void UtilityManagementSystem::addStudentUser() {
    cout << "\n===== 添加学生用户 =====" << endl;
    cout << "请输入用户ID: ";
    string id = safeInputString();
    
    if (findUserById(id) != nullptr) {
        cout << "错误：该用户ID已存在！" << endl;
        return;
    }
    
    cout << "请输入姓名: ";
    string name = safeInputString();
    cout << "请输入房间号: ";
    string addr = safeInputString();
    cout << "请输入联系电话: ";
    string phone = safeInputString();
    cout << "请输入学号: ";
    string stuId = safeInputString();
    cout << "请输入宿舍楼: ";
    string dorm = safeInputString();
    cout << "请输入年级: ";
    int grade = safeInputInt();
    
    users.push_back(new StudentUser(id, name, addr, phone, stuId, dorm, grade));
    cout << "学生用户添加成功！" << endl;
}

void UtilityManagementSystem::displayAllUsers() {
    if (users.empty()) {
        cout << "\n暂无用户信息！" << endl;
        return;
    }
    
    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    所有用户列表                           ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    
    for (auto user : users) {
        user->display();
        cout << endl;
    }
    cout << "共 " << users.size() << " 个用户" << endl;
}

void UtilityManagementSystem::searchUser() {
    cout << "\n请输入要查询的用户ID或姓名: ";
    string keyword = safeInputString();
    
    bool found = false;
    for (auto user : users) {
        if (user->getUserId() == keyword || user->getName() == keyword) {
            user->display();
            found = true;
        }
    }
    
    if (!found) {
        cout << "未找到匹配的用户！" << endl;
    }
}

void UtilityManagementSystem::addWaterRecord() {
    cout << "\n===== 录入水表数据 =====" << endl;
    cout << "请输入用户ID: ";
    string userId = safeInputString();
    
    if (findUserById(userId) == nullptr) {
        cout << "错误：用户不存在！" << endl;
        return;
    }
    
    cout << "请输入上次抄表日期 (YYYY-MM-DD): ";
    string lastDate = safeInputString();
    cout << "请输入上次抄表度数: ";
    double lastRead = safeInputDouble();
    cout << "请输入本次抄表度数: ";
    double currentRead = safeInputDouble();
    
    string meterId = generateMeterId("W");
    string currentDate = getCurrentDate();
    
    WaterMeterRecord* record = new WaterMeterRecord(meterId, userId, 
                                                     lastDate, currentDate,
                                                     lastRead, currentRead);
    
    // 计算费用
    User* user = findUserById(userId);
    double price = priceStandard.getWaterPrice(user->getUserType());
    double freeQuota = (user->getUserType() == UserType::STUDENT) ? 
                       priceStandard.getFreeWater() : 0;
    double fee = user->calculateFee(record->getUsage(), price, freeQuota);
    record->setFee(fee);
    
    waterRecords.push_back(record);
    cout << "水表数据录入成功！表ID: " << meterId << endl;
    cout << "本次用水: " << record->getUsage() << " 吨, 应缴费用: " << fee << " 元" << endl;
}

void UtilityManagementSystem::addElectricRecord() {
    cout << "\n===== 录入电表数据 =====" << endl;
    cout << "请输入用户ID: ";
    string userId = safeInputString();
    
    if (findUserById(userId) == nullptr) {
        cout << "错误：用户不存在！" << endl;
        return;
    }
    
    cout << "请输入上次抄表日期 (YYYY-MM-DD): ";
    string lastDate = safeInputString();
    cout << "请输入上次抄表度数: ";
    double lastRead = safeInputDouble();
    cout << "请输入本次抄表度数: ";
    double currentRead = safeInputDouble();
    
    string meterId = generateMeterId("E");
    string currentDate = getCurrentDate();
    
    ElectricMeterRecord* record = new ElectricMeterRecord(meterId, userId,
                                                           lastDate, currentDate,
                                                           lastRead, currentRead);
    
    // 计算费用
    User* user = findUserById(userId);
    double price = priceStandard.getElectricPrice(user->getUserType());
    double freeQuota = (user->getUserType() == UserType::STUDENT) ? 
                       priceStandard.getFreeElectric() : 0;
    double fee = user->calculateFee(record->getUsage(), price, freeQuota);
    record->setFee(fee);
    
    electricRecords.push_back(record);
    cout << "电表数据录入成功！表ID: " << meterId << endl;
    cout << "本次用电: " << record->getUsage() << " 度, 应缴费用: " << fee << " 元" << endl;
}

void UtilityManagementSystem::addGasRecord() {
    cout << "\n===== 录入煤气表数据 =====" << endl;
    cout << "请输入用户ID: ";
    string userId = safeInputString();
    
    if (findUserById(userId) == nullptr) {
        cout << "错误：用户不存在！" << endl;
        return;
    }
    
    cout << "请输入上次抄表日期 (YYYY-MM-DD): ";
    string lastDate = safeInputString();
    cout << "请输入上次抄表度数: ";
    double lastRead = safeInputDouble();
    cout << "请输入本次抄表度数: ";
    double currentRead = safeInputDouble();
    
    string meterId = generateMeterId("G");
    string currentDate = getCurrentDate();
    
    GasMeterRecord* record = new GasMeterRecord(meterId, userId,
                                                 lastDate, currentDate,
                                                 lastRead, currentRead);
    
    // 计算费用
    User* user = findUserById(userId);
    double price = priceStandard.getGasPrice(user->getUserType());
    double freeQuota = (user->getUserType() == UserType::STUDENT) ? 
                       priceStandard.getFreeGas() : 0;
    double fee = user->calculateFee(record->getUsage(), price, freeQuota);
    record->setFee(fee);
    
    gasRecords.push_back(record);
    cout << "煤气表数据录入成功！表ID: " << meterId << endl;
    cout << "本次用气: " << record->getUsage() << " 立方米, 应缴费用: " << fee << " 元" << endl;
}

void UtilityManagementSystem::calculateAllFees() {
    cout << "\n正在重新计算所有费用..." << endl;
    
    // 计算水费
    for (auto record : waterRecords) {
        User* user = findUserById(record->getUserId());
        if (user) {
            double price = priceStandard.getWaterPrice(user->getUserType());
            double freeQuota = (user->getUserType() == UserType::STUDENT) ?
                               priceStandard.getFreeWater() : 0;
            double fee = user->calculateFee(record->getUsage(), price, freeQuota);
            record->setFee(fee);
        }
    }
    
    // 计算电费
    for (auto record : electricRecords) {
        User* user = findUserById(record->getUserId());
        if (user) {
            double price = priceStandard.getElectricPrice(user->getUserType());
            double freeQuota = (user->getUserType() == UserType::STUDENT) ?
                               priceStandard.getFreeElectric() : 0;
            double fee = user->calculateFee(record->getUsage(), price, freeQuota);
            record->setFee(fee);
        }
    }
    
    // 计算煤气费
    for (auto record : gasRecords) {
        User* user = findUserById(record->getUserId());
        if (user) {
            double price = priceStandard.getGasPrice(user->getUserType());
            double freeQuota = (user->getUserType() == UserType::STUDENT) ?
                               priceStandard.getFreeGas() : 0;
            double fee = user->calculateFee(record->getUsage(), price, freeQuota);
            record->setFee(fee);
        }
    }
    
    cout << "所有费用计算完成！" << endl;
}

void UtilityManagementSystem::calculateUserFees(const string& userId) {
    User* user = findUserById(userId);
    if (!user) {
        cout << "用户不存在！" << endl;
        return;
    }
    
    double totalWater = 0, totalElectric = 0, totalGas = 0;
    
    // 统计水费
    for (auto record : waterRecords) {
        if (record->getUserId() == userId && !record->getIsPaid()) {
            totalWater += record->getFee();
        }
    }
    
    // 统计电费
    for (auto record : electricRecords) {
        if (record->getUserId() == userId && !record->getIsPaid()) {
            totalElectric += record->getFee();
        }
    }
    
    // 统计煤气费
    for (auto record : gasRecords) {
        if (record->getUserId() == userId && !record->getIsPaid()) {
            totalGas += record->getFee();
        }
    }
    
    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    用户费用汇总                           ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    user->display();
    cout << "\n未缴费用明细：" << endl;
    cout << "├─ 水费:     " << fixed << setprecision(2) << totalWater << " 元" << endl;
    cout << "├─ 电费:     " << totalElectric << " 元" << endl;
    cout << "├─ 煤气费:   " << totalGas << " 元" << endl;
    cout << "└─ 合计:     " << (totalWater + totalElectric + totalGas) << " 元" << endl;
}

void UtilityManagementSystem::queryUserFees() {
    cout << "\n请输入要查询的用户ID: ";
    string userId = safeInputString();
    
    calculateUserFees(userId);
}

void UtilityManagementSystem::queryAllFees() {
    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    所有费用记录                           ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n【水表记录】共 " << waterRecords.size() << " 条" << endl;
    for (auto record : waterRecords) {
        record->display();
    }
    
    cout << "\n【电表记录】共 " << electricRecords.size() << " 条" << endl;
    for (auto record : electricRecords) {
        record->display();
    }
    
    cout << "\n【煤气表记录】共 " << gasRecords.size() << " 条" << endl;
    for (auto record : gasRecords) {
        record->display();
    }
}

void UtilityManagementSystem::payFee() {
    cout << "\n===== 缴费 =====" << endl;
    cout << "请输入用户ID: ";
    string userId = safeInputString();
    
    User* user = findUserById(userId);
    if (!user) {
        cout << "用户不存在！" << endl;
        return;
    }
    
    cout << "请选择缴费类型：" << endl;
    cout << "1. 水费" << endl;
    cout << "2. 电费" << endl;
    cout << "3. 煤气费" << endl;
    cout << "4. 全部缴清" << endl;
    cout << "请选择: ";
    int choice = safeInputInt();
    
    double total = 0;
    int count = 0;
    
    switch (choice) {
        case 1:
            for (auto record : waterRecords) {
                if (record->getUserId() == userId && !record->getIsPaid()) {
                    record->setPaid(true);
                    total += record->getFee();
                    count++;
                }
            }
            cout << "已缴纳水费 " << count << " 笔，共 " << total << " 元" << endl;
            break;
        case 2:
            for (auto record : electricRecords) {
                if (record->getUserId() == userId && !record->getIsPaid()) {
                    record->setPaid(true);
                    total += record->getFee();
                    count++;
                }
            }
            cout << "已缴纳电费 " << count << " 笔，共 " << total << " 元" << endl;
            break;
        case 3:
            for (auto record : gasRecords) {
                if (record->getUserId() == userId && !record->getIsPaid()) {
                    record->setPaid(true);
                    total += record->getFee();
                    count++;
                }
            }
            cout << "已缴纳煤气费 " << count << " 笔，共 " << total << " 元" << endl;
            break;
        case 4:
            for (auto record : waterRecords) {
                if (record->getUserId() == userId && !record->getIsPaid()) {
                    record->setPaid(true);
                    total += record->getFee();
                    count++;
                }
            }
            for (auto record : electricRecords) {
                if (record->getUserId() == userId && !record->getIsPaid()) {
                    record->setPaid(true);
                    total += record->getFee();
                    count++;
                }
            }
            for (auto record : gasRecords) {
                if (record->getUserId() == userId && !record->getIsPaid()) {
                    record->setPaid(true);
                    total += record->getFee();
                    count++;
                }
            }
            cout << "已缴纳全部费用 " << count << " 笔，共 " << total << " 元" << endl;
            break;
        default:
            cout << "无效选择！" << endl;
    }
}

void UtilityManagementSystem::displayUnpaidList() {
    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    未缴费名单                             ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    
    map<string, double> unpaidUsers;
    
    // 统计水费欠费
    for (auto record : waterRecords) {
        if (!record->getIsPaid()) {
            unpaidUsers[record->getUserId()] += record->getFee();
        }
    }
    
    // 统计电费欠费
    for (auto record : electricRecords) {
        if (!record->getIsPaid()) {
            unpaidUsers[record->getUserId()] += record->getFee();
        }
    }
    
    // 统计煤气费欠费
    for (auto record : gasRecords) {
        if (!record->getIsPaid()) {
            unpaidUsers[record->getUserId()] += record->getFee();
        }
    }
    
    if (unpaidUsers.empty()) {
        cout << "\n恭喜！所有用户均已缴清费用！" << endl;
        return;
    }
    
    cout << "\n┌──────────────┬────────────────┬──────────────┬────────────┐" << endl;
    cout << "│    用户ID    │      姓名      │     类型     │   欠费金额 │" << endl;
    cout << "├──────────────┼────────────────┼──────────────┼────────────┤" << endl;
    
    double totalUnpaid = 0;
    for (auto& pair : unpaidUsers) {
        User* user = findUserById(pair.first);
        if (user) {
            cout << "│ " << setw(12) << left << user->getUserId()
                 << " │ " << setw(14) << user->getName()
                 << " │ " << setw(12) << user->getTypeDescription()
                 << " │ " << setw(10) << fixed << setprecision(2) << pair.second << " │" << endl;
            totalUnpaid += pair.second;
        }
    }
    
    cout << "└──────────────┴────────────────┴──────────────┴────────────┘" << endl;
    cout << "共 " << unpaidUsers.size() << " 个用户欠费，总欠费金额: " << totalUnpaid << " 元" << endl;
}

void UtilityManagementSystem::displayPriceStandard() {
    priceStandard.display();
}

void UtilityManagementSystem::modifyPriceStandard() {
    cout << "\n===== 修改收费标准 =====" << endl;
    priceStandard.display();
    
    cout << "\n请选择要修改的项目：" << endl;
    cout << "1. 教工水费单价" << endl;
    cout << "2. 学生水费单价" << endl;
    cout << "3. 教工电费单价" << endl;
    cout << "4. 学生电费单价" << endl;
    cout << "5. 教工煤气单价" << endl;
    cout << "6. 学生煤气单价" << endl;
    cout << "7. 学生免费额度" << endl;
    cout << "0. 返回" << endl;
    cout << "请选择: ";
    int choice = safeInputInt();
    
    double price;
    switch (choice) {
        case 1:
            cout << "请输入新的教工水费单价(元/吨): ";
            price = safeInputDouble();
            priceStandard.setWaterPrice(UserType::STAFF, price);
            break;
        case 2:
            cout << "请输入新的学生水费单价(元/吨): ";
            price = safeInputDouble();
            priceStandard.setWaterPrice(UserType::STUDENT, price);
            break;
        case 3:
            cout << "请输入新的教工电费单价(元/度): ";
            price = safeInputDouble();
            priceStandard.setElectricPrice(UserType::STAFF, price);
            break;
        case 4:
            cout << "请输入新的学生电费单价(元/度): ";
            price = safeInputDouble();
            priceStandard.setElectricPrice(UserType::STUDENT, price);
            break;
        case 5:
            cout << "请输入新的教工煤气单价(元/m³): ";
            price = safeInputDouble();
            priceStandard.setGasPrice(UserType::STAFF, price);
            break;
        case 6:
            cout << "请输入新的学生煤气单价(元/m³): ";
            price = safeInputDouble();
            priceStandard.setGasPrice(UserType::STUDENT, price);
            break;
        case 7: {
            cout << "请输入学生免费水量(吨): ";
            double water = safeInputDouble();
            cout << "请输入学生免费电量(度): ";
            double electric = safeInputDouble();
            cout << "请输入学生免费煤气量(m³): ";
            double gas = safeInputDouble();
            priceStandard.setFreeQuota(water, electric, gas);
            break;
        }
        case 0:
            return;
        default:
            cout << "无效选择！" << endl;
            return;
    }
    
    cout << "收费标准修改成功！" << endl;
    calculateAllFees();  // 重新计算所有费用
}

void UtilityManagementSystem::initTestData() {
    // 检查是否已有数据
    if (!users.empty() || !waterRecords.empty() || !electricRecords.empty() || !gasRecords.empty()) {
        cout << "\n系统中已存在数据，是否清空后重新初始化？(1-是, 0-否): ";
        int confirm = safeInputInt();
        if (confirm != 1) {
            cout << "已取消初始化。" << endl;
            return;
        }
        // 清空现有数据
        for (auto user : users) delete user;
        users.clear();
        for (auto record : waterRecords) delete record;
        waterRecords.clear();
        for (auto record : electricRecords) delete record;
        electricRecords.clear();
        for (auto record : gasRecords) delete record;
        gasRecords.clear();
        cout << "已清空现有数据。" << endl;
    }
    
    cout << "\n正在初始化测试数据..." << endl;
    
    // 添加5个教工用户
    users.push_back(new StaffUser("T001", "张教授", "教师公寓A101", "13800001111", "计算机学院", "20150001"));
    users.push_back(new StaffUser("T002", "李副教授", "教师公寓A202", "13800002222", "数学学院", "20160002"));
    users.push_back(new StaffUser("T003", "王讲师", "教师公寓B103", "13800003333", "物理学院", "20180003"));
    users.push_back(new StaffUser("T004", "刘教授", "教师公寓B204", "13800004444", "化学学院", "20140004"));
    users.push_back(new StaffUser("T005", "陈副教授", "教师公寓C105", "13800005555", "外语学院", "20170005"));
    
    // 添加5个学生用户
    users.push_back(new StudentUser("S001", "小明", "101室", "15900001111", "2021001001", "学生公寓1号楼", 3));
    users.push_back(new StudentUser("S002", "小红", "102室", "15900002222", "2021001002", "学生公寓1号楼", 3));
    users.push_back(new StudentUser("S003", "小刚", "201室", "15900003333", "2022001003", "学生公寓2号楼", 2));
    users.push_back(new StudentUser("S004", "小丽", "202室", "15900004444", "2022001004", "学生公寓2号楼", 2));
    users.push_back(new StudentUser("S005", "小强", "301室", "15900005555", "2023001005", "学生公寓3号楼", 1));
    
    // 添加水表记录
    WaterMeterRecord* w1 = new WaterMeterRecord("W001001", "T001", "2025-12-01", "2026-01-01", 100.0, 108.5);
    WaterMeterRecord* w2 = new WaterMeterRecord("W001002", "T002", "2025-12-01", "2026-01-01", 200.0, 206.0);
    WaterMeterRecord* w3 = new WaterMeterRecord("W001003", "S001", "2025-12-01", "2026-01-01", 50.0, 55.0);
    WaterMeterRecord* w4 = new WaterMeterRecord("W001004", "S002", "2025-12-01", "2026-01-01", 60.0, 62.0);
    WaterMeterRecord* w5 = new WaterMeterRecord("W001005", "S003", "2025-12-01", "2026-01-01", 70.0, 78.0);
    
    // 计算并设置水费
    User* u1 = findUserById("T001");
    w1->setFee(u1->calculateFee(w1->getUsage(), priceStandard.getWaterPrice(u1->getUserType()), 0));
    
    User* u2 = findUserById("T002");
    w2->setFee(u2->calculateFee(w2->getUsage(), priceStandard.getWaterPrice(u2->getUserType()), 0));
    
    User* u3 = findUserById("S001");
    w3->setFee(u3->calculateFee(w3->getUsage(), priceStandard.getWaterPrice(u3->getUserType()), 
               priceStandard.getFreeWater()));
    
    User* u4 = findUserById("S002");
    w4->setFee(u4->calculateFee(w4->getUsage(), priceStandard.getWaterPrice(u4->getUserType()),
               priceStandard.getFreeWater()));
    
    User* u5 = findUserById("S003");
    w5->setFee(u5->calculateFee(w5->getUsage(), priceStandard.getWaterPrice(u5->getUserType()),
               priceStandard.getFreeWater()));
    
    waterRecords.push_back(w1);
    waterRecords.push_back(w2);
    waterRecords.push_back(w3);
    waterRecords.push_back(w4);
    waterRecords.push_back(w5);
    
    // 添加电表记录
    ElectricMeterRecord* e1 = new ElectricMeterRecord("E001001", "T001", "2025-12-01", "2026-01-01", 1000.0, 1150.0);
    ElectricMeterRecord* e2 = new ElectricMeterRecord("E001002", "T003", "2025-12-01", "2026-01-01", 800.0, 920.0);
    ElectricMeterRecord* e3 = new ElectricMeterRecord("E001003", "S001", "2025-12-01", "2026-01-01", 500.0, 545.0);
    ElectricMeterRecord* e4 = new ElectricMeterRecord("E001004", "S004", "2025-12-01", "2026-01-01", 300.0, 315.0);
    ElectricMeterRecord* e5 = new ElectricMeterRecord("E001005", "S005", "2025-12-01", "2026-01-01", 400.0, 480.0);
    
    // 计算并设置电费
    e1->setFee(u1->calculateFee(e1->getUsage(), priceStandard.getElectricPrice(u1->getUserType()), 0));
    
    User* u6 = findUserById("T003");
    e2->setFee(u6->calculateFee(e2->getUsage(), priceStandard.getElectricPrice(u6->getUserType()), 0));
    
    e3->setFee(u3->calculateFee(e3->getUsage(), priceStandard.getElectricPrice(u3->getUserType()),
               priceStandard.getFreeElectric()));
    
    User* u7 = findUserById("S004");
    e4->setFee(u7->calculateFee(e4->getUsage(), priceStandard.getElectricPrice(u7->getUserType()),
               priceStandard.getFreeElectric()));
    
    User* u8 = findUserById("S005");
    e5->setFee(u8->calculateFee(e5->getUsage(), priceStandard.getElectricPrice(u8->getUserType()),
               priceStandard.getFreeElectric()));
    
    electricRecords.push_back(e1);
    electricRecords.push_back(e2);
    electricRecords.push_back(e3);
    electricRecords.push_back(e4);
    electricRecords.push_back(e5);
    
    // 添加煤气表记录
    GasMeterRecord* g1 = new GasMeterRecord("G001001", "T002", "2025-12-01", "2026-01-01", 50.0, 65.0);
    GasMeterRecord* g2 = new GasMeterRecord("G001002", "T004", "2025-12-01", "2026-01-01", 80.0, 92.0);
    GasMeterRecord* g3 = new GasMeterRecord("G001003", "S002", "2025-12-01", "2026-01-01", 20.0, 28.0);
    GasMeterRecord* g4 = new GasMeterRecord("G001004", "S003", "2025-12-01", "2026-01-01", 30.0, 42.0);
    GasMeterRecord* g5 = new GasMeterRecord("G001005", "T005", "2025-12-01", "2026-01-01", 40.0, 48.0);
    
    // 计算并设置煤气费
    g1->setFee(u2->calculateFee(g1->getUsage(), priceStandard.getGasPrice(u2->getUserType()), 0));
    
    User* u9 = findUserById("T004");
    g2->setFee(u9->calculateFee(g2->getUsage(), priceStandard.getGasPrice(u9->getUserType()), 0));
    
    g3->setFee(u4->calculateFee(g3->getUsage(), priceStandard.getGasPrice(u4->getUserType()),
               priceStandard.getFreeGas()));
    
    g4->setFee(u5->calculateFee(g4->getUsage(), priceStandard.getGasPrice(u5->getUserType()),
               priceStandard.getFreeGas()));
    
    User* u10 = findUserById("T005");
    g5->setFee(u10->calculateFee(g5->getUsage(), priceStandard.getGasPrice(u10->getUserType()), 0));
    
    gasRecords.push_back(g1);
    gasRecords.push_back(g2);
    gasRecords.push_back(g3);
    gasRecords.push_back(g4);
    gasRecords.push_back(g5);
    
    // 设置部分记录为已缴费
    w1->setPaid(true);
    e1->setPaid(true);
    g5->setPaid(true);
    
    cout << "测试数据初始化完成！" << endl;
    cout << "已添加 " << users.size() << " 个用户" << endl;
    cout << "已添加 " << waterRecords.size() << " 条水表记录" << endl;
    cout << "已添加 " << electricRecords.size() << " 条电表记录" << endl;
    cout << "已添加 " << gasRecords.size() << " 条煤气表记录" << endl;
}

void UtilityManagementSystem::showMainMenu() {
    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║            水电煤气管理系统 - 主菜单                       ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════╣" << endl;
    cout << "║  1. 用户管理                                              ║" << endl;
    cout << "║  2. 抄表录入                                              ║" << endl;
    cout << "║  3. 费用查询                                              ║" << endl;
    cout << "║  4. 缴费管理                                              ║" << endl;
    cout << "║  5. 收费标准                                              ║" << endl;
    cout << "║  6. 统计报表                                              ║" << endl;
    cout << "║  7. 初始化测试数据                                        ║" << endl;
    cout << "║  0. 退出系统                                              ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    cout << "请选择: ";
}

void UtilityManagementSystem::showUserMenu() {
    int choice;
    do {
        cout << "\n===== 用户管理 =====" << endl;
        cout << "1. 添加教工用户" << endl;
        cout << "2. 添加学生用户" << endl;
        cout << "3. 查看所有用户" << endl;
        cout << "4. 查询用户" << endl;
        cout << "0. 返回上级菜单" << endl;
        cout << "请选择: ";
        choice = safeInputInt();
        
        switch (choice) {
            case 1: addStaffUser(); break;
            case 2: addStudentUser(); break;
            case 3: displayAllUsers(); break;
            case 4: searchUser(); break;
            case 0: break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 0);
}

void UtilityManagementSystem::showRecordMenu() {
    int choice;
    do {
        cout << "\n===== 抄表录入 =====" << endl;
        cout << "1. 录入水表数据" << endl;
        cout << "2. 录入电表数据" << endl;
        cout << "3. 录入煤气表数据" << endl;
        cout << "0. 返回上级菜单" << endl;
        cout << "请选择: ";
        choice = safeInputInt();
        
        switch (choice) {
            case 1: addWaterRecord(); break;
            case 2: addElectricRecord(); break;
            case 3: addGasRecord(); break;
            case 0: break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 0);
}

void UtilityManagementSystem::showQueryMenu() {
    int choice;
    do {
        cout << "\n===== 费用查询 =====" << endl;
        cout << "1. 查询指定用户费用" << endl;
        cout << "2. 查看所有费用记录" << endl;
        cout << "3. 重新计算所有费用" << endl;
        cout << "0. 返回上级菜单" << endl;
        cout << "请选择: ";
        choice = safeInputInt();
        
        switch (choice) {
            case 1: queryUserFees(); break;
            case 2: queryAllFees(); break;
            case 3: calculateAllFees(); break;
            case 0: break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 0);
}

void UtilityManagementSystem::showPaymentMenu() {
    int choice;
    do {
        cout << "\n===== 缴费管理 =====" << endl;
        cout << "1. 用户缴费" << endl;
        cout << "2. 查看未缴费名单" << endl;
        cout << "0. 返回上级菜单" << endl;
        cout << "请选择: ";
        choice = safeInputInt();
        
        switch (choice) {
            case 1: payFee(); break;
            case 2: displayUnpaidList(); break;
            case 0: break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 0);
}

void UtilityManagementSystem::run() {
    int choice;
    
    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║        欢迎使用高校水电煤气管理信息系统                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << flush;
    
    do {
        showMainMenu();
        cout << flush;  // 确保菜单立即显示
        choice = safeInputInt();
        
        switch (choice) {
            case 1: showUserMenu(); break;
            case 2: showRecordMenu(); break;
            case 3: showQueryMenu(); break;
            case 4: showPaymentMenu(); break;
            case 5:
                displayPriceStandard();
                cout << "\n是否修改收费标准？(1-是, 0-否): ";
                {
                    int modify = safeInputInt();
                    if (modify == 1) modifyPriceStandard();
                }
                break;
            case 6: showStatisticsMenu(); break;
            case 7: initTestData(); break;
            case 0:
                cout << "\n感谢使用，再见！" << endl;
                break;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    } while (choice != 0);
}

// ==================== 统计报表功能实现 ====================

// 辅助函数：验证日期格式是否为 YYYY-MM-DD
bool isValidDateFormat(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    // 检查年份部分是否为数字
    for (int i = 0; i < 4; i++) {
        if (!isdigit(date[i])) return false;
    }
    
    // 检查月份部分是否为数字
    for (int i = 5; i < 7; i++) {
        if (!isdigit(date[i])) return false;
    }
    
    // 检查日期部分是否为数字
    for (int i = 8; i < 10; i++) {
        if (!isdigit(date[i])) return false;
    }
    
    // 验证月份范围
    int month = stoi(date.substr(5, 2));
    if (month < 1 || month > 12) return false;
    
    return true;
}

string UtilityManagementSystem::getPeriodKey(const string& date, StatisticsPeriod period) {
    // 验证日期格式
    if (!isValidDateFormat(date)) {
        return "unknown";
    }
    
    // 日期格式: YYYY-MM-DD
    string year = date.substr(0, 4);
    string month = date.substr(5, 2);
    
    switch (period) {
        case StatisticsPeriod::MONTHLY:
            return year + "-" + month;
        case StatisticsPeriod::QUARTERLY: {
            int m = stoi(month);
            int quarter = (m - 1) / 3 + 1;
            return year + "-Q" + to_string(quarter);
        }
        case StatisticsPeriod::YEARLY:
            return year;
        default:
            return year + "-" + month;
    }
}

// 辅助函数：验证月度周期键格式是否为 YYYY-MM
bool isValidMonthlyPeriodKey(const string& periodKey) {
    if (periodKey.length() != 7) return false;
    if (periodKey[4] != '-') return false;
    
    // 检查年份部分是否为数字
    for (int i = 0; i < 4; i++) {
        if (!isdigit(periodKey[i])) return false;
    }
    
    // 检查月份部分是否为数字
    for (int i = 5; i < 7; i++) {
        if (!isdigit(periodKey[i])) return false;
    }
    
    // 验证月份范围
    int month = stoi(periodKey.substr(5, 2));
    if (month < 1 || month > 12) return false;
    
    return true;
}

// 辅助函数：验证季度周期键格式是否为 YYYY-QN
bool isValidQuarterlyPeriodKey(const string& periodKey) {
    if (periodKey.length() != 7) return false;  // 格式：YYYY-QN (7个字符)
    if (periodKey[4] != '-' || periodKey[5] != 'Q') return false;
    
    // 检查年份部分是否为数字
    for (int i = 0; i < 4; i++) {
        if (!isdigit(periodKey[i])) return false;
    }
    
    // 检查季度部分是否为数字
    if (!isdigit(periodKey[6])) return false;
    
    // 验证季度范围
    int quarter = periodKey[6] - '0';
    if (quarter < 1 || quarter > 4) return false;
    
    return true;
}

// 辅助函数：验证年度周期键格式是否为 YYYY
bool isValidYearlyPeriodKey(const string& periodKey) {
    if (periodKey.length() != 4) return false;
    
    // 检查年份部分是否为数字
    for (int i = 0; i < 4; i++) {
        if (!isdigit(periodKey[i])) return false;
    }
    
    return true;
}

string UtilityManagementSystem::getPeriodDescription(const string& periodKey, StatisticsPeriod period) {
    // 处理未知周期
    if (periodKey == "unknown") {
        return "未知周期";
    }
    
    switch (period) {
        case StatisticsPeriod::MONTHLY:
            if (isValidMonthlyPeriodKey(periodKey)) {
                return periodKey.substr(0, 4) + "年" + periodKey.substr(5, 2) + "月";
            }
            break;
        case StatisticsPeriod::QUARTERLY:
            if (isValidQuarterlyPeriodKey(periodKey)) {
                string year = periodKey.substr(0, 4);
                string q = periodKey.substr(6, 1);
                return year + "年第" + q + "季度";
            }
            break;
        case StatisticsPeriod::YEARLY:
            if (isValidYearlyPeriodKey(periodKey)) {
                return periodKey + "年度";
            }
            break;
    }
    
    // 格式不正确时返回原始键
    return periodKey;
}

void UtilityManagementSystem::generateStatistics(StatisticsPeriod period) {
    map<string, StatisticsData> statsMap;
    
    // 统计水表数据
    for (auto record : waterRecords) {
        string periodKey = getPeriodKey(record->getCurrentReadDate(), period);
        statsMap[periodKey].period = periodKey;
        statsMap[periodKey].totalWaterUsage += record->getUsage();
        statsMap[periodKey].totalWaterFee += record->getFee();
        statsMap[periodKey].recordCount++;
    }
    
    // 统计电表数据
    for (auto record : electricRecords) {
        string periodKey = getPeriodKey(record->getCurrentReadDate(), period);
        statsMap[periodKey].period = periodKey;
        statsMap[periodKey].totalElectricUsage += record->getUsage();
        statsMap[periodKey].totalElectricFee += record->getFee();
        statsMap[periodKey].recordCount++;
    }
    
    // 统计煤气表数据
    for (auto record : gasRecords) {
        string periodKey = getPeriodKey(record->getCurrentReadDate(), period);
        statsMap[periodKey].period = periodKey;
        statsMap[periodKey].totalGasUsage += record->getUsage();
        statsMap[periodKey].totalGasFee += record->getFee();
        statsMap[periodKey].recordCount++;
    }
    
    if (statsMap.empty()) {
        cout << "\n暂无统计数据！" << endl;
        return;
    }
    
    // 显示统计报表
    displayStatistics(statsMap, period);
    
    // 询问是否导出到文件
    cout << "\n是否将统计报表导出到文件？(1-是, 0-否): ";
    int exportChoice = safeInputInt();
    if (exportChoice == 1) {
        exportStatisticsToFile(statsMap, period);
    }
}

void UtilityManagementSystem::displayStatistics(const map<string, StatisticsData>& stats, StatisticsPeriod period) {
    string periodName;
    switch (period) {
        case StatisticsPeriod::MONTHLY: periodName = "月度"; break;
        case StatisticsPeriod::QUARTERLY: periodName = "季度"; break;
        case StatisticsPeriod::YEARLY: periodName = "年度"; break;
    }
    
    cout << "\n╔════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                    " << periodName << "用量统计报表                                         ║" << endl;
    cout << "╠════════════════╤═══════════════╤═══════════════╤═══════════════╤══════════════════════════════════╣" << endl;
    cout << "║   统计周期     │    用水量(吨)  │    用电量(度)  │   用气量(m³)  │   水费(元)  │  电费(元)  │  煤气费(元) │" << endl;
    cout << "╠════════════════╪═══════════════╪═══════════════╪═══════════════╪═════════════╪════════════╪═════════════╣" << endl;
    
    double totalWater = 0, totalElectric = 0, totalGas = 0;
    double totalWaterFee = 0, totalElectricFee = 0, totalGasFee = 0;
    
    for (auto& pair : stats) {
        const StatisticsData& data = pair.second;
        string periodDesc = getPeriodDescription(pair.first, period);
        
        cout << "║ " << setw(12) << left << periodDesc
             << " │ " << setw(13) << right << fixed << setprecision(2) << data.totalWaterUsage
             << " │ " << setw(13) << data.totalElectricUsage
             << " │ " << setw(13) << data.totalGasUsage
             << " │ " << setw(11) << data.totalWaterFee
             << " │ " << setw(10) << data.totalElectricFee
             << " │ " << setw(11) << data.totalGasFee << " │" << endl;
        
        totalWater += data.totalWaterUsage;
        totalElectric += data.totalElectricUsage;
        totalGas += data.totalGasUsage;
        totalWaterFee += data.totalWaterFee;
        totalElectricFee += data.totalElectricFee;
        totalGasFee += data.totalGasFee;
    }
    
    cout << "╠════════════════╪═══════════════╪═══════════════╪═══════════════╪═════════════╪════════════╪═════════════╣" << endl;
    cout << "║    总计        │ " << setw(13) << right << totalWater
         << " │ " << setw(13) << totalElectric
         << " │ " << setw(13) << totalGas
         << " │ " << setw(11) << totalWaterFee
         << " │ " << setw(10) << totalElectricFee
         << " │ " << setw(11) << totalGasFee << " │" << endl;
    cout << "╚════════════════╧═══════════════╧═══════════════╧═══════════════╧═════════════╧════════════╧═════════════╝" << endl;
}

void UtilityManagementSystem::exportStatisticsToFile(const map<string, StatisticsData>& stats, StatisticsPeriod period) {
    string periodName;
    switch (period) {
        case StatisticsPeriod::MONTHLY: periodName = "monthly"; break;
        case StatisticsPeriod::QUARTERLY: periodName = "quarterly"; break;
        case StatisticsPeriod::YEARLY: periodName = "yearly"; break;
    }
    
    string filename = periodName + "_statistics_" + getCurrentDate() + ".csv";
    
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "无法创建文件：" << filename << endl;
        return;
    }
    
    // 写入BOM以支持Excel中文显示
    file << "\xEF\xBB\xBF";
    
    // 写入表头
    file << "统计周期,用水量(吨),水费(元),用电量(度),电费(元),用气量(m³),煤气费(元)" << endl;
    
    // 写入数据
    for (auto& pair : stats) {
        const StatisticsData& data = pair.second;
        string periodDesc = getPeriodDescription(pair.first, period);
        file << periodDesc << ","
             << fixed << setprecision(2)
             << data.totalWaterUsage << ","
             << data.totalWaterFee << ","
             << data.totalElectricUsage << ","
             << data.totalElectricFee << ","
             << data.totalGasUsage << ","
             << data.totalGasFee << endl;
    }
    
    file.close();
    cout << "统计报表已导出到文件：" << filename << endl;
}

void UtilityManagementSystem::showStatisticsMenu() {
    int choice;
    do {
        cout << "\n===== 统计报表 =====" << endl;
        cout << "1. 月度用量统计" << endl;
        cout << "2. 季度用量统计" << endl;
        cout << "3. 年度用量统计" << endl;
        cout << "0. 返回上级菜单" << endl;
        cout << "请选择: ";
        choice = safeInputInt();
        
        switch (choice) {
            case 1:
                generateStatistics(StatisticsPeriod::MONTHLY);
                break;
            case 2:
                generateStatistics(StatisticsPeriod::QUARTERLY);
                break;
            case 3:
                generateStatistics(StatisticsPeriod::YEARLY);
                break;
            case 0:
                break;
            default:
                cout << "无效选择！" << endl;
        }
    } while (choice != 0);
}
