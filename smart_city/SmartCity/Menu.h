#pragma once
#include <iostream>
#include <string>
using namespace std;

class Menu {
private:

    string clear = "\033[2J\033[H";

    int stringToInt(string& s) {
        int len = s.size();
        int num = 0;
        for (int i = 0; i < len; i++) {
            if (s[i] < '0' || s[i] > '9') {
                return -1;
            }
            num = num * 10 + (s[i] - '0');
        }
        return num;
    }

    int readChoice() {
        string input;
        getline(cin, input);
        return stringToInt(input);
    }

    string mainMenu[8] = {
        "Welcome to Smart City Management System",
        "1. Transport Module",
        "2. Education Module",
        "3. Medicine Module",
        "4. Public Services Module",
        "5. Commercial Module",
        "6. Population Module",
        "0. Exit"
    };

    string transportMenu[11] = {
        "=== TRANSPORT MODULE ===",
        "1. Register Company",
        "2. Register Bus with Route",
        "3. Add Bus Stop",
        "4. Connect Stops",
        "5. Bus Simulation",
        "6. Find Shortest Path",
        "7. Get Bus Details",
        "0. Back"
    };

    string educationMenu[11] = {
        "=== EDUCATION MODULE ===",
        "1. Register Schools",
        "2. Add Faculty",
        "3. Add Students",
        "4. Add Department",
        "5. Add Class",
        "6. Search School by Subject",
        "7. Rank Schools",
        "8. Locate Nearest School",
        "0. Back"
    };

    string medicineMenu[15] = {
       "=== MEDICINE MODULE ===",
       "1. Register Hospitals",
       "2. Register Pharmacies",
       "3. Add Doctor",
       "4. Add Patient",
       "5. Book Emergency Bed",
       "6. Search Doctor",
       "7. Search Patient",
       "8. Search Medicine",
       "9. Nearest Hospital Lookup",
       "10. List All Hospitals",
       "11. List All Doctors",
       "12. List All Pharmacies",
       "13. List All Medicines",
       "0. Back"
    };

    string commercialMenu[11] = {
        "=== COMMERCIAL MODULE ===",
        "1. Register Malls",
        "2. Register Shops in Malls",
        "3. Add Items to Shops",
        "4. Item Search (Category Based)",
        "5. Find Nearest Mall",
        "0. Back"
    };

    string populationMenu[11] = {
        "=== POPULATION MODULE ===",
        "1. Add People",
        "2. Search by CNIC",
        "3. Generate Report",
        "0. Back"
    };

    string publicMenu[11] = {
        "=== PUBLIC MODULE ===",
        "1. Add Utility",
        "2. Find Nearest Utility",
        "0. Back"
    };

public:

    void printMenu(string s[], int len) {
		cout << clear;
        for (int i = 0; i < len; i++) {
            cout << s[i] << '\n';
        }
    }

    int showMainMenu() {
        printMenu(mainMenu, 8);
        return readChoice();
    }

    int showTransportMenu() {
        printMenu(transportMenu, 9);
        return readChoice();
    }

    int showEducationMenu() {
        printMenu(educationMenu, 10);
        return readChoice();
    }

    int showMedicineMenu() {
        printMenu(medicineMenu, 15);
        return readChoice();
    }

    int showCommercialMenu() {
        printMenu(commercialMenu, 6);
        return readChoice();
    }

    int showPopulationMenu() {
        printMenu(populationMenu, 8);
        return readChoice();
    }

    int showPublicMenu() {
        printMenu(publicMenu, 4);
        return readChoice();
    }

};
