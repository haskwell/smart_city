#pragma once
#include "../Population/PopulationEntities.h"

class DoctorNode {
public:
    Person data;
    DoctorNode* next;

    DoctorNode(Person b) : data(b), next(nullptr) {}
};

class DoctorsHashTable {
public:
    DoctorNode** table;
    int tableSize;

    DoctorsHashTable() : table(nullptr), tableSize(0) {}

    void setUptable(int size) {
        tableSize = size;
        table = new DoctorNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int hash(string busNo) { return 0; }

    void insert(Person b) {}

    Person* search(string busNo) { return 0; }

    ~DoctorsHashTable() {
        for (int i = 0; i < tableSize; i++) {
            delete[]table[i];
        }
        delete[]table;
    }
};