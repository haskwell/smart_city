#pragma once
#include<string>

using namespace std;

class Facility
{
public:
	string type;
	string id;
	string name;

	Facility(string t = "", string i = "", string n = "") : type(t), id(i), name(n) {}
};