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
	string sector;
	int houseNo;
	string occupation;
	Person* next;

	Person(string n = "", int a = -99999, char g = 'M',
		string cnic = "", string s = "", int house = 0, string o = "", string sec = "") : name(n), age(a), gender(g)
		, CNIC(cnic), street(s), houseNo(house), occupation(o), next(nullptr), sector(sec) {
	}

	virtual ~Person() {}
};

class House {
public:
	int houseNo;
	Person* occupants;
	House* nextHouse;
	House(int n = 0) : houseNo(n), occupants(nullptr), nextHouse(nullptr) {}

	void insertOccupant(Person* toAdd) {
		if (!occupants)
		{
			occupants = toAdd;
			return;
		}

		Person* curr = nullptr;
		curr = occupants;

		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = toAdd;
		return;
	}

	Person* serachOccupant(string name) {
		Person* curr = nullptr;
		curr = occupants;

		while (curr) {
			if (curr->name == name)
			{
				return curr;
			}
			curr = curr->next;
		}

		return nullptr;
	}


};


class Street {
public:
	string name;
	House* houses;
	Street* nextStreet;
	Street(string n = "") : name(n), houses(nullptr), nextStreet(nullptr) {}

	void insertHouse(House* toAdd) {

		if (!houses)
		{
			houses = toAdd;
			return;
		}

		House* curr = nullptr;
		curr = houses;
		while (houses->nextHouse)
		{
			houses = houses->nextHouse;
		}

		houses->nextHouse = toAdd;
		return;
	}

	House* searchHouse(int houseNo)
	{
		House* curr = nullptr;
		curr = houses;

		while (curr)
		{
			if (curr->houseNo == houseNo)
			{
				return curr;
			}
			curr = curr->nextHouse;
		}
		return nullptr;
	}
};

class Sector {
public:
	string name;
	Street* streets;
	Sector* nextSector;
	Sector(string n = "") : name(n), streets(nullptr), nextSector(nullptr) {}
	
	void insertStreet(Street* toAdd){

		if (!streets)
		{
			streets = toAdd;
			return;
		}	

		Street* curr = nullptr;
		curr = streets;

		while (curr->nextStreet)
		{
			curr = curr->nextStreet;
		}

		curr->nextStreet = toAdd;
		return;
	}
	
	Street* searchStreet(string name)
	{
		Street* curr = streets;

		while (curr)
		{
			if (curr->name == name)
			{
				return curr;
			}
			curr = curr->nextStreet;
		}
		return nullptr;
	}
};



