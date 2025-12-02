#pragma once
#include "ProductHashTable.h"

class Mall {
public:
	string mallId;
	string name;
	string sector;

	ProductHashTable productTable;

	Mall(string id = "", string n = "", string s = "")
		: mallId(id), name(n), sector(s)
	{
	}

	//void insertProduct(Product p){}
	//void searchProduct(Product p){}
	//void searchCategory(Product p, string category){}

};