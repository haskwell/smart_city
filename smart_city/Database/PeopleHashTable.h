#pragma once
#include "../Population/PopulationEntities.h"
#include <string>
using namespace std;

class PersonNode {
public:
    Person* data;
    PersonNode* next;
    PersonNode(Person* p) : data(p), next(nullptr) {}
    ~PersonNode() { delete data; }
};

class PeopleHashTable {
public:
    PersonNode** table;
    int tableSize;

    PeopleHashTable(int size = 10) : tableSize(size) {
        table = new PersonNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;
    }

    int hash(const string& cnic) {
        long long hashValue = 0;
        int primeNumber = 31;
        for (char c : cnic) hashValue = (hashValue * primeNumber + c) % tableSize;
        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    void insert(Person* person) {
        int index = hash(person->CNIC);
        PersonNode* newNode = new PersonNode(person);
        if (!table[index]) table[index] = newNode;
        else {
            PersonNode* temp = table[index];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    Person* search(const string& cnic) {
        int index = hash(cnic);
        PersonNode* current = table[index];
        while (current) {
            if (current->data->CNIC == cnic) return current->data;
            current = current->next;
        }
        return nullptr;
    }

    void resize(int newSize) {
        PersonNode** oldTable = table;
        int oldSize = tableSize;
        tableSize = newSize;
        table = new PersonNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            PersonNode* current = oldTable[i];
            while (current) {
                PersonNode* nextNode = current->next;
                int index = hash(current->data->CNIC);
                current->next = table[index];
                table[index] = current;
                current = nextNode;
            }
        }
        delete[] oldTable;
    }

    ~PeopleHashTable() {
        for (int i = 0; i < tableSize; i++) {
            PersonNode* current = table[i];
            while (current) {
                PersonNode* toDelete = current;
                current = current->next;
                delete toDelete; // deletes Person* automatically via ~PersonNode
            }
        }
        delete[] table;
    }
};
