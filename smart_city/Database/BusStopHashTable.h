#pragma once
#include "../Transport/BusStop.h"
#include <string>
using namespace std;

class BusStopNode {
public:
    BusStop data;
    BusStopNode* next;

    BusStopNode(const BusStop& bs) : data(bs), next(nullptr) {}
};

class BusStopHashTable {
public:
    BusStopNode** table;
    int tableSize;

    // Constructor initializes the table directly
    BusStopHashTable(int size = 10) : tableSize(size) {
        table = new BusStopNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int hash(const string& busStopId) {
        if (tableSize == 0) return 0;

        long long hashValue = 0;
        int primeNumber = 29;

        for (char c : busStopId) {
            hashValue = (hashValue * primeNumber + c) % tableSize;
        }

        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(const BusStop& bs) {
        int index = hash(bs.stopId);
        BusStopNode* newNode = new BusStopNode(bs);

        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            BusStopNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    BusStop* search(const string& stopId) {
        int index = hash(stopId);
        BusStopNode* current = table[index];

        while (current) {
            if (current->data.stopId == stopId) return &current->data;
            current = current->next;
        }

        return nullptr;
    }

    // Resize function: doubles table size and rehashes all companies
    void resize(int newSize) {
        BusStopNode** oldTable = table;
        int oldSize = tableSize;

        tableSize = newSize;
        table = new BusStopNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            BusStopNode* current = oldTable[i];
            while (current) {
                BusStopNode* nextNode = current->next;
                int index = hash(current->data.stopId);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }

        delete[] oldTable; // delete old array, nodes reused
    }

    ~BusStopHashTable() {
        for (int i = 0; i < tableSize; i++) {
            BusStopNode* current = table[i];
            while (current) {
                BusStopNode* prev = current;
                current = current->next;
                delete prev;
            }
        }
        delete[] table;
    }
};
