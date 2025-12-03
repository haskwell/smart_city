#pragma once
#include<string>
#include"../Public/FacilityEntities.h"

using namespace std;

class FacilityNode
{
public:
	Facility data;
	FacilityNode* next;

	FacilityNode(const Facility& f) : data(f), next(nullptr) {}
};

class FacilityHashTable
{
public:

	FacilityNode** table;
	int tableSize;

	FacilityHashTable(int size = 10) : tableSize(size)
	{
		table = new FacilityNode * [tableSize];

		for (int i = 0; i < tableSize; i++)
		{
			table[i] = nullptr;
		}
	}

	int hash(const string& facilityID) {
		if (tableSize == 0) return 0;

		long long hashValue = 0;
		int primeNumber = 31;

		for (char c : facilityID) {
			hashValue = (hashValue * primeNumber + c) % tableSize;
		}

		return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
	}

	void insert(const Facility& fac) {
		int index = hash(fac.id); // Assuming Facility entity has an 'id' member
		FacilityNode* newNode = new FacilityNode(fac);

		if (table[index] == nullptr) {
			table[index] = newNode;
		}
		else {
			FacilityNode* temp = table[index];
			while (temp->next) temp = temp->next;
			temp->next = newNode;
		}
	}

	Facility* search(const string& facilityID) {
		int index = hash(facilityID);
		FacilityNode* current = table[index];

		while (current) {
			if (current->data.id == facilityID) return &(current->data);
			current = current->next;
		}
		return nullptr;
	}

	void resize(int newSize) {
		FacilityNode** oldTable = table;
		int oldSize = tableSize;

		tableSize = newSize;
		table = new FacilityNode * [tableSize];
		for (int i = 0; i < tableSize; i++) table[i] = nullptr;

		for (int i = 0; i < oldSize; i++) {
			FacilityNode* current = oldTable[i];
			while (current) {
				FacilityNode* nextNode = current->next;
				int index = hash(current->data.id);

				// Move node to new table (insert at head/prepend logic to save time)
				current->next = table[index];
				table[index] = current;

				current = nextNode;
			}
		}

		delete[] oldTable; // delete old array, nodes reused
	}

	~FacilityHashTable() {
		for (int i = 0; i < tableSize; i++) {
			FacilityNode* current = table[i];
			while (current) {
				FacilityNode* toDelete = current;
				current = current->next;
				delete toDelete;
			}
		}
		delete[] table;
		table = nullptr;
	}
};