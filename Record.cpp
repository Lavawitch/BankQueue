#include "Customer.h"
#include "Queue.h"
#include "Teller.h"
#include "Record.h"
#include "Modify.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

// ��¼ģ�麯������
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
        printf("û�н��׼�¼��\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        return;
    }
    Record* current = recordHead;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
    printf("���׼�¼��\n");
    while (current!= NULL) {
        printf("�ͻ���ţ�%s���ͻ�������%s��ҵ��Ա��ţ�%d��ҵ��Ա������%s��ҵ��", current->customerId, current->customerName, current->tellerId, current->tellerName);
        switch (current->serviceType) {
            case 1:
                printf("����");
                break;
            case 2:
                printf("ȡ��");
                break;
            case 3:
                printf("���");
                break;
            default:
                printf("δ֪");
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
    printf("ҵ��ͳ�����ݣ�\n");
    for (const auto& pair : stats) {
        printf("ҵ������ %s : %d ��\n",
            pair.first == 1? "����" :
            pair.first == 2? "ȡ��" :
            pair.first == 3? "���" : "δ֪ҵ��", pair.second);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
}
