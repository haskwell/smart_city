#pragma once
#include <iostream>
#include <string>
using namespace std;

class Menu {
private:

    int readChoice() {
        string input;
        getline(cin, input);
        return stringToInt(input);
    }

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

public:
    // === Main Menu ===
    void mainMenu() {
        cout << "\n====================================\n";
        cout << " SMART CITY MANAGEMENT SYSTEM \n";
        cout << "====================================\n";
        cout << "1. Transport Module\n";
        cout << "2. Education Module\n";
        cout << "3. Medical Module\n";
        cout << "4. Commercial Module [Coming Soon]\n";
        cout << "5. Public Services Module [Coming Soon]\n";
        cout << "6. Population Module [Coming Soon]\n";
        cout << "7. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
    }

    int getMainMenuChoice() {
        mainMenu();
        int choice = readChoice();
        while (choice < 0 || choice > 7) {
            cout << "Invalid choice. Please enter 0-7: ";
            choice = readChoice();
        }
        return choice;
    }

    // === Transport Menu ===
    void transportMenu() {
        cout << "\n====================================\n";
        cout << " TRANSPORT MODULE \n";
        cout << "====================================\n";
        cout << "1. Register Bus Company\n";
        cout << "2. Register New Bus\n";
        cout << "3. Add Bus Stop to Route\n";
        cout << "4. Add New Bus Stop\n";
        cout << "5. Connect Two Bus Stops (Road)\n";
        cout << "6. Find Shortest Route Between Stops\n";
        cout << "7. Find Nearest Bus at a Stop\n";
        cout << "8. Search Bus by Number\n";
        cout << "9. Start Bus Simulation\n";
        cout << "10. View All Bus Companies\n";
        cout << "0. Back to Main Menu\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
    }

    int getTransportChoice() {
        transportMenu();
        int choice = readChoice();
        while (choice < 0 || choice > 10) {
            cout << "Invalid choice. Please enter 0-10: ";
            choice = readChoice();
        }
        return choice;
    }

    // === Education Menu ===
    void educationMenu() {
        cout << "\n====================================\n";
        cout << " EDUCATION MODULE \n";
        cout << "====================================\n";
        cout << "1. Register New School\n";
        cout << "2. Register Student\n";
        cout << "3. Register Faculty/Teacher\n";
        cout << "4. Search School by Name\n";
        cout << "5. Search Schools by Subject\n";
        cout << "6. Display School Ranking (Performance)\n";
        cout << "7. View All Schools\n";
        cout << "0. Back to Main Menu\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
    }

    int getEducationChoice() {
        educationMenu();
        int choice = readChoice();
        while (choice < 0 || choice > 7) {
            cout << "Invalid choice. Please enter 0-7: ";
            choice = readChoice();
        }
        return choice;
    }

    // === Medical Menu ===
    void medicalMenu() {
        cout << "\n====================================\n";
        cout << " MEDICAL MODULE \n";
        cout << "====================================\n";
        cout << "1. Add New Hospital\n";
        cout << "2. Add Doctor to Hospital\n";
        cout << "3. Admit Patient\n";
        cout << "4. Request Emergency Beds\n";
        cout << "5. Add New Pharmacy\n";
        cout << "6. Add Medicine to Pharmacy\n";
        cout << "7. Search Hospital by Name\n";
        cout << "8. Search Medicine Availability\n";
        cout << "9. Find Nearest Hospital/Pharmacy\n";
        cout << "0. Back to Main Menu\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
    }

    int getMedicalChoice() {
        medicalMenu();
        int choice = readChoice();
        while (choice < 0 || choice > 9) {
            cout << "Invalid choice. Please enter 0-9: ";
            choice = readChoice();
        }
        return choice;
    }

    // Placeholder for future modules
    void showUnderConstruction() {
        cout << "\nThis module is under development.\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
    }

    int getPlaceholderChoice() {
        showUnderConstruction();
        int choice = readChoice();
        while (choice != 0) {
            cout << "Please enter 0 to go back: ";
            choice = readChoice();
        }
        return choice;
    }
};