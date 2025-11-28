#pragma once
#include <iostream>
#include <string>
#include "Menu.h"
#include "../Transport/TransportSystem.h"
#include "../Education/EducationSystem.h"
#include "../Medicine/MedicalSystem.h"

using namespace std;

class SmartCity {
    Menu menu;
    TransportSystem transport;
    EducationSystem education;
    MedicalSystem medical;

    // Your safe string-to-int converter
    int stringToInt(const string& s) {
        int num = 0;
        for (char c : s) {
            if (c < '0' || c > '9') {
                return -1;  // Invalid character found
            }
            num = num * 10 + (c - '0');
        }
        return num;
    }

public:

    SmartCity(){}

    void run() {
        string input;
        int choice;
        bool exitProgram = false;

        cout << "Welcome to the Smart City Management System!\n\n";

        do {
            menu.mainMenu();
            getline(cin, input);

            choice = stringToInt(input);
            if (choice == -1) {
                cout << "Invalid input! Please enter a number.\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            switch (choice) {
            case 1: transportSubMenu();   break;
            case 2: educationSubMenu();   break;
            case 3: medicalSubMenu();     break;
            case 4: menu.commercialMenu();     cin.get(); break;
            case 5: menu.publicServicesMenu(); cin.get(); break;
            case 6: populationSubMenu();       break;
            case 7:
                cout << "\nThank you for using Smart City Management System!\n";
                cout << "Goodbye!\n\n";
                exitProgram = true;
                break;
            default:
                cout << "Invalid option! Please choose 1-7.\n";
                cout << "Press Enter to continue...";
                cin.get();
            }
        } while (!exitProgram);
    }

private:
    void transportSubMenu() {
        string input;
        int choice;

        do {
            menu.transportMenu();
            getline(cin, input);
            choice = stringToInt(input);

            if (choice == -1) {
                cout << "Please enter a valid number!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            switch (choice) {
            case 1: {
                string name;
                cout << "Enter company name: ";
                getline(cin, name);
                if (!name.empty()) {
                    transport.registerCompany(name);
                    cout << "Company '" << name << "' registered successfully!\n";
                }
                else {
                    cout << "Company name cannot be empty!\n";
                }
                break;
            }
            case 2: cout << "Register New Bus - Coming soon!\n"; break;
            case 3: cout << "Add Bus Stop to Route - Coming soon!\n"; break;
            case 4: cout << "Add New Bus Stop - Coming soon!\n"; break;
            case 5: cout << "Connect Two Bus Stops - Coming soon!\n"; break;
            case 6: cout << "Find Shortest Route - Coming soon!\n"; break;
            case 7: cout << "Find Nearest Bus - Coming soon!\n"; break;
            case 8: cout << "Search Bus by Number - Coming soon!\n"; break;
            case 9:
                cout << "Starting bus simulation...\n";
                transport.busSimulation();
                break;
            case 10: cout << "View All Companies - Coming soon!\n"; break;
            case 0:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice! Please enter 0-10.\n";
            }

            if (choice != 0) {
                cout << "\nPress Enter to continue...";
                cin.get();
            }
        } while (choice != 0);
    }

    void educationSubMenu() {
        string input;
        int choice;

        do {
            menu.educationMenu();
            getline(cin, input);
            choice = stringToInt(input);

            if (choice == -1) {
                cout << "Invalid input! Numbers only.\n";
                cout << "Press Enter..."; cin.get();
                continue;
            }

            switch (choice) {
            case 1: cout << "Register New School - Coming soon!\n"; break;
            case 2: cout << "Register Student - Coming soon!\n"; break;
            case 3: cout << "Register Faculty - Coming soon!\n"; break;
            case 4: cout << "Search School by Name - Coming soon!\n"; break;
            case 5: cout << "Search Schools by Subject - Coming soon!\n"; break;
            case 6: education.showRanking(); break;
            case 7: cout << "View All Schools - Coming soon!\n"; break;
            case 0: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid option!\n";
            }
            if (choice != 0) { cout << "Press Enter..."; cin.get(); }
        } while (choice != 0);
    }

    void medicalSubMenu() {
        string input;
        int choice;

        do {
            menu.medicalMenu();
            getline(cin, input);
            choice = stringToInt(input);

            if (choice == -1) {
                cout << "Please enter a valid number!\n";
                cout << "Press Enter..."; cin.get();
                continue;
            }

            switch (choice) {
            case 1: cout << "Add New Hospital - Coming soon!\n"; break;
            case 2: cout << "Add Doctor - Coming soon!\n"; break;
            case 3: cout << "Admit Patient - Coming soon!\n"; break;
            case 4: {
                cout << "How many emergency beds needed? ";
                string bedsInput;
                getline(cin, bedsInput);
                int beds = stringToInt(bedsInput);
                if (beds > 0) {
                    medical.requestEmergencyBeds(beds);
                    cout << "Requested " << beds << " emergency beds.\n";
                }
                else {
                    cout << "Invalid number of beds!\n";
                }
                break;
            }
            case 5: cout << "Add Pharmacy - Coming soon!\n"; break;
            case 6: cout << "Add Medicine - Coming soon!\n"; break;
            case 7: cout << "Search Hospital - Coming soon!\n"; break;
            case 8: cout << "Search Medicine - Coming soon!\n"; break;
            case 9: cout << "Find Nearest Hospital/Pharmacy - Coming soon!\n"; break;
            case 0: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid choice!\n";
            }
            if (choice != 0) { cout << "Press Enter..."; cin.get(); }
        } while (choice != 0);
    }

    void populationSubMenu() {
        string input;
        int choice;

        do {
            menu.populationMenu();
            getline(cin, input);
            choice = stringToInt(input);

            if (choice == -1) {
                cout << "Invalid input!\nPress Enter..."; cin.get();
                continue;
            }

            switch (choice) {
            case 1: cout << "Add Citizen - Coming soon!\n"; break;
            case 2: cout << "Population Statistics - Coming soon!\n"; break;
            case 3: cout << "Search Citizen by ID - Coming soon!\n"; break;
            case 4: cout << "Update Citizen Info - Coming soon!\n"; break;
            case 0: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid option!\n";
            }
            if (choice != 0) { cout << "Press Enter..."; cin.get(); }
        } while (choice != 0);
    }
};