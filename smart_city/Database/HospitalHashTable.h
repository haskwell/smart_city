#pragma once
#include "../Medicine/HospitalEntities.h"

class HospitalNode {

public:
	Hospital data;
	HospitalNode* next;
	HospitalNode(Hospital h) : data(h), next(nullptr) {}
};

class HospitalHashTable {
public:
	HospitalNode** table;
	int tableSize;

	HospitalHashTable() : table(nullptr), tableSize(0) {}

	void setUptable(int size) {
		tableSize = size;
		table = new HospitalNode * [tableSize];
		for (int i = 0; i < tableSize; i++) {
			table[i] = nullptr;
		}
	}
	int hash(string hospitalID) {
		if (tableSize == 0)
		{
			return 0; // Safety check
		}
		long long hashValue = 0;
		int primeNumber = 31;

		for (int i = 0; i < hospitalID.length(); i++) {
			hashValue = (hashValue * primeNumber + hospitalID[i]) % tableSize;
		}
		// Ensure result is positive
		return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
	}
	// 2. Insert Function (Tail Insertion)
	void insert(Hospital Hos) {

	}

	Hospital* search(string hospitalID) {

	}

	~HospitalHashTable() {
		for (int i = 0; i < tableSize; i++) {
			HospitalNode* current = table[i];
			while (current != nullptr) {
				HospitalNode* toDelete = current;
				current = current->next;
				delete toDelete;
			}
		}
		delete[] table;
		table = nullptr;
	}
};
