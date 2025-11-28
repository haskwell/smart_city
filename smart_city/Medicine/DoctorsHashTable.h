#pragma once
#include "../Population/PopulationEntities.h"

class DoctorNode {
public:
    Person data;
    DoctorNode* next;

    DoctorNode(Person b) : data(b), next(nullptr) {}
};

class DoctorsHashTable {
public:
    DoctorNode** table;
    int tableSize;

    DoctorsHashTable() : table(nullptr), tableSize(0) {}

    void setUptable(int size) {
        tableSize = size;
        table = new DoctorNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

	// Simple hash function based on the doctor's name using polynomial hashing
    int hash(string doc) { 
        
		long long hashValue = 0;
		int primeNumber = 17; // to reduce collisions
		long long addNumber = 10; // polynomial base

        for (int i = 0; i < doc.length(); i++)
        {
            hashValue = (hashValue * primeNumber + doc[i]) % tableSize;

            //hashValue += ((docName[i] - 'a' + 26) * addNumber) % tableSize;

			//addNumber = (addNumber * primeNumber) % tableSize;

        }

        return hashValue;
    }

    //insert doctor at empty space using hash value
    void insert(Person doc) {
        int index = hash(doc.name);

        DoctorNode* docNode = new DoctorNode(doc);

        if (table[index] == nullptr)
        {
            table[index] = docNode;
        }

        else //linked list
        {
            DoctorNode* temp = table[index];

            while (temp->next != nullptr)
            {
                temp = temp->next;
            }

            temp->next = docNode;
        }
    }

    Person* search(string doc) {
        int index = hash(doc);

        DoctorNode* current = table[index];

        while (current != nullptr)
        {
            if (current->data.name == doc)
            {
                return &(current->data);
            }
            current = current->next;

        }
        return nullptr;
    }

    /*~DoctorsHashTable() {
        for (int i = 0; i < tableSize; i++) {
            delete[]table[i];
        }
        delete[]table;
    }*/

    ~DoctorsHashTable() {
        for (int i = 0; i < tableSize; i++) 
        {
            DoctorNode* current = table[i];
            // Traverse the linked list and delete every node individually
            while (current != nullptr) {
                DoctorNode* prev = current;
                current = current->next;
                delete prev;
            }
        }
        // Finally, delete the array of pointers
        delete[] table;
    }
};