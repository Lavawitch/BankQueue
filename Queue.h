/*#ifndef QUEUE_H
#define QUEUE_H

#include "Customer.h"

// ���������нṹ��
typedef struct {
    Customer* front; // ��ͷָ��
    Customer* rear;  // ��βָ��
} Queue;

// ����ģ�麯������
Queue* createQueue();
int isEmpty(Queue* queue);
void enqueue(Queue* queue, const std::string& id, const char* name,char* inputCode,int service);
Customer* dequeue(Queue* queue);
void freeQueue(Queue* queue);

#endif // QUEUE_H
*/
