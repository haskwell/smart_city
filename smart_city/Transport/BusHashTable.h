#pragma once
#include "Bus.h"

class BusNode {
public:
    Bus data;
    BusNode* next;

    BusNode(Bus b): data(b), next(nullptr) {}
};

class BusHashTable {
public:
    BusNode** table;
    int tableSize;

    BusHashTable(): table(nullptr), tableSize(0) {}

    void setUptable(int size) {
        tableSize = size;
        table = new BusNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int hash(string busNo) { return 0; }

    void insert(Bus b) {}

    Bus* search(string busNo) { return 0; }

    ~BusHashTable() {
        for (int i = 0; i < tableSize; i++) {
            delete[]table[i];
        }
        delete[]table;
    }
};