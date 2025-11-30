#pragma once
#include <iostream>
#include"../Database/Database.h"
#include "../SmartCity/CityLogger.h"

using namespace std;

class MallSystem {
private:
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
	MallSystem(Database* database = nullptr, CityLogger* log = nullptr) : db(database), logger(log) {}

    void registerMallsHandler() {
        cls();
        cout << ">>> Register Malls - Not implemented yet\n\n";
        pressEnterToContinue();
    }

    void addItemsHandler() {
        cls();
        cout << ">>> Add Items to Shops - Not implemented yet\n\n";
		pressEnterToContinue();
    }

    void itemSearchHandler() {
        cls();
        cout << ">>> Item Search (Category Based) - Not implemented yet\n\n";
		pressEnterToContinue();
    }

    void findNearestMallHandler() {
        cls();
        cout << ">>> Find Nearest Mall - Not implemented yet\n\n";
        pressEnterToContinue();
    }
};