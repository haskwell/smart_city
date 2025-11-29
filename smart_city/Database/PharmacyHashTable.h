#pragma once
#include "../Medicine/HospitalEntities.h"
#include <string>
using namespace std;

class PharmacyNode {
public:
    Pharmacy data;
    PharmacyNode* next;
    PharmacyNode(Pharmacy p) : data(p), next(nullptr) {}
};

class PharmacyHashTable {
public:
    PharmacyNode** table;
    int tableSize;

    PharmacyHashTable(int size = 10) : tableSize(size) {
        table = new PharmacyNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;
    }

    int hash(const string& pharmacyID) {
        long long hashValue = 0;
        int primeNumber = 31;
        for (char c : pharmacyID) hashValue = (hashValue * primeNumber + c) % tableSize;
        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(Pharmacy phar) {
        int index = hash(phar.id);
        PharmacyNode* newNode = new PharmacyNode(phar);
        if (!table[index]) table[index] = newNode;
        else {
            PharmacyNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    Pharmacy* search(const string& pharmacyID) {
        int index = hash(pharmacyID);
        PharmacyNode* current = table[index];
        while (current) {
            if (current->data.id == pharmacyID) return &current->data;
            current = current->next;
        }
        return nullptr;
    }

    void resize(int newSize) {
        PharmacyNode** oldTable = table;
        int oldSize = tableSize;
        tableSize = newSize;
        table = new PharmacyNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            PharmacyNode* current = oldTable[i];
            while (current) {
                PharmacyNode* nextNode = current->next;
                int index = hash(current->data.id);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }
        delete[] oldTable;
    }

    ~PharmacyHashTable() {
        for (int i = 0; i < tableSize; i++) {
            PharmacyNode* current = table[i];
            while (current) {
                PharmacyNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }
};
