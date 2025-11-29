#pragma once
#include "Medicine.h"

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

    int hash(string med) {
        long long hashValue = 0;
        int primeNumber = 17; // prime base

        for (int i = 0; i < med.length(); i++) {
            hashValue = (hashValue * primeNumber + med[i]) % tableSize;
        }

        return hashValue;
    }

    // Insert a medicine into the table
    void insert(Medicine med) {
        int index = hash(med.name);

        MedicineNode* medNode = new MedicineNode(med);

        if (table[index] == nullptr) {
            table[index] = medNode;
        }
        else { // collision ? append to linked list
            MedicineNode* temp = table[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = medNode;
        }
    }

    // Search a medicine by name
    Medicine* search(string med) {
        int index = hash(med);

        MedicineNode* current = table[index];

        while (current != nullptr) {
            if (current->data.name == med) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    // Destructor to free memory
    ~MedicineHashTable() {
        for (int i = 0; i < tableSize; i++) {
            MedicineNode* current = table[i];
            while (current != nullptr) {
                MedicineNode* prev = current;
                current = current->next;
                delete prev;
            }
        }
        delete[] table;
    }
};