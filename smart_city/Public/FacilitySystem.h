#pragma once
#include <iostream>
#include <string>
#include "../Database/Database.h"
#include "../SmartCity/CityLogger.h"
#include "FacilityEntities.h"

using namespace std;

class PublicSystem {
    Database* db;
    CityLogger* logger;

    void pressEnterToContinue() {
        logger->Prompt("Press Enter to continue...");
        cin.ignore();
    }

    void cls() {
        cout << "\033[2J\033[H";
    }

public:
    PublicSystem(Database* database = nullptr, CityLogger* log = nullptr) : db(database), logger(log) {}


    bool registerFacility(Facility* facility)
    {
        if (db == nullptr)
        {
            return false;
        }

        if (db->searchFacility(facility->id))
        {
            logger->Warning("Facility with ID " + facility->id + "already exists!");
            delete facility;
            return false;
        }

        db->insertFacility(*facility);
        return true;
    }

    void addFacilityHandler() {
        cls();

        logger->Title("REGISTER NEW FACILITY");

        string id, name, type;

        logger->Prompt("Enter Facility ID: ");
        cin >> id;
        cin.ignore();


        logger->Prompt("Enter Facility Name: ");
        getline(cin, name);

        logger->Prompt("Enter Facility Type (e.g., Park, Power Plant): ");
        getline(cin, type);

		logger->Prompt("Enter Facility Sector: ");
		string sector;
		getline(cin, sector);

        Facility* newFacility = new Facility(id, name, type, sector);

        if (registerFacility(newFacility))
        {
            logger->Ok("Facility '" + name + "' has been registered successfully.");
        }
        else
        {
            logger->Error("Facility Registration Failed");
        }

        pressEnterToContinue();
    }

    void findNearestUtilityHandler() {
        cls();
        logger->Info(">>> Nearest Utility Lookup - Not implemented yet");
        pressEnterToContinue();
    }

    void listAllFacility()
    {
        cls();
        logger->Title("LIST OF ALL PUBLIC FACILITIES");

        if (!db || db->getFacilityTableSize() == 0) {
            logger->Warning("No facilities registered yet.");
            pressEnterToContinue();
            return;
        }

        for (int i = 0; i < db->getFacilityTableSize(); i++) {
            FacilityNode* current = db->getFacilityAt(i);

            while (current) {
                logger->Info("ID: " + current->data.id + " | Name: " + current->data.name + " | Type: " + current->data.type);

                current = current->next;
            }
        }

        cout << endl;
        pressEnterToContinue();
    }



};