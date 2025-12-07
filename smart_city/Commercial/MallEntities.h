#pragma once
#include "ProductHashTable.h"

class Mall {
public:
	string mallId;
	string name;
	string sector;
	ProductHashTable productTable;
	double latitude = 0;
	double longitude = 0;

	Mall(string id = "", string n = "", string s = "")
		: mallId(id), name(n), sector(s)
	{
	}


};