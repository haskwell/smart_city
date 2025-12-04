#pragma once
#include<string>

using namespace std;

class Facility
{
public:
	string type;
	string id;
	string name;
	double latitude;
	double longitude;

	Facility(string t = "", string i = "", string n = "") : type(t), id(i), name(n), latitude(0.0), longitude(0.0) {}
};