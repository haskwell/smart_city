#pragma once
#include <string>
#include "BusHashTable.h"

using namespace std;

class BusCompany {
public:
	string companyName;
	BusHashTable busTable;

	BusCompany(string name = "") : companyName(name) {}
};