#pragma once
#include <string>
#include "PassengerQueue.h"
#include "BusRouteList.h"
#include "../Database/BusHashTable.h"
using namespace std;
class Bus {
public:
	string busNum;

	int currentStop;

	BusRouteList list;

	PassengerQueue queue;

	Bus(string n, int s) : busNum(n), currentStop(s) {}
};

class BusCompany {
public:
	string companyName;
	BusHashTable busTable;

	BusCompany(): companyName("") {}

	void registerName(string n) {
		companyName = n;
	}

	void addBus(const Bus &b) {

	}

	~BusCompany(){

	}
};