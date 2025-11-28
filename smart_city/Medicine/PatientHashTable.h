#pragma once
#include "../Population/PopulationEntities.h"

class PatientNode {
public:
    Person data;
    PatientNode* next;

    PatientNode(Person b) : data(b), next(nullptr) {}
};

class PatientHashTable {
public:
    PatientNode** table;
    int tableSize;

    PatientHashTable() : table(nullptr), tableSize(0) {}

    void setUptable(int size) {
        tableSize = size;
        table = new PatientNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int hash(string busNo) { return 0; }

    void insert(Person b) {}

    Person* search(string busNo) { return 0; }

    ~PatientHashTable() {
        for (int i = 0; i < tableSize; i++) {
            delete[]table[i];
        }
        delete[]table;
    }
};