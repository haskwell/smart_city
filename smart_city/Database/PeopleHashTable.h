#pragma once
#include "../Population/PopulationEntities.h"

class PersonNode {
	public:
	Person data;
	PersonNode* next;
	PersonNode(Person p) : data(p), next(nullptr) {}
};

class PeopleHashTable {
public:
	PersonNode** table;
	int tableSize;
	PeopleHashTable() : table(nullptr), tableSize(0) {}
	void setUptable(int size) {
		tableSize = size;
		table = new PersonNode * [tableSize];
		for (int i = 0; i < tableSize; i++) {
			table[i] = nullptr;
		}
	}
	int hash(string cnic) {
		if (tableSize == 0)
		{
			return 0; // Safety check
		}
		long long hashValue = 0;
		int primeNumber = 31;
		for (int i = 0; i < cnic.length(); i++) {
			hashValue = (hashValue * primeNumber + cnic[i]) % tableSize;
		}
		// Ensure result is positive
		return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
	}

	void insert(Person p) {

	}

	Person* search(string cnic) {

	}

	~PeopleHashTable() {
		for (int i = 0; i < tableSize; i++) {
			PersonNode* current = table[i];
			while (current != nullptr) {
				PersonNode* toDelete = current;
				current = current->next;
				delete toDelete;
			}
		}
		delete[] table;
		table = nullptr;
	}

};
