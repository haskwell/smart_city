#pragma once
#include <string>
#include "../smart_city/Commercial/ProductHashTable.h"
using namespace std;


class Shop
{
public:
	string name;
	string id;
	ProductHashTable products;

	Shop(string n = "", string i = "") : name(n), id(i) {
		products = ProductHashTable();
	}
};

class ShopNode {
public:
		Shop data;
	ShopNode* next;
	ShopNode(Shop b) : data(b), next(nullptr) {}

};

class ShopHashTable {
	ShopNode** table;
	int tableSize;

public:
	ShopHashTable(int size = 101) : tableSize(size) {
		table = new ShopNode * [tableSize];
		for (int i = 0; i < tableSize; i++) {
			table[i] = nullptr;
		}
	}

	void setUptable(int size) {
		tableSize = size;
		table = new ShopNode * [tableSize];
		for (int i = 0; i < tableSize; i++) {
			table[i] = nullptr;
		}
	}
	int hash

};