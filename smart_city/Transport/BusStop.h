#pragma once
#include <string>
using namespace std;

class BusStop {
	public:
	string name;
	string stopId;
	float latitude;
	float longitude;
	BusStop() : name(""), stopId(""), latitude(0.0), longitude(0.0) {}
	BusStop(string n, string id, float lat, float lon) : name(n), stopId(id), latitude(lat), longitude(lon) {}
};