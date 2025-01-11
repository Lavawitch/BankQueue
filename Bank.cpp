#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Customer.h"
#include "Queue.h"
#include "Teller.h"
#include "Record.h"
#include "Modify.h"
#include "Data.h"
//double deposite=0.0,withdrawal=0.0;
int flag=1;
const char* adminPassword = "Admin651562006";


void Bank(){
    system("cls"); // ����
    //Customer* loadedCustomers = NULL; // ��������ʼ���Ƶ� switch ֮��
    srand(time(NULL));
    Queue* bankQueue = createQueue();
    int numTellers = 3;
    Teller* tellers = (Teller*)malloc(numTellers * sizeof(Teller));
    tellers[0]=*createTeller(1,"Teller.Emily");
    tellers[1]=*createTeller(2,"Teller.Abby");
    tellers[2]=*createTeller(3,"Teller.Olaf");
    char inputPassword[100];
    Record* recordHead = NULL;
    int choice, subChoice;
    int running=1;
    outerLoop:;
    while (running) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("\t     < �����Ŷ�ϵͳ�˵� >\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        PrintSeparator();
        // Print menu items with decorative lines
        printf("�U        1. �û�                              �U\n");
        PrintDecorativeLine();
        printf("�U        2. ��̨ҵ��Ա                        �U\n");
        PrintDecorativeLine();
        printf("�U        3. �鿴�����ļ�                      �U\n");
        PrintDecorativeLine();
        printf("�U        4. ��������ļ�                      �U\n");
        PrintDecorativeLine();
        printf("�U        5. �˳�                              �U\n");
        // Print bottom frame
        PrintBottomSeparator();
        printf("��ѡ�������");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                while (1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_CYAN);
                    printf("\t\t< �û������˵� >\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                    PrintSeparator();
                    printf("�U        1. ���û����п���                    �U\n");
                    PrintDecorativeLine();
                    printf("�U        2. �ѿ����û�ѡ��ҵ��                �U\n");
                    PrintDecorativeLine();
                    printf("�U        3. �鿴�Ŷ����                      �U\n");
                    PrintDecorativeLine();
                    printf("�U        4. �����ϼ��˵�                      �U\n");
                    PrintBottomSeparator();
                    printf("��ѡ�������");
                    scanf("%d", &subChoice);
                    system("cls");
                    switch (subChoice) {
                    case 2:
                        flag=1;
                        addCustomer(bankQueue,flag);
                        break;
                    case 1:
                        flag=0;
                        addCustomer(bankQueue,flag);
                        //saveCustomerToFile(bankQueue->rear, "customers.csv");
                        break;
                    case 3:
                        viewQueue(bankQueue);
                        break;
                    case 4:
                        goto outerLoop;
                    default:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                        printf("��Чѡ�����������롣\n");
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                    }
                }
            case 2:
                while (1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_CYAN );
                    printf("\t   < ��̨ҵ��Ա�����˵� >\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE );
                    PrintSeparator();
                    printf("�U        1. ׼���û�����ҵ��                  �U\n");
                    PrintDecorativeLine();
                    printf("�U        2. �����û�����ҵ��                  �U\n");
                    PrintDecorativeLine();
                    printf("�U        3. �鿴���׼�¼                      �U\n");
                    PrintDecorativeLine();
                    printf("�U        4. �����ϼ��˵�                      �U\n");
                    PrintBottomSeparator();
                    printf("��ѡ�������");
                    scanf("%d", &subChoice);
                    system("cls");

                    switch (subChoice) {
                        case 2:
                            callCustomer(bankQueue, tellers, numTellers, &recordHead);
                            break;
                        case 1:
                            if (isEmpty(bankQueue)) {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                                printf("������û�пͻ���\n");
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                            } else {
                                Customer* currentCustomer = bankQueue->front;
                                prepareService(currentCustomer,tellers,numTellers);
                            }
                            break;
                        case 3:
                            viewRecords(recordHead);
                            displayStatistics(transactionStats);
                            break;
                        case 4:
                            goto outerLoop;
                        default:
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                            printf("��Чѡ�����������롣\n");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                    }
                }
            case 3:
                // ���������ļ�
                //loadData("customers.csv", bankQueue);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
                printf("�������Ա�����Բ鿴�����ļ���");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                scanf("%s", inputPassword);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
                if (strcmp(inputPassword,adminPassword)==0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    printf("������ȷ\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
                    printf("���ڼ��������ļ�����\n");
                    Sleep(400);
                    printf("���ݴ洢��ʽ(��ţ���������֤�룺ҵ��ѡ��˻����)\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("��ע�⣬��֤���ҵ��ѡ�����ʱЧ�ԣ�ֻ��¼��һ���û��������û�����������ͬ��������Ψһ�����ɸ���\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_MAGENTA|FOREGROUND_INTENSITY);
                    PrintFile("customers.csv");
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("��������޷��鿴�����ļ���\n");
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                break;
            case 4:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
                printf("�������Ա��������������ļ���");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                scanf("%s", inputPassword);
                if (strcmp(inputPassword,adminPassword)==0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    printf("������ȷ\n");
                    if (clearFileContent("customers.csv")) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                        printf("�ļ���������ա�\n");
                    } else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                        printf("����ļ�����ʧ�ܡ�\n");
                    }
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("��������޷���������ļ���\n");
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                break;
            case 5:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
                PrintFish();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                running=0;
                break;
            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("��Чѡ�����������롣\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                break;

        }
    }
    freeQueue(bankQueue);
    freeRecords(recordHead);
    free(tellers);
}

