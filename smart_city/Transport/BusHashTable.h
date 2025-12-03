#pragma once
#include "Bus.h"
#include <string>
using namespace std;

class BusNode {
public:
    Bus* data;
    BusNode* next;
    BusNode(Bus* p) : data(p), next(nullptr) {}
    ~BusNode() { delete data; }
};

class BusHashTable {
public:
    BusNode** table;
    int tableSize;

    BusHashTable(int size = 10) : tableSize(size) {
        table = new BusNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;
    }

    int hash(const string& cnic) {
        long long hashValue = 0;
        int primeNumber = 31;
        for (char c : cnic) hashValue = (hashValue * primeNumber + c) % tableSize;
        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(Bus* bus) {
        int index = hash(bus->busNum);
        BusNode* newNode = new BusNode(bus);
        if (!table[index]) table[index] = newNode;
        else {
            BusNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    Bus* search(const string& num) {
        int index = hash(num);
        BusNode* current = table[index];
        while (current) {
            if (current->data->busNum == num) return current->data;
            current = current->next;
        }
        return nullptr;
    }

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
                int index = hash(current->data->busNum);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }
        delete[] oldTable;
    }

    ~BusHashTable() {
        for (int i = 0; i < tableSize; i++) {
            BusNode* current = table[i];
            while (current) {
                BusNode* toDelete = current;
                current = current->next;
                delete toDelete; // deletes Person* automatically via ~BusNode
            }
        }
        delete[] table;
    }
};
