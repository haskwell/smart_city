#pragma once
#include "../Commercial/MallEntities.h"
#include <string>
using namespace std;

class MallNode {
public:
    Mall data;
    MallNode* next;
    MallNode(const Mall& m) : data(m), next(nullptr) {}
};

class MallHashTable {
public:
    MallNode** table;
    int tableSize;

    // Constructor initializes the table directly
    MallHashTable(int size = 10) : tableSize(size) {
        table = new MallNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int hash(const string& mallId) {
        if (tableSize == 0) return 0;

        long long hashValue = 0;
        int primeNumber = 31;

        for (char c : mallId) {
            hashValue = (hashValue * primeNumber + c) % tableSize;
        }

        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(const Mall& mall) {
        int index = hash(mall.mallId);
        MallNode* newNode = new MallNode(mall);

        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            MallNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    Mall* search(const string& hospitalID) {
        int index = hash(hospitalID);
        MallNode* current = table[index];

        while (current) {
            if (current->data.mallId == hospitalID) return &(current->data);
            current = current->next;
        }
        return nullptr;
    }

    // Resize function: doubles table size and rehashes all hospitals
    void resize(int newSize) {
        MallNode** oldTable = table;
        int oldSize = tableSize;

        tableSize = newSize;
        table = new MallNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            MallNode* current = oldTable[i];
            while (current) {
                MallNode* nextNode = current->next;
                int index = hash(current->data.mallId);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }

        delete[] oldTable; // delete old array, nodes reused
    }

    ~MallHashTable() {
        for (int i = 0; i < tableSize; i++) {
            MallNode* current = table[i];
            while (current) {
                MallNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
        table = nullptr;
    }
};
