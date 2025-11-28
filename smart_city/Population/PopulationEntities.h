#pragma once
#include <string>
using namespace std;

class Person {
public:
	string name;
	int age;
	char gender;
	string CNIC;
	string street;
	int houseNo;
	string occupation;

	Person(string n = "", int a = -99999, char g = 'M',
	string cnic = "", string s = "", int house = 0, string o = "") : name(n), age(a), gender(g)
	, CNIC(cnic), street(s), houseNo(house), occupation(o){ }
};


