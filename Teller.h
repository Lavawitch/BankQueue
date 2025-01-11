#ifndef TELLER_H
#define TELLER_H

#include <string>
#include "Customer.h"


// 定义柜台业务员结构体
typedef struct {
    int id;
    char name[50];
    int isBusy; // 表示业务员是否忙碌，0 表示空闲，1 表示忙碌
} Teller;

// 柜台业务员模块函数声明
Teller* createTeller(int id, const char* name);
void callCustomer(Queue* queue, Teller* tellers, int numTellers, Record** recordHead);
void verifyCustomer(Customer* customer,int *flag);
void prepareService(Customer* customer,Teller* tellers, int numTellers);
void handleTransaction(Customer* customer, Teller* teller, Record** recordHead);

#endif // TELLER_H
