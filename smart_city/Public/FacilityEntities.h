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
	string sector;

	Facility(string t = "", string i = "", string n = "", string s = "") : type(t), id(i), name(n), sector(s), latitude(0.0), longitude(0.0) {}
};