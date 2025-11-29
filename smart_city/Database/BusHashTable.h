#pragma once
#include "../Transport/Bus.h"

class BusNode {
public:
    Bus data;
    BusNode* next;

    BusNode(Bus b) : data(b), next(nullptr) {}
};

class BusHashTable {
public:
    BusNode** table;
    int tableSize;

    BusHashTable() : table(nullptr), tableSize(0) {}

    void setUptable(int size) {
        tableSize = size;
        table = new BusNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int hash(string busNo) {
        if (tableSize == 0) return 0; // Safety check

        long long hashValue = 0;
        int primeNumber = 17;

        for (int i = 0; i < busNo.length(); i++) {
            hashValue = (hashValue * primeNumber + busNo[i]) % tableSize;
        }

        // Ensure result is positive
        return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
    }

    // 2. Insert Function (Tail Insertion)
    void insert(Bus b) {
        // ASSUMPTION: Your Bus class has a 'busNo' member variable.
        // If it is named 'regNumber' or 'id', change 'b.busNo' below.
        int index = hash(b.busNum);

        BusNode* newNode = new BusNode(b);

        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            BusNode* temp = table[index];
            // Traverse to the end of the list
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // 3. Search Function
    Bus* search(string busNo) {
        int index = hash(busNo);
        BusNode* current = table[index];

        while (current != nullptr) {
            // Compare the key (busNo)
            if (current->data.busNum == busNo) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    // 4. Corrected Destructor
    ~BusHashTable() {
        if (table == nullptr) return;

        for (int i = 0; i < tableSize; i++) {
            BusNode* current = table[i];
            while (current != nullptr) {
                BusNode* prev = current;
                current = current->next;
                delete prev; // Delete individual nodes
            }
        }
        delete[] table; // Delete the array of pointers
    }
};