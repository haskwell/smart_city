#pragma once
#include <string>
#include"../Database/database.h"
#include "../SmartCity/CityLogger.h"
using namespace std;

class PopulationSystem {
private:
	Database* db;
    CityLogger* logger;

    void addPerson(Person* p) {
        if (!db) return;
        // If the hash table is uninitialized, create it with default size 101
        if (db->people.tableSize == 0) {
            db->people = PeopleHashTable(101);
        }
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
        else {
            newPerson = new Person(name, age, gender, CNIC, street, houseNo, occupation, sector);
            logger->Ok("Person '" + name + "' added to population as '" + occupation + "'");
        }

        db->people.insert(newPerson);

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

    void generateReportHandler() {
        cout << ">>> Generate Report - Not implemented yet\n\n";
    }
};