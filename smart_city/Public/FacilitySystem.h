#pragma once
#include <iostream>
#include "../Database/Database.h"
#include "../SmartCity/CityLogger.h"
using namespace std;

class PublicSystem {
	Database* db;
    CityLogger* logger;

public:
	PublicSystem(Database* database = nullptr, CityLogger* log = nullptr) : db(database), logger(log) {}
    void addUtilityHandler() {
        cout << ">>> Add Utility - Not implemented yet\n\n";
    }

    void findNearestUtilityHandler() {
        cout << ">>> Find Nearest Utility - Not implemented yet\n\n";
    }
};