#pragma once
#include <iostream>
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

public:
	PopulationSystem(Database* database, CityLogger* log) : db(database), logger(log) {}

    void addPeopleHandler() {
        cout << "\n----------------------------------------\n";
        cout << "      ADD NEW PERSON\n";
        cout << "----------------------------------------\n";

        string name, CNIC, street, sector, occupation;
        int age, houseNo;
        char gender;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Gender (M/F): ";
        cin >> gender;

        cout << "Enter CNIC: ";
        cin.ignore();
        getline(cin, CNIC);

        cout << "Enter Street: ";
        getline(cin, street);

        cout << "Enter Sector: ";
        getline(cin, sector);

        cout << "Enter House Number: ";
        cin >> houseNo;

        cout << "Enter Occupation: ";
        cin.ignore();
        getline(cin, occupation);

        if (occupation == "doctor") {
            string specialization;
			cout << "Enter Specialization: ";
            cin.ignore();
			Doctor* newDoctor = new Doctor(name, age, gender, CNIC, street, houseNo, occupation, sector, specialization);
			addPerson(newDoctor);
        }
        else{
            Person* newPerson = new Person(name, age, gender, CNIC, street, houseNo, occupation, sector);
            addPerson(newPerson);
        }

        cout << "\nPerson added successfully!\n";
        cout << "----------------------------------------\n";
    }


    void searchByCNICHandler() {
        cout << ">>> Search by CNIC - Not implemented yet\n\n";
    }

    void generateReportHandler() {
        cout << ">>> Generate Report - Not implemented yet\n\n";
    }
};