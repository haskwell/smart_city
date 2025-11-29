#pragma once
#include <iostream>
#include <string>
using namespace std;

class Menu {
private:

    string red = "\033[31m";
    string green = "\033[32m";
    string yellow = "\033[33m";
    string blue = "\033[34m";
    string magenta = "\033[35m";
    string cyan = "\033[36m";
    string clear = "\033[0m";

    bool errorFlag;
    string clearScreen = "\033[2J\033[H";

    int stringToInt(const string& s) {
        if (s.empty()) return -1;
        int num = 0;
        for (char c : s) {
            if (c < '0' || c > '9') return -1;
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
        cout << clearScreen;
        for (int i = 0; i < len; i++) {
            const string line = s[i];
            if (i == len - 1) {
                //last line red
                cout << red << line << clear << '\n';
                break;
            }
            if (line == "") {
                cout << '\n';
                continue;
            }
            if (line[1] == '=') {
                //blue
                cout << blue << line << clear << '\n';
            }
            else {
                //normal cyan
                cout << cyan << line << clear << '\n';
            }
        }
        cout << endl;
    }

    const string mainMenu[8] = {
        "\t=== SMART CITY MANAGEMENT SYSTEM ===",
        "\t1. Transport Module",
        "\t2. Education Module",
        "\t3. Medicine Module",
        "\t4. Public Services Module",
        "\t5. Commercial Module",
        "\t6. Population Module",
        "\t0. Exit"
    };

    const string transportMenu[10] = {
        "\t=== TRANSPORT MODULE ===",
        "",
        "\t1. Register Company",
        "\t2. Register Bus with Route",
        "\t3. Add Bus Stop",
        "\t4. Connect Stops",
        "\t5. Bus Simulation",
        "\t6. Find Shortest Path",
        "\t7. Get Bus Details",
        "\t0. Back"
    };

    const string educationMenu[11] = {
        "\t=== EDUCATION MODULE ===",
        "",
        "\t1. Register Schools",
        "\t2. Add Faculty",
        "\t3. Add Students",
        "\t4. Add Department",
        "\t5. Add Class",
        "\t6. Search School by Subject",
        "\t7. Rank Schools",
        "\t8. Locate Nearest School",
        "\t0. Back"
    };

    const string medicineMenu[16] = {
        "\t=== MEDICINE MODULE ===",
        "",
        "\t1. Register Hospitals",
        "\t2. Register Pharmacies",
        "\t3. Add Doctor",
        "\t4. Add Patient",
        "\t5. Book Emergency Bed",
        "\t6. Search Doctor",
        "\t7. Search Patient",
        "\t8. Search Medicine",
        "\t9. Nearest Hospital Lookup",
        "\t10. List All Hospitals",
        "\t11. List All Doctors",
        "\t12. List All Pharmacies",
        "\t13. List All Medicines",
        "\t0. Back"
    };

    const string commercialMenu[8] = {
        "\t=== COMMERCIAL MODULE ===",
        "",
        "\t1. Register Malls",
        "\t2. Register Shops in Malls",
        "\t3. Add Items to Shops",
        "\t4. Item Search (Category Based)",
        "\t5. Find Nearest Mall",
        "\t0. Back"
    };

    const string populationMenu[7] = {
        "\t=== POPULATION MODULE ===",
        "",
        "\t1. Add People",
        "\t2. Search by CNIC",
        "\t3. Generate Report",
		"\t4. Print All People",
        "\t0. Back"
    };

    const string publicMenu[6] = {
        "\t=== PUBLIC SERVICES MODULE ===",
        "",
        "\t1. Add Utility",
        "\t2. Find Nearest Utility",
        "\t0. Back"
    };

    int getMenuChoice(const string menuArr[], int len) {
        int choice;
        do {
            if (!errorFlag) printMenu(menuArr, len);

            cout << "\t\033[35mEnter your choice: \033[33m";
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

    Menu() : errorFlag(false) {}

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
        return getMenuChoice(populationMenu, 7);
    }

    int showPublicMenu() {
        return getMenuChoice(publicMenu, 6);
    }
};