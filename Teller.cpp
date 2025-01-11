#include "Teller.h"
#include "Queue.h"
#include "Customer.h"
#include "Modify.h"
#include "Record.h"
#include "Data.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

std::unordered_map<int, int> transactionStats;
double deposite=0.0,withdrawal=0.0;

void verifyCustomer(Customer* customer,int* flag) {
    char inputCode[7];
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
    printf("请 编号为%s 的 用户%s 输入验证码：",customer->id,customer->name);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
    scanf("%s", inputCode);
    if (strcmp(inputCode, customer->verificationCode) == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("验证码验证通过。\n");
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("验证码错误。\n");
        *flag=0;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
}

//用户分配及排队等待
void callCustomer(Queue* queue, Teller* tellers, int numTellers, Record** recordHead) {
    for (int i = 0; i < numTellers; i++) {
        int flag=1;
        if (isEmpty(queue)) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("没有等待的客户。\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
            return;
        }
        Customer* customer = dequeue(queue);
        if (!customer) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("错误：无法获取客户信息。\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
            return;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GOLD);
        printf("业务员 %s（编号：%d）正在为 %s（编号：%s）服务。\n", tellers[i].name, tellers[i].id, customer->name, customer->id);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        if (!tellers[i].isBusy) {
            tellers[i].isBusy = 1; // 将业务员状态设置为忙碌
            verifyCustomer(customer,&flag);
        if (flag) {
                handleTransaction(customer,tellers,recordHead);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE );
                printf("%s（编号：%s）的业务办理已结束。\n", customer->name, customer->id);
                printf("已移除已办理业务的客户。\n");//already dequeue
                tellers[i].isBusy = 0; // 服务完成后，将业务员状态设置为不忙碌
        } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("无法办理业务。\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
                tellers[i].isBusy = 0; // 验证码错误，不改变业务员状态
        }
        Customer* t=customer;
        customer=customer->next;
        free(t); // 释放客户内存
        }else{
            // 如果所有业务员都忙碌，重新将客户加入队列
            enqueue(queue, customer->id, customer->name,customer->verificationCode,customer->selectedService,customer->amount);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
            printf("所有业务员都正忙，请稍后。\n");//其实不会打印出来:(
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
            free(customer); // 释放客户内存
        }
    }
}

// 柜台业务员模块函数定义
Teller* createTeller(int id, const char* name) {
    Teller* teller = (Teller*)malloc(sizeof(Teller));
    teller->id = id;
    strcpy(teller->name, name);
    teller->isBusy = 0;
    return teller;
}

void prepareService(Customer* customer,Teller* tellers, int numTellers){
    for(int i=0;i<numTellers&&customer;i++){
        if(!tellers[i].isBusy){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
            printf("业务员 %s（编号：%d）正在为客户 %s 准备 %s 业务...\n",tellers[i].name,tellers[i].id, customer->name,
            customer->selectedService == 1? "开户" :
            customer->selectedService == 2? "取款" :
            customer->selectedService == 3? "存款" : "未知业务");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        }
        customer=customer->next;
    }
    while(customer){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        printf("正在排队的用户为：%s（编号：%s）\n",customer->name,customer->id);
        customer=customer->next;
    }
}

void handleTransaction(Customer* customer, Teller* teller, Record** recordHead) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
    if (customer->selectedService == 1) {
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        printf("为客户 %s 开户成功。\n", customer->name);
        saveCustomerToFile(customer, "customers.csv");
    }
    else if (customer->selectedService == 2) {
        printf("请输入取款金额：");
        scanf("%lf",&withdrawal);
        while(customer->amount<withdrawal){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("余额不足，无法取款\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
            printf("请重新输入：");
            scanf("%lf",&withdrawal);
        }
        customer->amount -= withdrawal;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("取款成功\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        if(updateCustomerData("customers.csv", customer)){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("文件内容已更新\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        }else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("文件内容更新失败\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        }
    }
    else if (customer->selectedService == 3) {
        printf("请输入存款金额：");
        scanf("%lf", &deposite);
        customer->amount += deposite;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("存款成功\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        if(updateCustomerData("customers.csv",customer)){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("文件内容已更新\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        }else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("文件内容更新失败\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        }
    }
    transactionStats[customer->selectedService]++;
    recordTransaction(recordHead, customer->id, customer->name, teller->id, teller->name, customer->selectedService);
}
