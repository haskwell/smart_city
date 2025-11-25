#pragma once
#include <string>
#include "PassengerQueue.h"
#include "BusRouteList.h"
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
	Bus* head;

	BusCompany(): companyName(""), head(nullptr) {}

	void registerName(string n) {
		companyName = n;
	}

	void addBus(const Bus &b) {

	}

	~BusCompany(){

	}
};