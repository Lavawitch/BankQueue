#include "Customer.h"
#include "Queue.h"
#include "Teller.h"
#include "Record.h"
#include "Modify.h"
#include <cstdlib>
#include <ctime>

// 初始化队列
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// 判断队列是否为空
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// 客户入队
void enqueue(Queue* queue, const char* inputID, const char* name,char* inputCode,int service,double amount) {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    strcpy(newCustomer->id,inputID);
    strcpy(newCustomer->verificationCode, inputCode);
    newCustomer->selectedService = service;
    newCustomer->amount=amount;
    strcpy(newCustomer->name, name);
    newCustomer->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newCustomer;
    } else {
        queue->rear->next = newCustomer;
        queue->rear = newCustomer;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf("客户 %s(编号：%s）已加入队列。\n", name, inputID);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
}

// 客户出队
Customer* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("队列已空，没有客户可办理业务。\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        return NULL;
    }
    Customer* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return temp;
}

// 释放队列内存
void freeQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        Customer* temp = dequeue(queue);
        free(temp);
    }
    free(queue);
}
