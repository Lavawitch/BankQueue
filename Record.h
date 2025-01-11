#ifndef RECORD_H
#define RECORD_H
#include <string>
#include <unordered_map>

extern std::unordered_map<int, int> transactionStats;

// 定义记录结构体
typedef struct Record {
    char customerId[20];
    char customerName[50];
    int tellerId;
    char tellerName[50];
    int serviceType;
    struct Record* next;
} Record;

// 记录模块函数声明
void recordTransaction(Record** recordHead,const char* customerId, const char* customerName, int tellerId, const char* tellerName, int serviceType);
void viewRecords(Record* recordHead);
void freeRecords(Record* recordHead);
void displayStatistics(const std::unordered_map<int, int>& stats);

#endif // RECORD_H
