#pragma once
#include"../Database/Database.h"
#include "../SmartCity/CityLogger.h"
#include <iostream>
class TransportSystem {
private:
    Database* db;
    CityLogger* logger;
    //0 -> success
    //1, 2 -> item missing
    int registerCompany(string companyName) {
        if (db->searchBusCompany(companyName))
            return 1;
        db->insertBusCompany(*new BusCompany(companyName));
        return 0;
    }

    int registerBus(string busNo, string companyName, string stopId) {
        BusCompany* cmp = db->searchBusCompany(companyName);
        if (!cmp) return 2;
        if (db->searchBusInCompany(companyName, busNo))
            return 1;
        if (!db->searchBusStop(stopId))
            return 2;
        db->insertBusToCompany(companyName, new Bus(busNo, companyName));
        return 0;
    }

    int addBusStop(string name, string stopId, string sector, float lat, float lon) {
        if (db->searchBusStop(stopId))
            return 1;
        db->insertBusStop(*new BusStop(name, stopId, sector, lat, lon));
        return 0;
    }

    int addBusRoute(string companyName, string busNo, string stopId) {
        Bus* bus = db->searchBusInCompany(companyName, busNo);
        if (!bus) return 1;
        BusStop* stop = db->searchBusStop(stopId);
        if (!stop) return 2;
        bus->addStop(stopId);
        return 0;
    }

public:
    TransportSystem(Database* database = nullptr, CityLogger* log = nullptr) : db(database), logger(log) {}

    void registerCompanyHandler() {
        cls();
        logger->Title("REGISTER NEW BUS COMPANY");
        string name;
        logger->Prompt("Enter Company Name: ");
        getline(cin, name);
        if (name == "") {
            logger->Warning("Company name cannot be empty!");
            return pressEnterToContinue();
        }
        int code = registerCompany(name);
        if (code == 0) logger->Ok("Registered Successfully!");
        else if (code == 1) logger->Warning("Company already exists!");
        else logger->Error("Database Missing!");
        pressEnterToContinue();
    }

    void registerBusHandler() {
        cls();
        logger->Title("REGISTER BUS");
        string busNo, company, stopId;
        logger->Prompt("Enter Bus Number: ");
        getline(cin, busNo);
        logger->Prompt("Enter Company Name: ");
        getline(cin, company);
        logger->Prompt("Enter Initial Stop ID: ");
        getline(cin, stopId);
        if (busNo == "" || company == "" || stopId == "") {
            logger->Warning("All fields must be filled!");
            return pressEnterToContinue();
        }
        int code = registerBus(busNo, company, stopId);
        if (code == 0) logger->Ok("Bus added successfully!");
        else if (code == 1) logger->Warning("Bus already exists in that company!");
        else if (code == 2) logger->Error("Company or Bus Stop not found!");
        pressEnterToContinue();
    }

    void addBusStopHandler() {
        cls();
        logger->Title("ADD BUS STOP");
        string name, stopId, sector, la, lo;
        float lat, lon;
        logger->Prompt("Enter Stop Name: "); getline(cin, name);
        logger->Prompt("Enter Stop ID: "); getline(cin, stopId);
        logger->Prompt("Enter Sector: "); getline(cin, sector);
        logger->Prompt("Enter Latitude: "); getline(cin, la);
        logger->Prompt("Enter Longitude: "); getline(cin, lo);
        if (name == "" || stopId == "" || sector == "" || la == "" || lo == "") {
            logger->Warning("All fields must be filled!");
            return pressEnterToContinue();
        }
        lat = stof(la);
        lon = stof(lo);
        int code = addBusStop(name, stopId, sector, lat, lon);
        if (code == 0) logger->Ok("Bus Stop Added!");
        else if (code == 1) logger->Warning("Bus Stop already exists!");
        else logger->Error("Database Missing!");
        pressEnterToContinue();
    }

    void busSimulation() {
        cls();
        logger->Title("Bus Simulation");
        BusCompaniesHashTable& busCompanies = db->getBuses();
        BusCompaniesNode** companiesTable = busCompanies.table;
        int tableSize = busCompanies.tableSize;
        int i = 0;
        while (i < tableSize)
        {
            BusCompaniesNode* companyNode = companiesTable[i];
            while (companyNode)
            {
                BusNode** busTable = companyNode->data.busTable.table;
                int busTableSize = companyNode->data.busTable.tableSize;
                int j = 0;
                while (j < busTableSize)
                {
                    BusNode* currBus = busTable[j];
                    while (currBus)
                    {
                        string* stopInfo = currBus->data->Simulate();
                        logger->Info("Bus Number: " + currBus->data->busNum);
                        logger->Info("\t\t\tCurrent Stop: " + stopInfo[0]);
                        logger->Info("\t\t\tNextStop: " + stopInfo[1]);
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

    void busSimulationWrapper() {
        string cmd = "";
        while (true) {
            cls();
            logger->Title("BUS SIMULATION - LIVE");
            busSimulation();
            logger->Prompt("\n[N] Next State    [Q] Quit Simulation : ");
            getline(cin, cmd);
            if (cmd == "q" || cmd == "Q") {
                logger->Ok("Simulation Ended.");
                pressEnterToContinue();
                break;
            }
        }
    }

    void addBusRouteHandler() {
        cls();
        logger->Title("ADD BUS ROUTE");
        string companyName, busNo;
        logger->Prompt("Enter Company Name: ");
        getline(cin, companyName);
        logger->Prompt("Enter Bus Number: ");
        getline(cin, busNo);
        if (companyName == "" || busNo == "") {
            logger->Warning("Company name & Bus number cannot be empty!");
            return pressEnterToContinue();
        }
        Bus* bus = db->searchBusInCompany(companyName, busNo);
        if (!bus) {
            logger->Error("Bus not found! Register bus first.");
            return pressEnterToContinue();
        }
        logger->Info("\nEnter Stop IDs one-by-one.");
        logger->Info("Type  'done'  when finished.\n");
        while (true) {
            string stopId;
            logger->Prompt("Enter Stop ID: ");
            getline(cin, stopId);
            if (stopId == "done" || stopId == "DONE")
                break;
            if (stopId == "") {
                logger->Warning("Stop ID cannot be empty!");
                continue;
            }
            int code = addBusRoute(companyName, busNo, stopId);
            if (code == 0) logger->Ok("Stop added to route.");
            else if (code == 1) logger->Error("Bus not found anymore?");
            else if (code == 2) logger->Warning("Stop doesn't exist in database!");
        }
        logger->Ok("\nRoute successfully updated for bus " + busNo);
        pressEnterToContinue();
    }

    void findShortestPathByTypeHandler() {
        cls();
        logger->Title("FIND SHORTEST PATH TO BUS STOP");
        string startID;
        logger->Prompt("Enter Start Node ID: ");
        getline(cin, startID);
        string targetType = db->getBusStopTag();
        if (startID == "") {
            logger->Warning("Empty Field!");
            pressEnterToContinue();
            return;
        }
        string path = db->findPathByType(startID, targetType);
        if (path == "") {
            logger->Warning("No path found.");
        }
        else {
            logger->Info("Shortest Path: " + path);
        }
        logger->Info(path);
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
};