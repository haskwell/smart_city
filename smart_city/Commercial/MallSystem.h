#pragma once
#include <iostream>
#include"../Database/Database.h"

using namespace std;

class MallSystem {
private:
	Database* db;

public:
	MallSystem(Database* database = nullptr) : db(database) {}

	void locateMall(){}

    void registerMallsHandler() {
        cout << ">>> Register Malls - Not implemented yet\n\n";
    }

    void registerShopsHandler() {
        cout << ">>> Register Shops in Malls - Not implemented yet\n\n";
    }

    void addItemsHandler() {
        cout << ">>> Add Items to Shops - Not implemented yet\n\n";
    }

    void itemSearchHandler() {
        cout << ">>> Item Search (Category Based) - Not implemented yet\n\n";
    }

    void findNearestMallHandler() {
        cout << ">>> Find Nearest Mall - Not implemented yet\n\n";
    }
};