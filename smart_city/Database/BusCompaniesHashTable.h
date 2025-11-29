#pragma once
#include "../Transport/Bus.h"
#include "BusHashTable.h"

class BusCompaniesNode {
	
	public:
		BusHashTable busTable;
	BusCompany data;
	BusCompaniesNode* next;
	BusCompaniesNode(BusCompany bc) : data(bc), next(nullptr) {}
};

class BusCompaniesHashTable {
public:
	BusCompaniesNode** table;
	int tableSize;
	BusCompaniesHashTable() : table(nullptr), tableSize(0) {}
	void setUptable(int size) {
		tableSize = size;
		table = new BusCompaniesNode * [tableSize];
		for (int i = 0; i < tableSize; i++) {
			table[i] = nullptr;
		}
	}
	int hash(string companyName) {
		if (tableSize == 0)
		{
			return 0; // Safety check
		}
		long long hashValue = 0;
		int primeNumber = 29;
		for (int i = 0; i < companyName.length(); i++) {
			hashValue = (hashValue * primeNumber + companyName[i]) % tableSize;
		}
		// Ensure result is positive
		return (hashValue < 0) ? (hashValue + tableSize) : hashValue;
	}
	// 2. Insert Function (Tail Insertion)
	void insert(BusCompany bc) {
		int index = hash(bc.companyName);;
		BusCompaniesNode* bcNode = new BusCompaniesNode(bc);
		if (table[index] == nullptr)
		{
			table[index] = bcNode;
		}
		else {
			BusCompaniesNode* temp = table[index];
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = bcNode;
		}
	}

	BusCompany* search(string companyName) {
		int index = hash(companyName);
		BusCompaniesNode* current = table[index];
		while (current != nullptr) {
			if (current->data.companyName == companyName) {
				return &current->data;
			}
			current = current->next;
		}
		// If not found, return a default BusCompany object
		return nullptr;
	}

	void insertBusToCompany(string companyName, Bus b) {
		BusCompany* company = search(companyName);
		if (company != nullptr) {
			company->addBus(b);
		}
	}
};
