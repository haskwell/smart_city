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

class BuildingNode {
public:
	string type;
	string ID;
	BuildingNode* nextBuilding;

	BuildingNode(string t = "", string id = "") : type(t), ID(id), nextBuilding(nullptr) {}
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
	BuildingNode** buildings;
	int totalBuildings;
	int schoolIndex = 0;
	int hospitalIndex = 1;
	int busStopIndex = 2;
	int publicFacilityIndex = 3;
	int malls = 4;
	int pharmacyIndex = 5;

	string schoolTag = "school";
	string hospitalTag = "hospital";
	string puclicTag = "public";
	string mallTag = "mall";
	string busStopTag = "busStop";
	string pharmacyTag = "pharmacy";

	Sector(string n = "") : name(n), streets(nullptr), nextSector(nullptr), totalBuildings(6) {
		buildings = new BuildingNode * [totalBuildings];
		for (int i = 0; i < totalBuildings; i++)
		{
			buildings[i] = nullptr;
		}
	}

	void insertBuilding(int index, string typeTag, string ID)
	{
		BuildingNode* head = buildings[index];

		// First building
		if (!head)
		{
			buildings[index] = new BuildingNode(typeTag, ID);
			return;
		}

		BuildingNode* curr = head;


		while (curr->nextBuilding)
		{
			if (curr->ID == ID)
				return;

			curr = curr->nextBuilding;
		}


		if (curr->ID == ID)
			return;
		curr->nextBuilding = new BuildingNode(typeTag, ID);
	}

	void insertSchool(string ID)
	{
		insertBuilding(schoolIndex, schoolTag, ID);
	}

	void insertHospital(string ID)
	{
		insertBuilding(hospitalIndex, hospitalTag, ID);
	}

	void insertPharmacy(string ID)
	{
		insertBuilding(pharmacyIndex, pharmacyTag, ID);
	}

	void insertBusStop(string ID)
	{
		insertBuilding(busStopIndex, busStopTag, ID);
	}

	void insertPublicFacility(string ID)
	{
		insertBuilding(publicFacilityIndex, puclicTag, ID);
	}

	void insertMall(string ID)
	{
		insertBuilding(malls, mallTag, ID);
	}

	void insertStreet(Street* toAdd) {
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

	void insertHospital()
	{

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



