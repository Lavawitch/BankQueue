#include "Data.h"

/**
 * 清空文件内容的函数
 * @param filename 文件名
 * @return 成功返回true，失败返回false
 */
bool clearFileContent(const std::string& filename) {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file) {
        // 文件打开失败
        return false;
    }
    // 文件已打开，并且内容已被清空（因为使用了std::ios::trunc）
    return true;
}


void saveCustomerToFile(const Customer* customer, const char* filename) {
    FILE* file = fopen(filename, "a"); // 追加模式打开文件
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s:%s:%s:%d:%lf\n", customer->id, customer->name, customer->verificationCode, customer->selectedService,customer->amount);
    fclose(file);
}

Customer* loadCustomerFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("打开文件失败");
        return NULL;
    }
    Customer* head = NULL;
    Customer* current = NULL;
    Customer* temp = NULL;

    while (!feof(file)) {
        temp = (Customer*)malloc(sizeof(Customer));
        if (fscanf(file, "%19[^:]:%49[^:]:%6[^:]:%d:%lf", temp->id, temp->name, temp->verificationCode, &temp->selectedService,&temp->amount) != 5) {
            free(temp);
            continue;
        }
        temp->next = NULL;
        if (head == NULL) {
            head = temp;
            current = head;
        } else {
            current->next = temp;
            current = temp;
        }
    }
    fclose(file);
    return head;
}

void PrintFile(const char* customersFile){
    Customer* loadedCustomers = loadCustomerFromFile(customersFile);
    while(loadedCustomers!= NULL){
        printf("%s:%s:%s:%d:%lf\n", loadedCustomers->id, loadedCustomers->name, loadedCustomers->verificationCode,loadedCustomers->selectedService,loadedCustomers->amount);
        loadedCustomers = loadedCustomers->next;
    }
}

void loadData(const char* customersFile, Queue* bankQueue) {
    Customer* loadedCustomers = loadCustomerFromFile(customersFile);
    while (loadedCustomers!= NULL) {
        enqueue(bankQueue, loadedCustomers->id, loadedCustomers->name,loadedCustomers->verificationCode,loadedCustomers->selectedService,loadedCustomers->amount);
        loadedCustomers = loadedCustomers->next;
    }
}

/**
 * 更新指定用户的函数
 * @param filename 文件名
 * @param customer 要更新的客户信息
 * @return 成功返回true，失败返回false
 */
//void updateCustomer(const char* filename, const Customer* customer) {
  //  std::fstream file(filename, std::ios::in | std::ios::out | std::ios::app);
   /// if (!file) {
        // 文件打开失败
   //     return;
    //}

   // bool found = false;
   // char line[256];
   // std::string newLine;
  //  std::string searchId = customer->id;

    // 读取文件并查找指定用户
   // while (std::getline(file, line)) {
     //   std::string currentLine(line);
    //    if (currentLine.find(searchId) != std::string::npos) {
     //       found = true;
            // 构建新的行数据
    //        newLine = customer->id;
    //        newLine += ":";
     //       newLine += customer->name;
     //       newLine += ":";
     //       newLine += customer->verificationCode;
     //       newLine += ":";
     //       newLine += std::to_string(customer->selectedService);
     //       newLine += ":";
     //       newLine += std::to_string(customer->depositAmount);
     //       newLine += ":";
     //       newLine += std::to_string(customer->withdrawalAmount);
     //       newLine += "\n";
     //       break;
   //     }
 //   }

    // 如果找到用户，则更新数据
  //  if (found) {
     //   file.seekp(0); // 移动到文件开头
     //   bool updated = false;
     //   while (std::getline(file, line)) {
     //       std::string currentLine(line);
     //       if (currentLine.find(searchId) != std::string::npos && !updated) {
      //          file << newLine; // 写入新的行数据
      //          updated = true;
       //     } else {
       //         file << currentLine << "\n"; // 写入原始行数据
      //      }
//}
     //   if (!updated) {
      //      file << newLine << "\n"; // 如果用户在文件末尾，追加新的行数据
      //  }
   // }

   // file.close();
//}

/**
 * 查找指定用户
 * @param filename 文件名
 * @param customerId 用户ID
 * @return 找到返回Customer指针，未找到返回NULL
 */

 void freeCustomers(Customer* head) {
    Customer* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

 Customer* findCustomer(const char* filename, const char* customerId) {//BINGO!
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("打开文件失败");
        return NULL;
    }
    //Customer* customer = NULL;
    Customer* head = NULL;
    Customer* current = NULL;
    Customer* temp;

    while (1) {
        // 使用fgets读取一行，避免feof的问题
        char buffer[256];
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            // 到达文件末尾或读取错误
            break;
        }
        temp = (Customer*)malloc(sizeof(Customer));
        if (temp == NULL) {
            break; // 内存分配失败
        }
        // 使用sscanf解析行数据
        if (sscanf(buffer, "%19[^:]:%49[^:]:%6[^:]:%d:%lf",
                   temp->id, temp->name, temp->verificationCode,
                   &temp->selectedService, &temp->amount) == 5) {
            temp->next = NULL;
            if (strcmp(temp->id, customerId) == 0) {
                // 找到客户，释放之前创建的链表并返回这个客户
                if (head != NULL) {
                    freeCustomers(head); // 定义一个函数来释放链表
                }
                fclose(file);
                return temp;
            }
            // 如果不是目标客户，添加到链表
            if (head == NULL) {
                head = temp;
                current = head;
            } else {
                current->next = temp;
                current = temp;
            }
        } else {
            free(temp); // 解析失败，释放内存
        }
    }
    // 没有找到客户，释放链表内存并返回NULL
    if (head != NULL) {
        freeCustomers(head);
    }
    fclose(file);
    return NULL;
}

 Customer* findCustomer3(const char* filename, const char* customerId) {//也存在问题:(
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("打开文件失败");
        return NULL;
    }

    Customer* customer = NULL;
    Customer* temp = NULL;

    while (1) {
        temp = (Customer*)malloc(sizeof(Customer));
        if (temp == NULL) {
            perror("内存分配失败");
            fclose(file);
            return NULL;
        }

        if (fscanf(file, "%19[^:]:%49[^:]:%6[^:]:%d:%lf", temp->id, temp->name, temp->verificationCode, &temp->selectedService, &temp->amount)!= 5) {
            free(temp);
            if (feof(file)) {
                break; // 到达文件末尾，退出循环
            }
            continue;
        }

        if (strcmp(temp->id, customerId) == 0) {
            customer = temp;
            break;
        } else {
            free(temp); // 未找到匹配的客户，释放内存
        }
    }

    fclose(file);
    return customer;
}

Customer* findCustomer2(const char* filename, const char* customerId) {//存在一定问题
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("打开文件失败");
        return NULL;
    }
    Customer* customer = NULL;
    Customer* head = NULL;
    Customer* current = NULL;
    Customer* temp = NULL;

    while (!feof(file)) {
        temp = (Customer*)malloc(sizeof(Customer));
        if (fscanf(file, "%19[^:]:%49[^:]:%6[^:]:%d:%lf", temp->id, temp->name, temp->verificationCode, &temp->selectedService, &temp->amount) != 5) {
            free(temp);
            continue;
        }
        temp->next = NULL;
        if (strcmp(temp->id, customerId) == 0) {
            customer = temp; // 找到客户
            break;
        }
        if (head == NULL) {
            head = temp;
            current = head;
        } else {
            current->next = temp;
            current = temp;
        }
    }
    fclose(file);
    return customer;
}

/**
 * 更新指定用户的数据
 * @param filename 文件名
 * @param customer 要更新的客户信息
 * @return 成功返回true，失败返回false
 */


 bool updateCustomerData(const char* filename, const Customer* customer) {
    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    // 打开原文件并读取所有行
    std::ifstream file(filename);
    if (!file) {
        perror("打开文件失败");
        return false;
    }

    // 读取文件中的每一行，并查找需要更新的客户
    while (std::getline(file, line)) {
        if (line.find(customer->id) != std::string::npos) {
            // 找到客户，构建新的行数据
            std::string newLine = customer->id;
            newLine += ":";
            newLine += customer->name;
            newLine += ":";
            newLine += customer->verificationCode;
            newLine += ":";
            newLine += std::to_string(customer->selectedService);
            newLine += ":";
            newLine += std::to_string(customer->amount);
            newLine += "\n";
            lines.push_back(newLine); // 使用新的行数据替换旧的
            found = true;
        } else {
            line+="\n";
            lines.push_back(line); // 其他客户数据保持不变
        }
    }
    file.close();

    if (!found) {
        return false; // 未找到用户
    }

    // 将更新后的所有数据写回到文件中
    std::ofstream outFile(filename);
    if (!outFile) {
        perror("写入文件失败");
        return false;
    }
    for (const auto& it : lines) {
        outFile << it;
    }
    outFile.close();

    return true;
}


bool updateCustomerData3(const char* filename, const Customer* customer) {//有bug算法
    std::vector<std::string> lines;
    std::string line;
    std::string newLine;
    bool found = false;

    // 打开原文件并读取所有行
    std::ifstream file(filename);
    if (!file) {
        perror("打开文件失败");
        return false;
    }

    while (std::getline(file, line)) {
        // 检查当前行是否包含要更新的客户ID
        if (line.find(customer->id) != std::string::npos) {
            // 构建新的行数据
            newLine = customer->id;
            newLine += ":";
            newLine += customer->name;
            newLine += ":";
            newLine += customer->verificationCode;
            newLine += ":";
            newLine += std::to_string(customer->selectedService);
            newLine += ":";
            newLine += std::to_string(customer->amount);
            newLine += "\n";
            lines.push_back(newLine); // 使用新的行数据替换旧的
            found = true;
        } else {
            lines.push_back(line); // 保持其他行不变
        }
    }
    file.close();

    // 如果找到并更新了客户数据
    if (found) {
        // 创建临时文件
        std::string tempFilename = std::string(filename) + ".tmp";
        std::ofstream tempFile(tempFilename);

        // 将更新后的内容写入临时文件
        for (const auto& it : lines) {
            tempFile << it;
        }
        tempFile.close();

        // 替换原文件与临时文件
        if (remove(filename) == 0) {
            rename(tempFilename.c_str(), filename);
        } else {
            remove(tempFilename.c_str()); // 如果替换失败，删除临时文件
            return false;
        }
    } else {
        // 如果没有找到客户，返回失败
        return false;
    }

    return true;
}


bool updateCustomerData2(const char* filename, const Customer* customer) {//删除其他所有，只更新一个的杀敌一千自损八百算法
    // 首先查找用户
    Customer* foundCustomer = findCustomer(filename, customer->id);
    if (!foundCustomer) {
        return false; // 未找到用户
    }

    // 然后保存更新后的用户数据到文件
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("打开文件失败");
        return false;
    }
    // 写入更新后的客户数据
    fprintf(file, "%s:%s:%s:%d:%lf\n", customer->id, customer->name, customer->verificationCode, customer->selectedService, customer->amount);
    fclose(file);
    return true;
}
