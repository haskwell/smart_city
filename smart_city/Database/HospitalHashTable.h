#pragma once
#include "../Medicine/HospitalEntities.h"
#include <string>
using namespace std;

class HospitalNode {
public:
    Hospital data;
    HospitalNode* next;
    HospitalNode(const Hospital& h) : data(h), next(nullptr) {}
};

class HospitalHashTable {
public:
    HospitalNode** table;
    int tableSize;

    // Constructor initializes the table directly
    HospitalHashTable(int size = 10) : tableSize(size) {
        table = new HospitalNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int hash(const string& hospitalID) {
        if (tableSize == 0) return 0;

        long long hashValue = 0;
        int primeNumber = 31;

        for (char c : hospitalID) {
            hashValue = (hashValue * primeNumber + c) % tableSize;
        }

        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(const Hospital& hos) {
        int index = hash(hos.id);
        HospitalNode* newNode = new HospitalNode(hos);

        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            HospitalNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    Hospital* search(const string& hospitalID) {
        int index = hash(hospitalID);
        HospitalNode* current = table[index];

        while (current) {
            if (current->data.id == hospitalID) return &(current->data);
            current = current->next;
        }
        return nullptr;
    }

    // Resize function: doubles table size and rehashes all hospitals
    void resize(int newSize) {
        HospitalNode** oldTable = table;
        int oldSize = tableSize;

        tableSize = newSize;
        table = new HospitalNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            HospitalNode* current = oldTable[i];
            while (current) {
                HospitalNode* nextNode = current->next;
                int index = hash(current->data.id);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }

        delete[] oldTable; // delete old array, nodes reused
    }

    ~HospitalHashTable() {
        for (int i = 0; i < tableSize; i++) {
            HospitalNode* current = table[i];
            while (current) {
                HospitalNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
        table = nullptr;
    }
};
