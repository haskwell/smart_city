#pragma once
#include"../Database/Database.h"
#include "../SmartCity/CityLogger.h"
#include <iostream>
using namespace std;
class TransportSystem {
private:
    Database* db;
    CityLogger* logger;

    void registerCompany(string companyName) {
        if (!db) return;

        BusCompany* com = new BusCompany(companyName);
        db->insertBusCompany(*com);
        logger->Ok("Company '" + companyName + "' registered successfully.");
    }

    void registerBus(string busNo, string companyName, string stopId) {
        if (!db) return;

		BusCompany* company = db->searchBusCompany(companyName);
        if (!company) {
            logger->Error("Company '" + companyName + "' not found.");
            return;
        }

        Bus* newBus = new Bus(busNo, companyName);
        db->insertBusToCompany(companyName, newBus);
        logger->Ok("Bus '" + busNo + "' registered with company '" + companyName + "'.");
    }

    void addBusStopInRoute(string busNo, int stopId) {

    }

    void addBusStop(string name, string stopId, string sector, float lat, float lon) {
        if (!db) return;

        if (db->searchBusStop(stopId)) {
            logger->Warning("Bus stop with ID " + stopId + " already exists!");
            return;
        }

        BusStop* newStop = new BusStop(name, stopId, sector, lat, lon);
		db->insertBusStop(*newStop);
        logger->Ok("Bus stop '" + name + "' added successfully.");
    }

public:
    TransportSystem(Database* database = nullptr, CityLogger* log = nullptr) : db(database), logger(log) {}

    void registerCompanyHandler() {
        cls();

        logger->Title("REGISTER NEW BUS COMPANY");

        string companyName;
        logger->Prompt("Enter Company Name: ");
        getline(cin, companyName);

        if (db->searchBusCompany(companyName)) {
            logger->Warning("Company '" + companyName + "' already exists!");
            pressEnterToContinue();
            return;
        }

        registerCompany(companyName);
        logger->Ok(companyName + " has been registered successfully.");
        pressEnterToContinue();
    }

    void registerBusHandler() {
        cls();

        logger->Title("REGISTER NEW BUS");

        string busNo, companyName;
        string stopId;

        logger->Prompt("Enter Bus Number: ");
        cin >> busNo;
        cin.ignore();

        logger->Prompt("Enter Company Name: ");
        getline(cin, companyName);

        BusCompany* company = db->searchBusCompany(companyName);
        if (!company) {
            logger->Error("Company '" + companyName + "' not found. Please register the company first.");
            pressEnterToContinue();
            return;
        }

        if (db->searchBusInCompany(companyName, busNo)) {
            logger->Warning("Bus '" + busNo + "' already exists in company '" + companyName + "'!");
            pressEnterToContinue();
            return;
        }

        logger->Prompt("Enter Starting Bus Stop ID: ");
        getline(cin, stopId);

        BusStop* stop = db->searchBusStop(stopId);
        if (!stop) {
            logger->Error("Bus stop with ID " + stopId + " not found. Please add the bus stop first.");
            pressEnterToContinue();
            return;
        }

        registerBus(busNo, companyName, stopId);

        logger->Ok("Bus '" + busNo + "' has been registered with company '" + companyName + "'.");
        pressEnterToContinue();
    }

    void addBusStopHandler() {
        cls();

        logger->Title("ADD NEW BUS STOP");

        string name;
        string stopId;
        float lat, lon;

        logger->Prompt("Enter Bus Stop Name: ");
        getline(cin, name);

        logger->Prompt("Enter Bus Stop ID: ");
		getline(cin, stopId);

        if (db->searchBusStop(stopId)) {
            logger->Warning("Bus stop with ID " + stopId + " already exists!");
            pressEnterToContinue();
            return;
        }

		logger->Prompt("Enter Sector: ");
		string sector;
		getline(cin, sector);

        logger->Prompt("Enter Latitude: ");
        cin >> lat;

        logger->Prompt("Enter Longitude: ");
        cin >> lon;
        cin.ignore();

        addBusStop(name, stopId, sector, lat, lon);
        logger->Ok(name + " has been added successfully.");
        pressEnterToContinue();
    }

    void connectStopsHandler() {
        cls();
        logger->Prompt("Not implemented");

        pressEnterToContinue();
    }

    void busSimulation() {

        logger->Title("Bus Simulation");
        BusCompaniesHashTable& busCompanies = db->getBuses();
        BusCompaniesNode** companiesTable = busCompanies.table;
        int tableSize = busCompanies.tableSize;
        int i = 0;
        while (i<tableSize)
        {
            BusCompaniesNode* companyNode=companiesTable[i];
            while (companyNode)
            {
                BusNode** busTable = companyNode->data.busTable.table;
                int busTableSize= companyNode->data.busTable.tableSize;
                int j = 0;

                while (j < busTableSize)
                {
                    BusNode* currBus = busTable[j];
                    while (currBus)
                    {
                        string* stopInfo = currBus->data->Simulate();
                        logger->Info("Bus Number: " + currBus->data->busNum);
                        logger->Info("\t\t\tCurrent Stop: "+ stopInfo[0]);
                        logger->Info("\t\t\tNextStop: "+ stopInfo[1]);
                        currBus = currBus->next;
                        delete[] stopInfo;
                    }
                    
                    j++;
                }
                companyNode = companyNode->next;
            }
            i++;
        }
        pressEnterToContinue();
    }

    void shortestRouteHandler() {
        cls();

        logger->Prompt("Not implemented");
        pressEnterToContinue();
    }

    void searchBusHandler() {
        cls();

        logger->Title("SEARCH BUS");

        string busNo, companyName;

        logger->Prompt("Enter Company Name: ");
        getline(cin, companyName);

        BusCompany* company = db->searchBusCompany(companyName);
        if (!company) {
            logger->Error("Company '" + companyName + "' not found.");
            pressEnterToContinue();
            return;
        }

        logger->Prompt("Enter Bus Number: ");
        getline(cin, busNo);

        Bus* bus = db->searchBusInCompany(companyName, busNo);

        if (bus) {
            logger->Info("Bus Found:");
            logger->Info("Bus Number: " + bus->busNum);
            logger->Info("Company: " + companyName);
            logger->Info("Status: Active");
        }
        else {
            logger->Warning("Bus '" + busNo + "' not found in company '" + companyName + "'.");
        }
        pressEnterToContinue();
    }

    void listAllCompanies() {
        cls();
		for (int i = 0; i < db->getBusCompaniesTableSize(); i++) {
            BusCompaniesNode* current = db->getBusCompanyAt(i);
            while (current) {
                logger->Info("Company: " + current->data.companyName);
				listAllBusesInCompany(current->data.companyName);
                current = current->next;
            }
        }
		pressEnterToContinue();
    }

    void listAllBusesInCompany(const string& companyName) {
        BusCompany* company = db->searchBusCompany(companyName);
        if (!company) {
            logger->Error("Company '" + companyName + "' not found.");
            return;
        }
        BusHashTable& busTable = company->busTable;
        for (int i = 0; i < busTable.tableSize; i++) {
            BusNode* current = busTable.table[i];
            while (current) {
                logger->Info("Bus Number: " + current->data->busNum);
                current = current->next;
            }
        }
    }

    void listAllBusStops() {
        cls();
		for (int i = 0; i < db->getBusStopsTableSize(); i++) {
            BusStopNode* current = db->getBusStopAt(i);
            while (current) {
                logger->Info("Bus Stop ID: " + current->data.stopId + ", Name: " + current->data.name);
                current = current->next;
            }
        }
		pressEnterToContinue();
    }

    void pressEnterToContinue() {
        logger->Prompt("Press Enter to continue...");
        cin.ignore();
    }

    void cls() {
        cout << "\033[2J\033[H";
    }

    ~TransportSystem() {

    }

};