#pragma once
#include "../Education/EducationEntities.h"

class SchoolNode {
	public:
	School data;
	SchoolNode* next;
	SchoolNode(School s) : data(s), next(nullptr) {}
};

class SchoolHashTable {
public:
	SchoolNode** table;
	int tableSize;
	SchoolHashTable() : table(nullptr), tableSize(0) {}
	void setUptable(int size) {
		tableSize = size;
		table = new SchoolNode * [tableSize];
		for (int i = 0; i < tableSize; i++) {
			table[i] = nullptr;
		}
	}
	int hash(string schoolID) {
		if (tableSize == 0)
		{
			return 0; // Safety check
		}
		long long hashValue = 0;
		int primeNumber = 31;
		for (int i = 0; i < schoolID.length(); i++) {
			hashValue = (hashValue * primeNumber + schoolID[i]) % tableSize;
		}
		// Ensure result is positive
		return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
	}

	void insert(School school) {

	}

	School* search(string schoolID) {
	}

	~SchoolHashTable() {
		for (int i = 0; i < tableSize; i++) {
			SchoolNode* current = table[i];
			while (current != nullptr) {
				SchoolNode* toDelete = current;
				current = current->next;
				delete toDelete;
			}
		}
		delete[] table;
		table = nullptr;
	}

};