#include "Data.h"

/**
 * ����ļ����ݵĺ���
 * @param filename �ļ���
 * @return �ɹ�����true��ʧ�ܷ���false
 */
bool clearFileContent(const std::string& filename) {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file) {
        // �ļ���ʧ��
        return false;
    }
    // �ļ��Ѵ򿪣����������ѱ���գ���Ϊʹ����std::ios::trunc��
    return true;
}


void saveCustomerToFile(const Customer* customer, const char* filename) {
    FILE* file = fopen(filename, "a"); // ׷��ģʽ���ļ�
    if (file == NULL) {
        perror("���ļ�ʧ��");
        return;
    }
    fprintf(file, "%s:%s:%s:%d:%lf\n", customer->id, customer->name, customer->verificationCode, customer->selectedService,customer->amount);
    fclose(file);
}

Customer* loadCustomerFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("���ļ�ʧ��");
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
 * ����ָ���û��ĺ���
 * @param filename �ļ���
 * @param customer Ҫ���µĿͻ���Ϣ
 * @return �ɹ�����true��ʧ�ܷ���false
 */
//void updateCustomer(const char* filename, const Customer* customer) {
  //  std::fstream file(filename, std::ios::in | std::ios::out | std::ios::app);
   /// if (!file) {
        // �ļ���ʧ��
   //     return;
    //}

   // bool found = false;
   // char line[256];
   // std::string newLine;
  //  std::string searchId = customer->id;

    // ��ȡ�ļ�������ָ���û�
   // while (std::getline(file, line)) {
     //   std::string currentLine(line);
    //    if (currentLine.find(searchId) != std::string::npos) {
     //       found = true;
            // �����µ�������
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

    // ����ҵ��û������������
  //  if (found) {
     //   file.seekp(0); // �ƶ����ļ���ͷ
     //   bool updated = false;
     //   while (std::getline(file, line)) {
     //       std::string currentLine(line);
     //       if (currentLine.find(searchId) != std::string::npos && !updated) {
      //          file << newLine; // д���µ�������
      //          updated = true;
       //     } else {
       //         file << currentLine << "\n"; // д��ԭʼ������
      //      }
//}
     //   if (!updated) {
      //      file << newLine << "\n"; // ����û����ļ�ĩβ��׷���µ�������
      //  }
   // }

   // file.close();
//}

/**
 * ����ָ���û�
 * @param filename �ļ���
 * @param customerId �û�ID
 * @return �ҵ�����Customerָ�룬δ�ҵ�����NULL
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
        perror("���ļ�ʧ��");
        return NULL;
    }
    //Customer* customer = NULL;
    Customer* head = NULL;
    Customer* current = NULL;
    Customer* temp;

    while (1) {
        // ʹ��fgets��ȡһ�У�����feof������
        char buffer[256];
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            // �����ļ�ĩβ���ȡ����
            break;
        }
        temp = (Customer*)malloc(sizeof(Customer));
        if (temp == NULL) {
            break; // �ڴ����ʧ��
        }
        // ʹ��sscanf����������
        if (sscanf(buffer, "%19[^:]:%49[^:]:%6[^:]:%d:%lf",
                   temp->id, temp->name, temp->verificationCode,
                   &temp->selectedService, &temp->amount) == 5) {
            temp->next = NULL;
            if (strcmp(temp->id, customerId) == 0) {
                // �ҵ��ͻ����ͷ�֮ǰ������������������ͻ�
                if (head != NULL) {
                    freeCustomers(head); // ����һ���������ͷ�����
                }
                fclose(file);
                return temp;
            }
            // �������Ŀ��ͻ�����ӵ�����
            if (head == NULL) {
                head = temp;
                current = head;
            } else {
                current->next = temp;
                current = temp;
            }
        } else {
            free(temp); // ����ʧ�ܣ��ͷ��ڴ�
        }
    }
    // û���ҵ��ͻ����ͷ������ڴ沢����NULL
    if (head != NULL) {
        freeCustomers(head);
    }
    fclose(file);
    return NULL;
}

 Customer* findCustomer3(const char* filename, const char* customerId) {//Ҳ��������:(
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("���ļ�ʧ��");
        return NULL;
    }

    Customer* customer = NULL;
    Customer* temp = NULL;

    while (1) {
        temp = (Customer*)malloc(sizeof(Customer));
        if (temp == NULL) {
            perror("�ڴ����ʧ��");
            fclose(file);
            return NULL;
        }

        if (fscanf(file, "%19[^:]:%49[^:]:%6[^:]:%d:%lf", temp->id, temp->name, temp->verificationCode, &temp->selectedService, &temp->amount)!= 5) {
            free(temp);
            if (feof(file)) {
                break; // �����ļ�ĩβ���˳�ѭ��
            }
            continue;
        }

        if (strcmp(temp->id, customerId) == 0) {
            customer = temp;
            break;
        } else {
            free(temp); // δ�ҵ�ƥ��Ŀͻ����ͷ��ڴ�
        }
    }

    fclose(file);
    return customer;
}

Customer* findCustomer2(const char* filename, const char* customerId) {//����һ������
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("���ļ�ʧ��");
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
            customer = temp; // �ҵ��ͻ�
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
 * ����ָ���û�������
 * @param filename �ļ���
 * @param customer Ҫ���µĿͻ���Ϣ
 * @return �ɹ�����true��ʧ�ܷ���false
 */


 bool updateCustomerData(const char* filename, const Customer* customer) {
    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    // ��ԭ�ļ�����ȡ������
    std::ifstream file(filename);
    if (!file) {
        perror("���ļ�ʧ��");
        return false;
    }

    // ��ȡ�ļ��е�ÿһ�У���������Ҫ���µĿͻ�
    while (std::getline(file, line)) {
        if (line.find(customer->id) != std::string::npos) {
            // �ҵ��ͻ��������µ�������
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
            lines.push_back(newLine); // ʹ���µ��������滻�ɵ�
            found = true;
        } else {
            line+="\n";
            lines.push_back(line); // �����ͻ����ݱ��ֲ���
        }
    }
    file.close();

    if (!found) {
        return false; // δ�ҵ��û�
    }

    // �����º����������д�ص��ļ���
    std::ofstream outFile(filename);
    if (!outFile) {
        perror("д���ļ�ʧ��");
        return false;
    }
    for (const auto& it : lines) {
        outFile << it;
    }
    outFile.close();

    return true;
}


bool updateCustomerData3(const char* filename, const Customer* customer) {//��bug�㷨
    std::vector<std::string> lines;
    std::string line;
    std::string newLine;
    bool found = false;

    // ��ԭ�ļ�����ȡ������
    std::ifstream file(filename);
    if (!file) {
        perror("���ļ�ʧ��");
        return false;
    }

    while (std::getline(file, line)) {
        // ��鵱ǰ���Ƿ����Ҫ���µĿͻ�ID
        if (line.find(customer->id) != std::string::npos) {
            // �����µ�������
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
            lines.push_back(newLine); // ʹ���µ��������滻�ɵ�
            found = true;
        } else {
            lines.push_back(line); // ���������в���
        }
    }
    file.close();

    // ����ҵ��������˿ͻ�����
    if (found) {
        // ������ʱ�ļ�
        std::string tempFilename = std::string(filename) + ".tmp";
        std::ofstream tempFile(tempFilename);

        // �����º������д����ʱ�ļ�
        for (const auto& it : lines) {
            tempFile << it;
        }
        tempFile.close();

        // �滻ԭ�ļ�����ʱ�ļ�
        if (remove(filename) == 0) {
            rename(tempFilename.c_str(), filename);
        } else {
            remove(tempFilename.c_str()); // ����滻ʧ�ܣ�ɾ����ʱ�ļ�
            return false;
        }
    } else {
        // ���û���ҵ��ͻ�������ʧ��
        return false;
    }

    return true;
}


bool updateCustomerData2(const char* filename, const Customer* customer) {//ɾ���������У�ֻ����һ����ɱ��һǧ����˰��㷨
    // ���Ȳ����û�
    Customer* foundCustomer = findCustomer(filename, customer->id);
    if (!foundCustomer) {
        return false; // δ�ҵ��û�
    }

    // Ȼ�󱣴���º���û����ݵ��ļ�
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("���ļ�ʧ��");
        return false;
    }
    // д����º�Ŀͻ�����
    fprintf(file, "%s:%s:%s:%d:%lf\n", customer->id, customer->name, customer->verificationCode, customer->selectedService, customer->amount);
    fclose(file);
    return true;
}
