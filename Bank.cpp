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
    system("cls"); // 清屏
    //Customer* loadedCustomers = NULL; // 将变量初始化移到 switch 之外
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
        printf("\t     < 银行排队系统菜单 >\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        PrintSeparator();
        // Print menu items with decorative lines
        printf("║        1. 用户                              ║\n");
        PrintDecorativeLine();
        printf("║        2. 柜台业务员                        ║\n");
        PrintDecorativeLine();
        printf("║        3. 查看数据文件                      ║\n");
        PrintDecorativeLine();
        printf("║        4. 清空数据文件                      ║\n");
        PrintDecorativeLine();
        printf("║        5. 退出                              ║\n");
        // Print bottom frame
        PrintBottomSeparator();
        printf("请选择操作：");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                while (1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_CYAN);
                    printf("\t\t< 用户操作菜单 >\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                    PrintSeparator();
                    printf("║        1. 新用户进行开户                    ║\n");
                    PrintDecorativeLine();
                    printf("║        2. 已开户用户选择业务                ║\n");
                    PrintDecorativeLine();
                    printf("║        3. 查看排队情况                      ║\n");
                    PrintDecorativeLine();
                    printf("║        4. 返回上级菜单                      ║\n");
                    PrintBottomSeparator();
                    printf("请选择操作：");
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
                        printf("无效选择，请重新输入。\n");
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                    }
                }
            case 2:
                while (1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_CYAN );
                    printf("\t   < 柜台业务员操作菜单 >\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE );
                    PrintSeparator();
                    printf("║        1. 准备用户所办业务                  ║\n");
                    PrintDecorativeLine();
                    printf("║        2. 呼叫用户办理业务                  ║\n");
                    PrintDecorativeLine();
                    printf("║        3. 查看交易记录                      ║\n");
                    PrintDecorativeLine();
                    printf("║        4. 返回上级菜单                      ║\n");
                    PrintBottomSeparator();
                    printf("请选择操作：");
                    scanf("%d", &subChoice);
                    system("cls");

                    switch (subChoice) {
                        case 2:
                            callCustomer(bankQueue, tellers, numTellers, &recordHead);
                            break;
                        case 1:
                            if (isEmpty(bankQueue)) {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                                printf("队列中没有客户。\n");
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
                            printf("无效选择，请重新输入。\n");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                    }
                }
            case 3:
                // 加载数据文件
                //loadData("customers.csv", bankQueue);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
                printf("输入管理员密码以查看数据文件：");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                scanf("%s", inputPassword);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
                if (strcmp(inputPassword,adminPassword)==0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    printf("输入正确\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_HBLUE);
                    printf("正在加载数据文件……\n");
                    Sleep(400);
                    printf("数据存储格式(编号：姓名：验证码：业务选项：账户余额)\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("请注意，验证码和业务选项具有时效性，只记录上一次用户操作；用户姓名可以相同，但其编号唯一，不可更改\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_MAGENTA|FOREGROUND_INTENSITY);
                    PrintFile("customers.csv");
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("密码错误，无法查看数据文件。\n");
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                break;
            case 4:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GOLD);
                printf("输入管理员密码以清空数据文件：");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                scanf("%s", inputPassword);
                if (strcmp(inputPassword,adminPassword)==0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    printf("输入正确\n");
                    if (clearFileContent("customers.csv")) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                        printf("文件内容已清空。\n");
                    } else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                        printf("清空文件内容失败。\n");
                    }
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("密码错误，无法清空数据文件。\n");
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
                printf("无效选择，请重新输入。\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                break;

        }
    }
    freeQueue(bankQueue);
    freeRecords(recordHead);
    free(tellers);
}

