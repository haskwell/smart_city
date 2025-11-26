#pragma once
#include "HospitalEntities.h"

class MedicineNode {
public:
    Medicine data;
    MedicineNode* next;

    MedicineNode(Medicine b) : data(b), next(nullptr) {}
};

class MedicineHashTable {
public:
    MedicineNode** table;
    int tableSize;

    MedicineHashTable() : table(nullptr), tableSize(0) {}

    void setUptable(int size) {
        tableSize = size;
        table = new MedicineNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int hash(string busNo) { return 0; }

    void insert(Medicine b) {}

    Medicine* search(string busNo) { return 0; }

    ~MedicineHashTable() {
        for (int i = 0; i < tableSize; i++) {
            delete[]table[i];
        }
        delete[]table;
    }
};