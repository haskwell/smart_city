#pragma once
#include "../Population/PopulationEntities.h"
#include <string>
using namespace std;

class SectorNode {
public:
    Sector data;
    SectorNode* next;
    SectorNode(const Sector& s) : data(s), next(nullptr) {}
};

class SectorHashTable {
public:
    SectorNode** table;
    int tableSize;

    SectorHashTable(int size = 10) : tableSize(size) {
        table = new SectorNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;
    }

    int hash(const string& SectorID) {
        long long hashValue = 0;
        int primeNumber = 31;
        for (char c : SectorID) hashValue = (hashValue * primeNumber + c) % tableSize;
        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(const Sector& Sector) {
        int index = hash(Sector.name);
        SectorNode* newNode = new SectorNode(Sector);
        if (!table[index]) table[index] = newNode;
        else {
            SectorNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    Sector* search(const string& name) {
        int index = hash(name);
        SectorNode* current = table[index];
        while (current) {
            if (current->data.name == name) return &current->data;
            current = current->next;
        }
        return nullptr;
    }

    void resize(int newSize) {
        SectorNode** oldTable = table;
        int oldSize = tableSize;
        tableSize = newSize;
        table = new SectorNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            SectorNode* current = oldTable[i];
            while (current) {
                SectorNode* nextNode = current->next;
                int index = hash(current->data.name);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }
        delete[] oldTable;
    }

    ~SectorHashTable() {
        for (int i = 0; i < tableSize; i++) {
            SectorNode* current = table[i];
            while (current) {
                SectorNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }
};
