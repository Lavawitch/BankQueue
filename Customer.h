#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "Record.h"


// ����ͻ��ṹ��
typedef struct Customer {
    char id[20]; // �ͻ����
    char name[50]; // �ͻ�����
    char verificationCode[7]; // ��֤��
    int selectedService; // ѡ���ҵ��
    double amount;//���
    struct Customer* next;
} Customer;

// ���������нṹ��
typedef struct {
    Customer* front; // ��ͷָ��
    Customer* rear;  // ��βָ��
} Queue;

// ����ģ�麯������
Queue* createQueue();
int isEmpty(Queue* queue);
void enqueue(Queue* queue, const char* id, const char* name,char* inputCode,int service,double amount);
Customer* dequeue(Queue* queue);
void freeQueue(Queue* queue);

// �û�ģ�麯������
void addCustomer(Queue* queue,int flag);
void generateVerificationCode(char* code);
void getVerificationCode(Customer* customer);
void viewQueue(Queue* queue);

#endif // CUSTOMER_H
