#pragma once
#include "../Transport/BusCompany.h"
#include <string>
using namespace std;

class BusCompaniesNode {
public:
    BusCompany data;
    BusCompaniesNode* next;

    BusCompaniesNode(const BusCompany& bc) : data(bc), next(nullptr) {}
};

class BusCompaniesHashTable {
public:
    BusCompaniesNode** table;
    int tableSize;

    // Constructor initializes the table directly
    BusCompaniesHashTable(int size = 10) : tableSize(size) {
        table = new BusCompaniesNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int hash(const string& companyName) {
        if (tableSize == 0) return 0;

        long long hashValue = 0;
        int primeNumber = 29;

        for (char c : companyName) {
            hashValue = (hashValue * primeNumber + c) % tableSize;
        }

        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(const BusCompany& bc) {
        int index = hash(bc.companyName);
        BusCompaniesNode* newNode = new BusCompaniesNode(bc);

        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            BusCompaniesNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    BusCompany* search(const string& companyName) {
        int index = hash(companyName);
        BusCompaniesNode* current = table[index];

        while (current) {
            if (current->data.companyName == companyName) {
                return &current->data;
            }
            current = current->next;
        }

        return nullptr;
    }

    void insertBusToCompany(const string& companyName, Bus* b) {
        BusCompany* company = search(companyName);
        if (company) company->busTable.insert(b);
    }

    Bus* searchBusInCompany(const string& companyName, const string& busNum) {
        BusCompany* company = search(companyName);
        if (company) return company->busTable.search(busNum);
        return nullptr;
    }

    // Resize function: doubles table size and rehashes all companies
    void resize(int newSize) {
        BusCompaniesNode** oldTable = table;
        int oldSize = tableSize;

        tableSize = newSize;
        table = new BusCompaniesNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            BusCompaniesNode* current = oldTable[i];
            while (current) {
                BusCompaniesNode* nextNode = current->next;
                int index = hash(current->data.companyName);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }

        delete[] oldTable; // delete old array, nodes reused
    }

    ~BusCompaniesHashTable() {
        for (int i = 0; i < tableSize; i++) {
            BusCompaniesNode* current = table[i];
            while (current) {
                BusCompaniesNode* prev = current;
                current = current->next;
                delete prev;
            }
        }
        delete[] table;
    }
};
