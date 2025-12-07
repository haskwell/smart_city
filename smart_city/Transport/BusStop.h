#pragma once
#include <string>
#include "PassengerQueue.h"
using namespace std;

class BusStop {
	public:
	string name;
	string stopId;
	string sector;
	double latitude;
	double longitude;
		
	BusStop(string n = "", string id = "", string sectorName = "", double lat = 0.0f, double lon = 0.0f) : name(n), stopId(id), sector(sectorName), latitude(lat), longitude(lon) {}


};