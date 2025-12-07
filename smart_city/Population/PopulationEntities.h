#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

struct Coords {
	int x;
	int y;
	Coords(int x = 0, int y = 0) : x(x), y(y) {}
};

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

class GridNode {
public:
	string type;
	string buildingID;
	int xPos;
	int yPos;
	GridNode(int x = 0, int y = 0, string buildingID = "", string t = "") : type(t), xPos(x), yPos(y), buildingID(buildingID) {}
};

class Sector {
public:
	
	int rows = 5;
	int cols = 5;
	int count = 0;
	int gridSize = rows * cols;

	unsigned int seed = 123456;
	unsigned int randomNumber() {
		//Linear Congruential Generator
		seed = (21433103u * seed + 32183u) % 2143245289u;
		return seed;
	}

	GridNode** buildingsGrid;

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
		buildingsGrid = new GridNode * [rows];
		for(int i = 0; i < rows; i++)
		{
			buildingsGrid[i] = new GridNode[cols];
			for (int j = 0; j < cols; j++)
			{
				buildingsGrid[i][j] = GridNode(i, j, "");
			}
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

	void printBuildingsGrid()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (buildingsGrid[i][j].buildingID != "")
				{
					cout << "[" << buildingsGrid[i][j].type << ": " << buildingsGrid[i][j].buildingID << "] ";
				}
				else
				{
					cout << "[Empty] ";
				}
			}
			cout << endl;
		}
	}

	Coords insertIntoGrid(string ID, string typeTag) {

		// now insert into grid
		// in order
		if (count >= rows * cols) {
			return Coords(-1, -1);
		}

		int total = rows * cols;

		for (int k = 0; k < total; k++) {
			int i = randomNumber() % rows;
			int j = randomNumber() % cols;

			if (buildingsGrid[i][j].buildingID == "")
			{
				buildingsGrid[i][j] = GridNode(i, j, ID, typeTag);
				count++;
				return Coords(i, j);
			}
		}
		return Coords(-1, -1);
	}

	Coords insertSchool(string ID)
	{
		insertBuilding(schoolIndex, schoolTag, ID);
		return insertIntoGrid(ID, schoolTag);
	}

	Coords insertHospital(string ID)
	{
		insertBuilding(hospitalIndex, hospitalTag, ID);
		return insertIntoGrid(ID, hospitalTag);
	}

	Coords insertPharmacy(string ID)
	{
		insertBuilding(pharmacyIndex, pharmacyTag, ID);
		return insertIntoGrid(ID, pharmacyTag);
	}

	Coords insertBusStop(string ID)
	{
		insertBuilding(busStopIndex, busStopTag, ID);
		return insertIntoGrid(ID, busStopTag);
	}

	Coords insertPublicFacility(string ID)
	{
		insertBuilding(publicFacilityIndex, puclicTag, ID);
		return insertIntoGrid(ID, puclicTag);
	}

	Coords insertMall(string ID)
	{
		insertBuilding(malls, mallTag, ID);
		return insertIntoGrid(ID, mallTag);
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



