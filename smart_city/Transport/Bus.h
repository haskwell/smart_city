#pragma once
#include <string>
#include "PassengerQueue.h"
#include "BusRouteList.h"
using namespace std;
class Bus {
public:
	string busNum;
	string company;

	int currentStop;

	BusRouteList list;

	PassengerQueue queue;

	Bus(string n, string c, int s) : busNum(n), company(c), currentStop(s) {}
};