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
    printf("�� ���Ϊ%s �� �û�%s ������֤�룺",customer->id,customer->name);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
    scanf("%s", inputCode);
    if (strcmp(inputCode, customer->verificationCode) == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("��֤����֤ͨ����\n");
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("��֤�����\n");
        *flag=0;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
}

//�û����估�Ŷӵȴ�
void callCustomer(Queue* queue, Teller* tellers, int numTellers, Record** recordHead) {
    for (int i = 0; i < numTellers; i++) {
        int flag=1;
        if (isEmpty(queue)) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("û�еȴ��Ŀͻ���\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
            return;
        }
        Customer* customer = dequeue(queue);
        if (!customer) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("�����޷���ȡ�ͻ���Ϣ��\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
            return;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GOLD);
        printf("ҵ��Ա %s����ţ�%d������Ϊ %s����ţ�%s������\n", tellers[i].name, tellers[i].id, customer->name, customer->id);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        if (!tellers[i].isBusy) {
            tellers[i].isBusy = 1; // ��ҵ��Ա״̬����Ϊæµ
            verifyCustomer(customer,&flag);
        if (flag) {
                handleTransaction(customer,tellers,recordHead);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE );
                printf("%s����ţ�%s����ҵ������ѽ�����\n", customer->name, customer->id);
                printf("���Ƴ��Ѱ���ҵ��Ŀͻ���\n");//already dequeue
                tellers[i].isBusy = 0; // ������ɺ󣬽�ҵ��Ա״̬����Ϊ��æµ
        } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("�޷�����ҵ��\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
                tellers[i].isBusy = 0; // ��֤����󣬲��ı�ҵ��Ա״̬
        }
        Customer* t=customer;
        customer=customer->next;
        free(t); // �ͷſͻ��ڴ�
        }else{
            // �������ҵ��Ա��æµ�����½��ͻ��������
            enqueue(queue, customer->id, customer->name,customer->verificationCode,customer->selectedService,customer->amount);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
            printf("����ҵ��Ա����æ�����Ժ�\n");//��ʵ�����ӡ����:(
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
            free(customer); // �ͷſͻ��ڴ�
        }
    }
}

// ��̨ҵ��Աģ�麯������
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
            printf("ҵ��Ա %s����ţ�%d������Ϊ�ͻ� %s ׼�� %s ҵ��...\n",tellers[i].name,tellers[i].id, customer->name,
            customer->selectedService == 1? "����" :
            customer->selectedService == 2? "ȡ��" :
            customer->selectedService == 3? "���" : "δ֪ҵ��");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        }
        customer=customer->next;
    }
    while(customer){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        printf("�����Ŷӵ��û�Ϊ��%s����ţ�%s��\n",customer->name,customer->id);
        customer=customer->next;
    }
}

void handleTransaction(Customer* customer, Teller* teller, Record** recordHead) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
    if (customer->selectedService == 1) {
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        printf("Ϊ�ͻ� %s �����ɹ���\n", customer->name);
        saveCustomerToFile(customer, "customers.csv");
    }
    else if (customer->selectedService == 2) {
        printf("������ȡ���");
        scanf("%lf",&withdrawal);
        while(customer->amount<withdrawal){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("���㣬�޷�ȡ��\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
            printf("���������룺");
            scanf("%lf",&withdrawal);
        }
        customer->amount -= withdrawal;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("ȡ��ɹ�\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        if(updateCustomerData("customers.csv", customer)){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("�ļ������Ѹ���\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        }else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("�ļ����ݸ���ʧ��\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        }
    }
    else if (customer->selectedService == 3) {
        printf("���������");
        scanf("%lf", &deposite);
        customer->amount += deposite;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("���ɹ�\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        if(updateCustomerData("customers.csv",customer)){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("�ļ������Ѹ���\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        }else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("�ļ����ݸ���ʧ��\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
        }
    }
    transactionStats[customer->selectedService]++;
    recordTransaction(recordHead, customer->id, customer->name, teller->id, teller->name, customer->selectedService);
}
