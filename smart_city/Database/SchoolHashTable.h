#pragma once
#include "../Education/EducationEntities.h"
#include <string>
using namespace std;

class SchoolNode {
public:
    School data;
    SchoolNode* next;
    SchoolNode(const School& s) : data(s), next(nullptr) {}
};

class SchoolHashTable {
public:
    SchoolNode** table;
    int tableSize;

    SchoolHashTable(int size = 10) : tableSize(size) {
        table = new SchoolNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;
    }

    int hash(const string& schoolID) {
        long long hashValue = 0;
        int primeNumber = 31;
        for (char c : schoolID) hashValue = (hashValue * primeNumber + c) % tableSize;
        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(const School& school) {
        int index = hash(school.schoolID);
        SchoolNode* newNode = new SchoolNode(school);
        if (!table[index]) table[index] = newNode;
        else {
            SchoolNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    School* search(const string& schoolID) {
        int index = hash(schoolID);
        SchoolNode* current = table[index];
        while (current) {
            if (current->data.schoolID == schoolID) return &current->data;
            current = current->next;
        }
        return nullptr;
    }

    void resize(int newSize) {
        SchoolNode** oldTable = table;
        int oldSize = tableSize;
        tableSize = newSize;
        table = new SchoolNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            SchoolNode* current = oldTable[i];
            while (current) {
                SchoolNode* nextNode = current->next;
                int index = hash(current->data.schoolID);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }
        delete[] oldTable;
    }

    ~SchoolHashTable() {
        for (int i = 0; i < tableSize; i++) {
            SchoolNode* current = table[i];
            while (current) {
                SchoolNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }
};
