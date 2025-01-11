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
#include <iomanip> // ����std::setw��std::setfill

using namespace std;

//double deposite=0.0,withdrawal=0.0;
// ȫ�ֱ��������ڴ洢���к�
static int sequenceNumber = 0;

// �����������ɱ��
void generateUniqueID(char* id) {
    time_t now = time(nullptr);
    tm* timeNow = localtime(&now);

    // ��ʽ��ʱ��Ϊ YYMMDDHHMMSS
    char timestamp[15];
    strftime(timestamp, sizeof(timestamp), "%y%m%d%H%M%S", timeNow);

    // �����к�ת��Ϊ�ַ�������ȷ��������λ��
    char sequence[5];
    sprintf(sequence, "%04d", ++sequenceNumber);

    // ���ʱ��������к�
    string uniqueID = string(timestamp) + "-" + sequence;
    strcpy(id, uniqueID.c_str());
}


// �û�ģ�麯������
void addCustomer(Queue* queue,int flag) {
    char name[50];
    char id[20];
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    if(!flag){
        newCustomer->selectedService=1;
        newCustomer->amount=0.0;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        printf("������ͻ�������");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        scanf("%s", name);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        printf("�������ɿͻ���š���\n");
        Sleep(200);
        generateUniqueID(id);
        strcpy(newCustomer->name, name);
        strcpy(newCustomer->id, id);
        getVerificationCode(newCustomer);
        enqueue(queue, newCustomer->id, newCustomer->name,newCustomer->verificationCode,newCustomer->selectedService,newCustomer->amount);
    }else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        printf("����������ID��");
        scanf("%s", id);
        strcpy(newCustomer->id, id);
        Customer* temp=findCustomer("customers.csv",newCustomer->id);
        if(temp){
            printf("��ѡ��ҵ��1. ���� 2. ȡ�� 3. ���\n");
            scanf("%d", &newCustomer->selectedService);
            while(newCustomer->selectedService==1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("���ѿ����������ظ�ѡ��!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
                printf("������ѡ��");
                scanf("%d",&newCustomer->selectedService);
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
            printf("�ͻ� %s ѡ���� %s ҵ��\n", temp->name,
            newCustomer->selectedService == 1? "����" :
            newCustomer->selectedService == 2? "ȡ��" :
            newCustomer->selectedService == 3? "���" : "δ֪ҵ��");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
            getVerificationCode(temp);
            enqueue(queue, temp->id, temp->name,temp->verificationCode,newCustomer->selectedService,temp->amount);//ע�������newCustomer
        }else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("����δ����������Ϊ�����ſ���ҵ�񡭡�\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
            Sleep(500);
            newCustomer->selectedService=1;
            newCustomer->amount=0.0;
            printf("������ͻ�������");
            scanf("%s", name);
            printf("�������ɿͻ���š���\n");
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


// ������֤��
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
    printf("�ͻ� %s ����֤���ǣ�%s\n", customer->name, customer->verificationCode);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
}

void viewQueue(Queue* queue) {
    if (isEmpty(queue)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("�����ѿա�\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        return;
    }
    Customer* current = queue->front;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
    printf("��ǰ�Ŷӿͻ���\n");
    while (current!= NULL) {
        printf("��ţ�%s��������%s��ҵ��", current->id, current->name);
        switch (current->selectedService) {
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
