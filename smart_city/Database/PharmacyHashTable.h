#pragma once
#include "../Medicine/HospitalEntities.h"

class PharmacyNode {
	public:
	Pharmacy data;
	PharmacyNode* next;
	PharmacyNode(Pharmacy p) : data(p), next(nullptr) {}
};

class PharmacyHashTable {	
	public:
	PharmacyNode** table;
	int tableSize;
	PharmacyHashTable() : table(nullptr), tableSize(0) {}
	void setUptable(int size) {
		tableSize = size;
		table = new PharmacyNode * [tableSize];
		for (int i = 0; i < tableSize; i++) {
			table[i] = nullptr;
		}
	}
	int hash(string pharmacyID) {
		if (tableSize == 0)
		{
			return 0; // Safety check
		}
		long long hashValue = 0;
		int primeNumber = 31;
		for (int i = 0; i < pharmacyID.length(); i++) {
			hashValue = (hashValue * primeNumber + pharmacyID[i]) % tableSize;
		}
		// Ensure result is positive
		return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
	}
	// 2. Insert Function (Tail Insertion)
	void insert(Pharmacy phar) {
		int index = hash(phar.id);

		PharmacyNode* pharNode = new PharmacyNode(phar);

		if (table[index] == nullptr)
		{
			table[index] = pharNode;
		}
		else {
			PharmacyNode* temp = table[index];
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = pharNode;
		}
	}
	Pharmacy* search(string pharmacyID) {
		int index = hash(pharmacyID);

		PharmacyNode* current = table[index];
		
		while (current != nullptr) {
			if (current->data.id == pharmacyID) {
				return &current->data;
			}
			current = current->next;
		}
		return nullptr; 
	}
	~PharmacyHashTable() {
		for (int i = 0; i < tableSize; i++) {
			PharmacyNode* current = table[i];
			while (current != nullptr) {
				PharmacyNode* toDelete = current;
				current = current->next;
				delete toDelete;
			}
		}
		delete[] table;
		table = nullptr;
	}
};