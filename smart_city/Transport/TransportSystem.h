#pragma once
#include"../Database/Database.h"
#include "../SmartCity/CityLogger.h"
class TransportSystem {
private:
    Database* db;
    CityLogger* logger;

    void registerCompany(string companyName) {
        if (!db) return;

        BusCompany* com = new BusCompany(companyName);
        db->busCompanies.insert(*com);
        logger->Ok("Company '" + companyName + "' registered successfully.");
    }

    void registerBus(string busNo, string companyName, string stopId) {
        if (!db) return;

        BusCompany* company = db->busCompanies.search(companyName);
        if (!company) {
            logger->Error("Company '" + companyName + "' not found.");
            return;
        }

        Bus* newBus = new Bus(busNo, companyName);
        db->busCompanies.insertBusToCompany(companyName, newBus);
        logger->Ok("Bus '" + busNo + "' registered with company '" + companyName + "'.");
    }

    void addBusStopInRoute(string busNo, int stopId) {

    }

    void addBusStop(string name, string stopId, float lat, float lon) {
        if (!db) return;

        if (db->busStops.search(stopId)) {
            logger->Warning("Bus stop with ID " + stopId + " already exists!");
            return;
        }

        BusStop* newStop = new BusStop(name, stopId, lat, lon);
        db->busStops.insert(*newStop);
        logger->Ok("Bus stop '" + name + "' added successfully.");
    }

    void connectStops(int fromId, int toId, int distance) {


    }

    void shortestRoute(int startId, int endId) {

    }

    void addCompany(string name) {
        if (!db) return;

        BusCompany newCompany(name);
        db->busCompanies.insert(newCompany);
        logger->Ok("Company '" + name + "' added successfully.");
    }

public:
    TransportSystem(Database* database = nullptr, CityLogger* log = nullptr) : db(database), logger(log) {}

    void registerCompanyHandler() {
        cls();

        logger->Title("REGISTER NEW BUS COMPANY");

        string companyName;
        logger->Prompt("Enter Company Name: ");
        getline(cin, companyName);

        if (db->busCompanies.search(companyName)) {
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

        BusCompany* company = db->busCompanies.search(companyName);
        if (!company) {
            logger->Error("Company '" + companyName + "' not found. Please register the company first.");
            pressEnterToContinue();
            return;
        }

        if (db->busCompanies.searchBusInCompany(companyName, busNo)) {
            logger->Warning("Bus '" + busNo + "' already exists in company '" + companyName + "'!");
            pressEnterToContinue();
            return;
        }

        logger->Prompt("Enter Starting Bus Stop ID: ");
        getline(cin, stopId);

        BusStop* stop = db->busStops.search(stopId);
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

        if (db->busStops.search(stopId)) {
            logger->Warning("Bus stop with ID " + stopId + " already exists!");
            pressEnterToContinue();
            return;
        }

        logger->Prompt("Enter Latitude: ");
        cin >> lat;

        logger->Prompt("Enter Longitude: ");
        cin >> lon;
        cin.ignore();

        addBusStop(name, stopId, lat, lon);
        logger->Ok(name + " has been added successfully.");
        pressEnterToContinue();
    }

    void connectStopsHandler() {
        cls();
        logger->Prompt("Not implemented");

        pressEnterToContinue();
    }

    void busSimulation() {
        logger->Info(">>> Bus Simulation - Not implemented yet");
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

        BusCompany* company = db->busCompanies.search(companyName);
        if (!company) {
            logger->Error("Company '" + companyName + "' not found.");
            pressEnterToContinue();
            return;
        }

        logger->Prompt("Enter Bus Number: ");
        getline(cin, busNo);

        Bus* bus = db->busCompanies.searchBusInCompany(companyName, busNo);

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
		for (int i = 0; i < db->busCompanies.tableSize; i++) {
            BusCompaniesNode* current = db->busCompanies.table[i];
            while (current) {
                logger->Info("Company: " + current->data.companyName);
				listAllBusesInCompany(current->data.companyName);
                current = current->next;
            }
        }
		pressEnterToContinue();
    }

    void listAllBusesInCompany(const string& companyName) {
        BusCompany* company = db->busCompanies.search(companyName);
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
		for (int i = 0; i < db->busStops.tableSize; i++) {
            BusStopNode* current = db->busStops.table[i];
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