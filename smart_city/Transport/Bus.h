#pragma once
#include <string>
#include "PassengerQueue.h"
#include "BusRouteList.h"

using namespace std;

class Bus {
public:
	string busNum;

	string companyName;

	int currentStop;

	BusRouteList list;

	PassengerQueue queue;

	Bus(string n, string company) : busNum(n), companyName(company) {}
};
