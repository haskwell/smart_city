#pragma once
#include "PopulationEntities.h"
#include <iostream>

class CityHierarchy {
	public:
		Sector* sectors;
		
		CityHierarchy(): sectors(nullptr){}

		void addSector(string sectorName)
		{
			Sector* toAdd = new Sector();
			toAdd->name = sectorName;
			if (!sectors)
			{
				sectors = toAdd;
				return;
			}

			Sector* curr = nullptr;
			curr = sectors;
			
			while (curr->nextSector)
			{
				curr = curr->nextSector;
			}

			curr->nextSector = toAdd;
			return;
		}

		Sector* searchSector(string name)
		{
			Sector* curr = nullptr;
			curr = sectors;

			while (curr)
			{
				if (curr->name == name)
				{
					return curr;
				}
				curr = curr->nextSector;
			}

			return nullptr;
		}

		Street* searchStreet(string streetName)
		{
			Sector* currSector = sectors;
			while (currSector)
			{
				Street* currStreet = currSector->searchStreet(streetName);
				if (currStreet&& currStreet->name==streetName) {
					return currStreet;
				}
				currSector = currSector->nextSector;
			}
			return nullptr;
		}

		House* searchHouse(int houseNo)
		{
			Sector* currSector = sectors;
			while (currSector)
			{
				Street* currStreet = currSector->streets;
				while (currStreet)
				{
					House* currHouse=currStreet->houses;
					while (currHouse)
					{
						if (currHouse->houseNo == houseNo)
						{
							return currHouse;
						}
						currHouse = currHouse->nextHouse;
					}
					currStreet = currStreet->nextStreet;
				}
				currSector = currSector->nextSector;
			}
			return nullptr;
		}

		//takes name of sector, finds it, adds a street of streetName
		void addStreet(string sectorName, string streetName)
		{
			Sector* currSector = searchSector(sectorName);

			if (!currSector)
			{
				cout << "\033[33mThis Sector Doesn't Exist!\033[0m\n";
				return;
			}

			Street* street = new Street;
			street->name = streetName;
			currSector->insertStreet(street);
			return;
		}

		//takes sectorName, streetNAme, finds them, adds a house of HouseName
		void addHouse(string sectorName, string streetName, int houseNo)
		{
			Sector* currSector = searchSector(sectorName);

			if (!currSector)
			{
				cout << "\033[33mThis Sector Doesn't Exist!\033[0m\n";
				return;
			}

			Street* currStreet = currSector->searchStreet(streetName);

			if (!currStreet)
			{
				cout << "\033[33mThis Street Doesn't Exist!\033[0m\n";
				return;
			}

			House* house = new House;
			house->houseNo = houseNo;
			currStreet->insertHouse(house);
		}

		void addPerson(Person* toAdd)
		{
			//dest=destination
			Sector* destSector = searchSector(toAdd->sector);
			Street* destStreet = nullptr;
			House* destHouse = nullptr;
			if (!destSector)
			{ 
				destSector = new Sector();
				destSector->name = toAdd->name;
				destStreet = new Street();
				destStreet->name = toAdd->name;
				destHouse = new House();
				destHouse->houseNo = toAdd->houseNo;
				destHouse->insertOccupant(toAdd);
				destStreet->insertHouse(destHouse);
				destSector->insertStreet(destStreet);
				return;
			}
			
			destStreet = destSector->searchStreet(toAdd->street);
			if (!destStreet)
			{
				destStreet = new Street();
				destStreet->name = toAdd->name;
				destHouse = new House();
				destHouse->houseNo = toAdd->houseNo;
				destHouse->insertOccupant(toAdd);
				destStreet->insertHouse(destHouse);
				destSector->insertStreet(destStreet);
				return;
			}

			destHouse = destStreet->searchHouse(toAdd->houseNo);
			if (!destHouse)
			{
				destHouse = new House();
				destHouse->houseNo = toAdd->houseNo;
				destHouse->insertOccupant(toAdd);
				destStreet->insertHouse(destHouse);
				destSector->insertStreet(destStreet);
				return;
			}

			destHouse->insertOccupant(toAdd);
	
		}
		//takes sectorName, streetNAme, HouseName finds them, takes in a PERSON POINTER, adds that to them
		void addPerson(string sectorName, string streetName, int houseNo, Person* toAdd)
		{
			
			Sector* currSector = searchSector(sectorName);
			
			if (!currSector)
			{
				cout << "\033[33mThis Sector Doesn't Exist!\033[0m\n";
				return;
			}

			Street* currStreet = currSector->searchStreet(streetName);

			if (!currStreet)
			{
				cout << "\033[33mThis Street Doesn't Exist!\033[0m\n";
				return;
			}

			House* currHouse = currStreet->searchHouse(houseNo);

			if (!currHouse)
			{
				cout << "\033[33mThis House Doesn't Exist!\033[0m\n";
				return;
			}

			currHouse->insertOccupant(toAdd);

			return;
		}
};

