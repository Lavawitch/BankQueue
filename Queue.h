/*#ifndef QUEUE_H
#define QUEUE_H

#include "Customer.h"

// 定义链队列结构体
typedef struct {
    Customer* front; // 队头指针
    Customer* rear;  // 队尾指针
} Queue;

// 队列模块函数声明
Queue* createQueue();
int isEmpty(Queue* queue);
void enqueue(Queue* queue, const std::string& id, const char* name,char* inputCode,int service);
Customer* dequeue(Queue* queue);
void freeQueue(Queue* queue);

#endif // QUEUE_H
*/
