#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "Record.h"


// 定义客户结构体
typedef struct Customer {
    char id[20]; // 客户编号
    char name[50]; // 客户姓名
    char verificationCode[7]; // 验证码
    int selectedService; // 选择的业务
    double amount;//余额
    struct Customer* next;
} Customer;

// 定义链队列结构体
typedef struct {
    Customer* front; // 队头指针
    Customer* rear;  // 队尾指针
} Queue;

// 队列模块函数声明
Queue* createQueue();
int isEmpty(Queue* queue);
void enqueue(Queue* queue, const char* id, const char* name,char* inputCode,int service,double amount);
Customer* dequeue(Queue* queue);
void freeQueue(Queue* queue);

// 用户模块函数声明
void addCustomer(Queue* queue,int flag);
void generateVerificationCode(char* code);
void getVerificationCode(Customer* customer);
void viewQueue(Queue* queue);

#endif // CUSTOMER_H
