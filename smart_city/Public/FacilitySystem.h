#pragma once
#include <iostream>
#include "../Database/Database.h"
using namespace std;

class PublicSystem {
	Database* db;
public:
	PublicSystem(Database* database = nullptr) : db(database) {}
    void addUtilityHandler() {
        cout << ">>> Add Utility - Not implemented yet\n\n";
    }

    void findNearestUtilityHandler() {
        cout << ">>> Find Nearest Utility - Not implemented yet\n\n";
    }
};