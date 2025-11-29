#pragma once
#include "Medicine.h"

class MedicineNode {
public:
    Medicine data;
    MedicineNode* next;

    MedicineNode(const Medicine& b) : data(b), next(nullptr) {}
};

class MedicineHashTable {
public:
    MedicineNode** table;
    int tableSize;

    // Constructor allocates table directly
    MedicineHashTable(int size = 101) : tableSize(size) {
        table = new MedicineNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    // Polynomial hash
    int hash(const string& med) {
        long long hashValue = 0;
        int primeNumber = 17;

        for (char c : med) {
            hashValue = (hashValue * primeNumber + c) % tableSize;
        }
        return hashValue;
    }

    // Insert a medicine
    void insert(const Medicine& med) {
        int index = hash(med.name);

        MedicineNode* medNode = new MedicineNode(med);

        if (!table[index]) {
            table[index] = medNode;
        }
        else {
            MedicineNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = medNode;
        }
    }

    // Search for a medicine by name
    Medicine* search(const string& medName) {
        int index = hash(medName);

        MedicineNode* current = table[index];
        while (current) {
            if (current->data.name == medName)
                return &current->data;
            current = current->next;
        }
        return nullptr;
    }

    // Destructor
    ~MedicineHashTable() {
        for (int i = 0; i < tableSize; i++) {
            MedicineNode* current = table[i];
            while (current) {
                MedicineNode* prev = current;
                current = current->next;
                delete prev;
            }
        }
        delete[] table;
    }
};
