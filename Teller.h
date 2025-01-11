#ifndef TELLER_H
#define TELLER_H

#include <string>
#include "Customer.h"


// �����̨ҵ��Ա�ṹ��
typedef struct {
    int id;
    char name[50];
    int isBusy; // ��ʾҵ��Ա�Ƿ�æµ��0 ��ʾ���У�1 ��ʾæµ
} Teller;

// ��̨ҵ��Աģ�麯������
Teller* createTeller(int id, const char* name);
void callCustomer(Queue* queue, Teller* tellers, int numTellers, Record** recordHead);
void verifyCustomer(Customer* customer,int *flag);
void prepareService(Customer* customer,Teller* tellers, int numTellers);
void handleTransaction(Customer* customer, Teller* teller, Record** recordHead);

#endif // TELLER_H
