#pragma once
#include "../Population/PopulationEntities.h"

class Doctor : public Person {
public:
    string specialization;

    Doctor(string n = "",
        int a = -99999,
        char g = 'M',
        string cnic = "",
        string s = "",
        int house = 0,
        string o = "",
        string sec = "",
        string spec = "")
        : Person(n, a, g, cnic, s, house, o, sec),
        specialization(spec) {
    }
};

class DoctorNode {
public:
    Doctor* data;
    DoctorNode* next;

    DoctorNode(Doctor* b) : data(b), next(nullptr) {}
};

class DoctorsHashTable {
public:
    DoctorNode** table;
    int tableSize;

    // Constructor initializes table directly
    DoctorsHashTable(int size = 101) : tableSize(size) {
        table = new DoctorNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    // Simple hash function based on the doctor's name using polynomial hashing
    int hash(const string& doc) {
        long long hashValue = 0;
        int primeNumber = 17; // to reduce collisions

        for (char c : doc) {
            hashValue = (hashValue * primeNumber + c) % tableSize;
        }

        return hashValue;
    }

    // Insert doctor
    void insert(Doctor* doc) {
        int index = hash(doc->name);

        DoctorNode* docNode = new DoctorNode(doc);

        if (table[index] == nullptr) {
            table[index] = docNode;
        }
        else { // linked list
            DoctorNode* temp = table[index];
            while (temp->next != nullptr) temp = temp->next;
            temp->next = docNode;
        }
    }

    // Search doctor by name
    Doctor* search(const string& doc) {
        int index = hash(doc);
        DoctorNode* current = table[index];

        while (current != nullptr) {
            if (current->data->name == doc) return current->data;
            current = current->next;
        }
        return nullptr;
    }

    // Destructor
    ~DoctorsHashTable() {
        for (int i = 0; i < tableSize; i++) {
            DoctorNode* current = table[i];
            while (current != nullptr) {
                DoctorNode* prev = current;
                current = current->next;
                delete prev;
            }
        }
        delete[] table;
    }
};
