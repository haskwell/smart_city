#pragma once
#include <iostream>
#include <string>
using namespace std;

class Menu {
private:

    bool errorFlag;

    string clear = "\033[2J\033[H";

    int stringToInt(const string& s) {
        if (s.empty()) return -1;
        int num = 0;
        for (char c : s) {
            if (c < '0' || c > '9') {
                return -1;
            }
            num = num * 10 + (c - '0');
        }
        return num;
    }

    int readChoice() {
        string input;
        getline(cin, input);
        return stringToInt(input);
    }

    void pressEnterToContinue() {
        cout << "\nPress Enter to continue...";
        cin.ignore();
    }

    void printMenu(const string s[], int len) {
		cout << clear;
        for (int i = 0; i < len; i++) {
            cout << s[i] << '\n';
        }
        cout << endl;
    }

    const string mainMenu[8] = {
        "=== SMART CITY MANAGEMENT SYSTEM ===",
        "1. Transport Module",
        "2. Education Module",
        "3. Medicine Module",
        "4. Public Services Module",
        "5. Commercial Module",
        "6. Population Module",
        "0. Exit"
    };

    const string transportMenu[10] = {
        "=== TRANSPORT MODULE ===",
        "",
        "1. Register Company",
        "2. Register Bus with Route",
        "3. Add Bus Stop",
        "4. Connect Stops",
        "5. Bus Simulation",
        "6. Find Shortest Path",
        "7. Get Bus Details",
        "0. Back"
    };

    const string educationMenu[11] = {
        "=== EDUCATION MODULE ===",
        "",
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

    const string medicineMenu[16] = {
        "=== MEDICINE MODULE ===",
        "",
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

    const string commercialMenu[8] = {
        "=== COMMERCIAL MODULE ===",
        "",
        "1. Register Malls",
        "2. Register Shops in Malls",
        "3. Add Items to Shops",
        "4. Item Search (Category Based)",
        "5. Find Nearest Mall",
        "0. Back"
    };

    const string populationMenu[6] = {
        "=== POPULATION MODULE ===",
        "",
        "1. Add People",
        "2.Search by CNIC",
        "3. Generate Report",
        "0. Back"
    };

    const string publicMenu[6] = {
        "=== PUBLIC SERVICES MODULE ===",
        "",
        "1. Add Utility",
        "2. Find Nearest Utility",
        "0. Back"
    };

    int getMenuChoice(const string menuArr[], int len) {
        int choice;
        do {
            if (!errorFlag) {
                printMenu(menuArr, len);
            }
            cout << "\nEnter your choice: ";
            choice = readChoice();

            if (choice == -1) {
                cout << "\nInvalid input! Please enter a valid number.\n";
				errorFlag = true;
            }
        } while (choice == -1);
		errorFlag = false;
        return choice;
    }

public:

    Menu(): errorFlag(false){}

    int showMainMenu() {
        return getMenuChoice(mainMenu, 8);
    }

    int showTransportMenu() {
        return getMenuChoice(transportMenu, 10);
    }

    int showEducationMenu() {
        return getMenuChoice(educationMenu, 11);
    }

    int showMedicineMenu() {
        return getMenuChoice(medicineMenu, 16);
    }

    int showCommercialMenu() {
        return getMenuChoice(commercialMenu, 8);
    }

    int showPopulationMenu() {
        return getMenuChoice(populationMenu, 6);
    }

    int showPublicMenu() {
        return getMenuChoice(publicMenu, 6);
    }
};