#include "Customer.h"
#include "Queue.h"
#include "Teller.h"
#include "Record.h"
#include "Modify.h"
#include <cstdlib>
#include <ctime>

// ��ʼ������
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// �ж϶����Ƿ�Ϊ��
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// �ͻ����
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
    printf("�ͻ� %s(��ţ�%s���Ѽ�����С�\n", name, inputID);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
}

// �ͻ�����
Customer* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("�����ѿգ�û�пͻ��ɰ���ҵ��\n");
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

// �ͷŶ����ڴ�
void freeQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        Customer* temp = dequeue(queue);
        free(temp);
    }
    free(queue);
}
