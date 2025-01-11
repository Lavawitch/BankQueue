#include "Customer.h"
#include "Queue.h"
#include "Teller.h"
#include "Record.h"
#include "Modify.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

// 记录模块函数定义
void recordTransaction(Record** recordHead, const char* customerId, const char* customerName, int tellerId, const char* tellerName, int serviceType) {
    Record* newRecord = (Record*)malloc(sizeof(Record));
    strcpy(newRecord->customerId, customerId);
    strcpy(newRecord->customerName, customerName);
    newRecord->tellerId = tellerId;
    strcpy(newRecord->tellerName, tellerName);
    newRecord->serviceType = serviceType;
    newRecord->next = *recordHead;
    *recordHead = newRecord;
}

void viewRecords(Record* recordHead) {
    if (!recordHead) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("没有交易记录。\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        return;
    }
    Record* current = recordHead;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
    printf("交易记录：\n");
    while (current!= NULL) {
        printf("客户编号：%s，客户姓名：%s，业务员编号：%d，业务员姓名：%s，业务：", current->customerId, current->customerName, current->tellerId, current->tellerName);
        switch (current->serviceType) {
            case 1:
                printf("开户");
                break;
            case 2:
                printf("取款");
                break;
            case 3:
                printf("存款");
                break;
            default:
                printf("未知");
        }
        printf("\n");
        current = current->next;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
}

void freeRecords(Record* recordHead) {
    Record* current = recordHead;
    Record* nextRecord;
    while (current!= NULL) {
        nextRecord = current->next;
        free(current);
        current = nextRecord;
    }
}

void displayStatistics(const std::unordered_map<int, int>& stats) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_MAGENTA|FOREGROUND_INTENSITY);
    printf("业务统计数据：\n");
    for (const auto& pair : stats) {
        printf("业务类型 %s : %d 次\n",
            pair.first == 1? "开户" :
            pair.first == 2? "取款" :
            pair.first == 3? "存款" : "未知业务", pair.second);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
}
