#pragma once
#include "../Transport/Bus.h"
#include <string>
using namespace std;

class BusNode {
public:
    Bus data;
    BusNode* next;

    BusNode(Bus b) : data(b), next(nullptr) {}
};

class BusHashTable {
public:
    BusNode** table;
    int tableSize;

    // Constructor initializes the table directly
    BusHashTable(int size = 10) : tableSize(size) {
        table = new BusNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    long long hash(const string& busNo) {
        if (tableSize == 0) return 0;

        long long hashValue = 0;
        int primeNumber = 17;

        for (char c : busNo) {
            hashValue = (hashValue * primeNumber + c) % tableSize;
        }

        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(Bus b) {
        int index = hash(b.busNum);
        BusNode* newNode = new BusNode(b);

        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            BusNode* temp = table[index];
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }
    }

    Bus* search(const string& busNo) {
        int index = hash(busNo);
        BusNode* current = table[index];

        while (current) {
            if (current->data.busNum == busNo) return &(current->data);
            current = current->next;
        }
        return nullptr;
    }

    // Resize function: doubles table size and rehashes all elements
    void resize(int newSize) {
        BusNode** oldTable = table;
        int oldSize = tableSize;

        tableSize = newSize;
        table = new BusNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            BusNode* current = oldTable[i];
            while (current) {
                BusNode* nextNode = current->next;
                int index = hash(current->data.busNum);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }

        delete[] oldTable; // Only delete the old array, nodes are reused
    }

    ~BusHashTable() {
        for (int i = 0; i < tableSize; i++) {
            BusNode* current = table[i];
            while (current) {
                BusNode* prev = current;
                current = current->next;
                delete prev;
            }
        }
        delete[] table;
    }
};
