#pragma once
#include <string>
using namespace std;

class BusStop {
	public:
	string name;
	string stopId;
	string sector;
	double latitude;
	double longitude;
	BusStop() : name(""), stopId(""), latitude(0.0), longitude(0.0), sector("") {}
	BusStop(string n, string id, string sectorName, double lat, double lon) : name(n), stopId(id),sector(sectorName), latitude(lat), longitude(lon) {}
};