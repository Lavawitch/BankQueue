#include <cstdio>
#include "Customer.h"
#include <fstream>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>


void saveCustomerToFile(const Customer* customer, const char* filename);
Customer* loadCustomerFromFile(const char* filename);
void loadData(const char* customersFile, Queue* bankQueue);
bool clearFileContent(const std::string& filename);
bool updateCustomerData(const char* filename, const Customer* customer);
Customer* findCustomer(const char* filename, const char* customerId);
bool updateCustomerDataEfficiently(const char* filename, const Customer* customer);
void PrintFile(const char* customersFile);
//void updateCustomer(const char* filename, const Customer* customer);
//void openf();
