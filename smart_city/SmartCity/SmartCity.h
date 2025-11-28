#pragma once
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

    int stringToInt(const string& s) {
        int num = 0;
        for (char c : s) {
            if (c < '0' || c > '9') return -1;
            num = num * 10 + (c - '0');
        }
        return num;
    }

public:
    SmartCity() {};

    void run() {
        while (true) {
            int choice = menu.getMainMenuChoice();

            if (choice == 7) {
                cout << "\nThank you for using Smart City Management System!\n";
                break;
            }

            if (choice == 1) {  // Transport Module
                while (true) {
                    int sub = menu.getTransportChoice();
                    if (sub == 0) break;

                    switch (sub) {
                    case 1: {
                        cout << "Enter company name: ";
                        string name; getline(cin, name);
                        transport.registerCompany(name);
                        break;
                    }
                    case 2: {
                        cout << "Enter bus number: "; string bno; getline(cin, bno);
                        cout << "Enter company name: "; string cname; getline(cin, cname);
                        cout << "Enter starting stop ID: "; string sid; getline(cin, sid);
                        int stopId = stringToInt(sid);
                        if (stopId >= 0) transport.registerBus(bno, cname, stopId);
                        else cout << "Invalid stop ID.\n";
                        break;
                    }
                    case 3: cout << "Feature coming soon...\n"; break;
                    case 4: cout << "Feature coming soon...\n"; break;
                    case 5: cout << "Feature coming soon...\n"; break;
                    case 6: cout << "Feature coming soon...\n"; break;
                    case 7: cout << "Feature coming soon...\n"; break;
                    case 8: cout << "Feature coming soon...\n"; break;
                    case 9: transport.busSimulation(); break;
                    case 10: cout << "Feature coming soon...\n"; break;
                    }
                    cout << "\nPress Enter to continue...";
                    cin.get();  // pause
                }
            }
            else if (choice == 2) {  // Education Module
                while (true) {
                    int sub = menu.getEducationChoice();
                    if (sub == 0) break;

                    switch (sub) {
                    case 1: cout << "Register school coming soon...\n"; break;
                    case 2: cout << "Register student coming soon...\n"; break;
                    case 3: cout << "Register faculty coming soon...\n"; break;
                    case 4: cout << "Search by name coming soon...\n"; break;
                    case 5: cout << "Search by subject coming soon...\n"; break;
                    case 6: education.showRanking(); break;
                    case 7: cout << "View all schools coming soon...\n"; break;
                    }
                    cout << "\nPress Enter to continue...";
                    cin.get();
                }
            }
            else if (choice == 3) {  // Medical Module
                while (true) {
                    int sub = menu.getMedicalChoice();
                    if (sub == 0) break;

                    switch (sub) {
                    case 1: cout << "Add hospital coming soon...\n"; break;
                    case 2: cout << "Add doctor coming soon...\n"; break;
                    case 3: cout << "Admit patient coming soon...\n"; break;
                    case 4: {
                        cout << "Enter number of emergency beds needed: ";
                        string num; getline(cin, num);
                        int n = stringToInt(num);
                        if (n > 0) medical.requestEmergencyBeds(n);
                        break;
                    }
                    case 5: cout << "Add pharmacy coming soon...\n"; break;
                    case 6: cout << "Add medicine coming soon...\n"; break;
                    case 7: cout << "Search hospital coming soon...\n"; break;
                    case 8: cout << "Search medicine coming soon...\n"; break;
                    case 9: cout << "Find nearest coming soon...\n"; break;
                    }
                    cout << "\nPress Enter to continue...";
                    cin.get();
                }
            }
            else if (choice == 4 || choice == 5) {
                menu.getPlaceholderChoice();  // Commercial / Public Services
            }
            else if (choice == 6) {
                menu.getPlaceholderChoice();  // Population (partial)
            }
        }
    }
};