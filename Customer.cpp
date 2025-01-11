#include "Customer.h"
#include "Queue.h"
#include "Modify.h"
#include "Teller.h"
#include "Record.h"
#include "Data.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip> // 用于std::setw和std::setfill

using namespace std;

//double deposite=0.0,withdrawal=0.0;
// 全局变量，用于存储序列号
static int sequenceNumber = 0;

// 函数用于生成编号
void generateUniqueID(char* id) {
    time_t now = time(nullptr);
    tm* timeNow = localtime(&now);

    // 格式化时间为 YYMMDDHHMMSS
    char timestamp[15];
    strftime(timestamp, sizeof(timestamp), "%y%m%d%H%M%S", timeNow);

    // 将序列号转换为字符串，并确保它是四位的
    char sequence[5];
    sprintf(sequence, "%04d", ++sequenceNumber);

    // 组合时间戳和序列号
    string uniqueID = string(timestamp) + "-" + sequence;
    strcpy(id, uniqueID.c_str());
}


// 用户模块函数定义
void addCustomer(Queue* queue,int flag) {
    char name[50];
    char id[20];
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    if(!flag){
        newCustomer->selectedService=1;
        newCustomer->amount=0.0;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        printf("请输入客户姓名：");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        scanf("%s", name);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        printf("正在生成客户编号……\n");
        Sleep(200);
        generateUniqueID(id);
        strcpy(newCustomer->name, name);
        strcpy(newCustomer->id, id);
        getVerificationCode(newCustomer);
        enqueue(queue, newCustomer->id, newCustomer->name,newCustomer->verificationCode,newCustomer->selectedService,newCustomer->amount);
    }else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        printf("请输入您的ID：");
        scanf("%s", id);
        strcpy(newCustomer->id, id);
        Customer* temp=findCustomer("customers.csv",newCustomer->id);
        if(temp){
            printf("请选择业务：1. 开户 2. 取款 3. 存款\n");
            scanf("%d", &newCustomer->selectedService);
            while(newCustomer->selectedService==1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("您已开户，请勿重复选择!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
                printf("请重新选择：");
                scanf("%d",&newCustomer->selectedService);
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
            printf("客户 %s 选择了 %s 业务。\n", temp->name,
            newCustomer->selectedService == 1? "开户" :
            newCustomer->selectedService == 2? "取款" :
            newCustomer->selectedService == 3? "存款" : "未知业务");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
            getVerificationCode(temp);
            enqueue(queue, temp->id, temp->name,temp->verificationCode,newCustomer->selectedService,temp->amount);//注意这里的newCustomer
        }else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("您还未开户，正在为您安排开户业务……\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
            Sleep(500);
            newCustomer->selectedService=1;
            newCustomer->amount=0.0;
            printf("请输入客户姓名：");
            scanf("%s", name);
            printf("正在生成客户编号……\n");
            Sleep(200);
            generateUniqueID(id);
            strcpy(newCustomer->name, name);
            strcpy(newCustomer->id, id);
            getVerificationCode(newCustomer);
            enqueue(queue, newCustomer->id, newCustomer->name,newCustomer->verificationCode,newCustomer->selectedService,newCustomer->amount);
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
    free(newCustomer);
}


// 生成验证码
void generateVerificationCode(char* code) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 6; i++) {
        code[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    code[6] = '\0';
}

void getVerificationCode(Customer* customer) {
    generateVerificationCode(customer->verificationCode);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
    printf("客户 %s 的验证码是：%s\n", customer->name, customer->verificationCode);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
}

void viewQueue(Queue* queue) {
    if (isEmpty(queue)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("队列已空。\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        return;
    }
    Customer* current = queue->front;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
    printf("当前排队客户：\n");
    while (current!= NULL) {
        printf("编号：%s，姓名：%s，业务：", current->id, current->name);
        switch (current->selectedService) {
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
