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

    // Polynomial hash function based on patient name
    int hash(string patientName) {
        long long hashValue = 0;
        int primeNumber = 17; // prime base

        for (int i = 0; i < patientName.length(); i++) {
            hashValue = (hashValue * primeNumber + patientName[i]) % tableSize;
        }

        return hashValue;
    }

    // Insert a patient into the table
    void insert(Person patient) {
        int index = hash(patient.name);

        PatientNode* patientNode = new PatientNode(patient);

        if (table[index] == nullptr) {
            table[index] = patientNode;
        }
        else { // collision ? append to linked list
            PatientNode* temp = table[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = patientNode;
        }
    }

    // Search a patient by name
    Person* search(string patientName) {
        int index = hash(patientName);

        PatientNode* current = table[index];

        while (current != nullptr) {
            if (current->data.name == patientName) {
                return &(current->data);
            }
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
                delete prev;
            }
        }
        delete[] table;
    }
};