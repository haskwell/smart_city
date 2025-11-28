#pragma once
#include <iostream>
using namespace std;

class Menu {
public:
    void mainMenu() {
        cout << "\n====================================\n";
        cout << "     SMART CITY MANAGEMENT SYSTEM     \n";
        cout << "====================================\n";
        cout << "1. Transport Module\n";
        cout << "2. Education Module\n";
        cout << "3. Medical Module\n";
        cout << "4. Commercial Module     [Coming Soon]\n";
        cout << "5. Public Services Module [Coming Soon]\n";
        cout << "6. Population Module      [Coming Soon]\n";
        cout << "7. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
    }

    void transportMenu() {
        cout << "\n====================================\n";
        cout << "          TRANSPORT MODULE           \n";
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

    void educationMenu() {
        cout << "\n====================================\n";
        cout << "          EDUCATION MODULE           \n";
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

    void medicalMenu() {
        cout << "\n====================================\n";
        cout << "           MEDICAL MODULE            \n";
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

    // Optional: You can add these later when modules are implemented
    void commercialMenu() {
        cout << "\n====================================\n";
        cout << "         COMMERCIAL MODULE           \n";
        cout << "====================================\n";
        cout << "This module is under development.\n";
        cout << "0. Back to Main Menu\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
    }

    void publicServicesMenu() {
        cout << "\n====================================\n";
        cout << "      PUBLIC SERVICES MODULE         \n";
        cout << "====================================\n";
        cout << "This module is under development.\n";
        cout << "0. Back to Main Menu\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
    }

    void populationMenu() {
        cout << "\n====================================\n";
        cout << "         POPULATION MODULE           \n";
        cout << "====================================\n";
        cout << "1. Add Citizen\n";
        cout << "2. View Population Statistics\n";
        cout << "3. Search Citizen by ID\n";
        cout << "4. Update Citizen Information\n";
        cout << "0. Back to Main Menu\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
    }
};