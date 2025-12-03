#pragma once
#include <string>
#include"../Database/database.h"
#include "../SmartCity/CityLogger.h"
#include "CityHierarchy.h"
using namespace std;

class PopulationSystem {
private:
	Database* db;
    CityLogger* logger;

    void addPerson(Person* p) {
        if (!db) return;
        db->people.insert(p);
	}

    Person* searchPersonByCNIC(const string& cnic) {
        if (!db) return nullptr;
        return db->people.search(cnic);
	}

    void pressEnterToContinue() {
        logger->Prompt("Press Enter to continue...");
        cin.ignore();
    }

    void cls() {
        cout << "\033[2J\033[H";
    }

public:
    CityHierarchy cityHierarchy;
	PopulationSystem(Database* database, CityLogger* log) : db(database), logger(log) {}

    void addPeopleHandler() {
        cls();
        logger->Title("ADD NEW PERSON");

        string name, CNIC, street, sector, occupation, specialization;
        int age, houseNo;
        char gender;

        logger->Prompt("Enter Name: ");
        getline(cin, name);

        logger->Prompt("Enter Age: ");
        cin >> age;

        logger->Prompt("Enter Gender (M/F): ");
        cin >> gender;
        cin.ignore();

        logger->Prompt("Enter CNIC: ");
        getline(cin, CNIC);

        logger->Prompt("Enter Street: ");
        getline(cin, street);

        logger->Prompt("Enter Sector: ");
        getline(cin, sector);

        logger->Prompt("Enter House Number: ");
        cin >> houseNo;
        cin.ignore();

        logger->Prompt("Enter Occupation: ");
        getline(cin, occupation);

        if (db->people.search(CNIC)) {
            logger->Warning("Person with CNIC '" + CNIC + "' already exists in the population!");
            pressEnterToContinue();
            return;
        }

        Person* newPerson = nullptr;

        if (occupation == "doctor" || occupation == "Doctor" || occupation == "DOCTOR") {
            logger->Prompt("Enter Doctor Specialization: ");
            getline(cin, specialization);

            newPerson = new Doctor(name, age, gender, CNIC, street, houseNo, occupation, sector, specialization);
            logger->Ok("Doctor '" + name + "' registered with specialization: " + specialization);
        }
        else if (occupation == "student" || occupation == "Student" || occupation == "STUDENT") {
			newPerson = new Student(name, age, gender, CNIC, street, houseNo, occupation);
			logger->Ok("Student '" + name + "' added to population.");
        }
        else if (occupation == "faculty" || occupation == "Faculty" || occupation == "FACULTY") {
			newPerson = new Faculty(name, age, gender, CNIC, street, houseNo, occupation);
			logger->Ok("Faculty '" + name + "' added to population.");
        }
        else {
            newPerson = new Person(name, age, gender, CNIC, street, houseNo, occupation, sector);
            logger->Ok("Person '" + name + "' added to population as '" + occupation + "'");
        }

        db->people.insert(newPerson);
        cityHierarchy.addPerson(newPerson);
        pressEnterToContinue();
    }

    void searchByCNICHandler() {
        cls();
        logger->Title("SEARCH PERSON BY CNIC");

        string cnic;
        logger->Prompt("Enter CNIC to search: ");
        getline(cin, cnic);

        Person* person = db->people.search(cnic);

        if(!person) {
            logger->Warning("No person found with CNIC: " + cnic);
			pressEnterToContinue();
			return;
        }
        
        if (person->occupation == "doctor" || person->occupation == "Doctor" || person->occupation == "DOCTOR") {
            Doctor* doc = dynamic_cast<Doctor*>(person);
            logger->Ok("Person Found!");
            logger->Info("Name           : " + person->name);
            logger->Info("CNIC           : " + person->CNIC);
            logger->Info("Age            : " + to_string(person->age));
            logger->Info("Gender         : " + string(1, person->gender));
            logger->Info("Occupation     : " + person->occupation);
            logger->Info("Address        : House #" + to_string(person->houseNo) + ", " + person->street + ", " + person->sector);
            logger->Info("Specialization : " + doc->specialization);
        }
        else {
			logger->Ok("Person Found!");
            logger->Info("Name         : " + person->name);
            logger->Info("CNIC         : " + person->CNIC);
            logger->Info("Age          : " + to_string(person->age));
            logger->Info("Gender       : " + string(1, person->gender));
            logger->Info("Occupation   : " + person->occupation);
            logger->Info("Address      : House #" + to_string(person->houseNo) + ", " + person->street + ", " + person->sector);
        }
        pressEnterToContinue();
    }

    void generateAgeReport() {

		int oneToEighteen = 0;
		int nineteenTo25 = 0;
		int twentySixTo40 = 0;
		int fortyOneTo60 = 0;
		int sixtyOnePlus = 0;

        for (int i = 0; i < db->people.tableSize; i++) {
            PersonNode* current = db->people.table[i];
            while (current) {
                int age = current->data->age;
                if (age >= 1 && age <= 18) oneToEighteen++;
                else if (age >= 19 && age <= 25) nineteenTo25++;
                else if (age >= 26 && age <= 40) twentySixTo40++;
                else if (age >= 41 && age <= 60) fortyOneTo60++;
                else if (age >= 61) sixtyOnePlus++;
                current = current->next;
            }
        }

		logger->Info("Population Age Report:");
		logger->Info("Age 1-18      : " + to_string(oneToEighteen));
		logger->Info("Age 19-25     : " + to_string(nineteenTo25));
		logger->Info("Age 26-40     : " + to_string(twentySixTo40));
		logger->Info("Age 41-60     : " + to_string(fortyOneTo60));
		logger->Info("Age 61+       : " + to_string(sixtyOnePlus));

    }

    void occupationSummaryReport() {
        
    
    }

    void genderRatioReport() {
        int maleCount = 0;
		int femaleCount = 0;

        for (int i = 0; i < db->people.tableSize; i++) {
            PersonNode* current = db->people.table[i];
            while (current) {
                if (current->data->gender == 'M' || current->data->gender == 'm') {
                    maleCount++;
                }
                else if (current->data->gender == 'F' || current->data->gender == 'f') {
                    femaleCount++;
                }
                current = current->next;
            }

        }
        logger->Info("Gender Ratio Report");
		logger->Info("Men     : " + to_string(maleCount));
		logger->Info("Women   : " + to_string(femaleCount));
    
    }

    void generateReportHandler() {
        cls();
		generateAgeReport();
        logger->Info("\n");
        logger->Info("\n");
        logger->Info("\n");
		genderRatioReport();

        pressEnterToContinue();

    }

    void printHierarchyHandler() {
        cls();
        logger->Title("CITY HIERARCHY");

        if (!cityHierarchy.sectors) {
            logger->Info("No sectors exist in the hierarchy.");
            pressEnterToContinue();
            return;
        }

        Sector* currSector = cityHierarchy.sectors;

        while (currSector) {
            logger->Info("Sector: " + currSector->name);

            Street* currStreet = currSector->streets;
            if (!currStreet) {
                logger->Info("   (No streets in this sector)");
            }

            while (currStreet) {
                logger->Info("   Street: " + currStreet->name);

                House* currHouse = currStreet->houses;
                if (!currHouse) {
                    logger->Info("      (No houses on this street)");
                }

                while (currHouse) {
                    logger->Info("      House No: " + to_string(currHouse->houseNo));

                    Person* currPerson = currHouse->occupants;
                    if (!currPerson) {
                        logger->Info("         (No occupants in this house)");
                    }

                    while (currPerson) {
                        logger->Info("         Person: " + currPerson->name +
                            " | Age: " + to_string(currPerson->age) +
                            " | Gender: " + string(1, currPerson->gender) +
                            " | CNIC: " + currPerson->CNIC +
                            " | Occupation: " + currPerson->occupation);
                        currPerson = currPerson->next;
                    }

                    currHouse = currHouse->nextHouse;
                }

                currStreet = currStreet->nextStreet;
            }

            currSector = currSector->nextSector;
            logger->Info("-------------------------------------------------");
        }

        pressEnterToContinue();
    }


    void searchHouseHandler() {
        logger->Title("SEARCH HOUSE");
        logger->Prompt("Enter Sector: ");
        string sectorName;
        getline(cin, sectorName);

        logger->Prompt("Enter Street: ");
        string streetName;
        getline(cin, streetName);

        logger->Prompt("Enter House Number: ");
        int houseNo;
        cin >> houseNo;
        cin.ignore(); // consume leftover newline

        House* house = cityHierarchy.getHouse(sectorName, streetName, houseNo);
        if (!house) {
            logger->Warning("House not found");
            pressEnterToContinue();
            return;
        }

        logger->Ok("House found in city hierarchy");
        logger->Info("Sector name: " + sectorName);
        logger->Info("Street name: " + streetName);
        logger->Info("House number: " + to_string(houseNo));

        Person* currPerson = house->occupants;
        if (!currPerson) {
            logger->Info("   (No occupants in this house)");
        }
        else {
            while (currPerson) {
                logger->Info("   Name: " + currPerson->name);
                logger->Info("   Age: " + to_string(currPerson->age));
                logger->Info("   Gender: " + string(1, currPerson->gender));
                logger->Info("   CNIC: " + currPerson->CNIC);
                logger->Info("   Occupation: " + currPerson->occupation);
                logger->Info("----------------------");
                currPerson = currPerson->next;
            }
        }
        pressEnterToContinue();
    }


    void searchStreetHandler() {
        logger->Title("SEARCH STREET");
        logger->Prompt("Enter Sector Name: ");
        string sectorName;
        getline(cin, sectorName);

        Sector* sector = cityHierarchy.searchSector(sectorName);
        if (!sector) {
            logger->Warning("Sector '" + sectorName + "' not found.");
            pressEnterToContinue();
            return;
        }

        logger->Prompt("Enter Street Name: ");
        string streetName;
        getline(cin, streetName);

        Street* street = sector->searchStreet(streetName);
        if (!street) {
            logger->Warning("Street '" + streetName + "' not found in sector '" + sectorName + "'.");
            pressEnterToContinue();
            return;
        }

        logger->Ok("Street found in sector");
        logger->Info("Street Name: " + street->name);

        House* currHouse = street->houses;
        if (!currHouse) {
            logger->Info("   (No houses in this street)");
        }
        else {
            while (currHouse) {
                logger->Info("   House No: " + to_string(currHouse->houseNo));
                Person* currPerson = currHouse->occupants;
                if (!currPerson) {
                    logger->Info("      (No occupants in this house)");
                }
                else {
                    while (currPerson) {
                        logger->Info("      Name: " + currPerson->name);
                        currPerson = currPerson->next;
                    }
                }
                currHouse = currHouse->nextHouse;
            }
        }
        pressEnterToContinue();
    }

    void searchSectorHandler() {
        logger->Title("SEARCH SECTOR");
        logger->Prompt("Enter Sector Name: ");
        string sectorName;
        getline(cin, sectorName);

        Sector* sector = cityHierarchy.searchSector(sectorName);
        if (!sector) {
            logger->Warning("Sector '" + sectorName + "' not found in the city hierarchy.");
            pressEnterToContinue();
            return;
        }

        logger->Ok("Sector '" + sectorName + "' found.");
        logger->Info("Sector Name: " + sector->name);

        Street* currStreet = sector->streets;
        if (!currStreet) {
            logger->Info("   (No streets in this sector)");
        }
        else {
            while (currStreet) {
                logger->Info("   Street: " + currStreet->name);
                House* currHouse = currStreet->houses;
                if (!currHouse) {
                    logger->Info("      (No houses in this street)");
                }
                else {
                    while (currHouse) {
                        logger->Info("      House No: " + to_string(currHouse->houseNo));
                        Person* currPerson = currHouse->occupants;
                        if (!currPerson) {
                            logger->Info("         (No occupants)");
                        }
                        else {
                            while (currPerson) {
                                logger->Info("         Name: " + currPerson->name);
                                currPerson = currPerson->next;
                            }
                        }
                        currHouse = currHouse->nextHouse;
                    }
                }
                currStreet = currStreet->nextStreet;
            }
        }
        pressEnterToContinue();
    }
};