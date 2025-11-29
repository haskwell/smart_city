#pragma once
#include "../Population/PopulationEntities.h"

class PatientNode {
public:
    Person* data;
    PatientNode* next;

    PatientNode(Person* p) : data(p), next(nullptr) {}
    ~PatientNode() { delete data; }
};

class PatientHashTable {
public:
    PatientNode** table;
    int tableSize;

    // Constructor allocates table directly
    PatientHashTable(int size = 101) : tableSize(size) {
        table = new PatientNode * [tableSize];
        for (int i = 0; i < tableSize; i++) table[i] = nullptr;
    }

    // Polynomial hash function based on patient name
    int hash(const string& patientName) {
        long long hashValue = 0;
        int primeNumber = 17; // prime base

        for (char c : patientName) {
            hashValue = (hashValue * primeNumber + c) % tableSize;
        }

        return hashValue;
    }

    // Insert a patient into the table
    void insert(Person* patient) {
        int index = hash(patient->name);

        PatientNode* patientNode = new PatientNode(patient);

        if (table[index] == nullptr) {
            table[index] = patientNode;
        }
        else { // linked list
            PatientNode* temp = table[index];
            while (temp->next != nullptr) temp = temp->next;
            temp->next = patientNode;
        }
    }

    // Search a patient by name
    Person* search(const string& patientName) {
        int index = hash(patientName);

        PatientNode* current = table[index];

        while (current != nullptr) {
            if (current->data->name == patientName) return current->data;
            current = current->next;
        }
        return nullptr;
    }

    // Destructor to free memory
    ~PatientHashTable() {
        for (int i = 0; i < tableSize; i++) {
            PatientNode* current = table[i];
            while (current != nullptr) {
                PatientNode* prev = current;
                current = current->next;
                delete prev; // deletes PatientNode, which deletes Person*
            }
        }
        delete[] table;
    }
};
