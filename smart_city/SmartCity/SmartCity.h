#pragma once
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

public:
    SmartCity() {};

    void run() {
        int choice;
        do {
            choice = menu.showMainMenu();
            switch (choice) {
            case 1: {
                int tChoice;
                do {
                    tChoice = menu.showTransportMenu();
                    switch (tChoice) {
                    case 1: break;
                    case 2: break;
                    case 3: break;
                    case 4: break;
                    case 5: break;
                    case 6: break;
                    case 7: break;
                    case 0: break;
                    default: cout << "Invalid choice! Try again.\n"; break;
                    }
                } while (tChoice != 0);
                break;
            }
            case 2: {
                int eChoice;
                do {
                    eChoice = menu.showEducationMenu();
                    switch (eChoice) {
                    case 1: break;
                    case 2: break;
                    case 3: break;
                    case 4: break;
                    case 5: break;
                    case 6: break;
                    case 7: break;
                    case 8: break;
                    case 0: break;
                    default: cout << "Invalid choice! Try again.\n"; break;
                    }
                } while (eChoice != 0);
                break;
            }
            case 3: {
                int mChoice;
                do {
                    mChoice = menu.showMedicineMenu();
                    switch (mChoice) {
                    case 1: break;
                    case 2: break;
                    case 3: break;
                    case 4: break;
                    case 5: break;
                    case 6: break;
                    case 7: break;
                    case 0: break;
                    default: cout << "Invalid choice! Try again.\n"; break;
                    }
                } while (mChoice != 0);
                break;
            }
            case 4: {
                int pChoice;
                do {
                    pChoice = menu.showPublicMenu();
                    switch (pChoice) {
                    case 1: break;
                    case 2: break;
                    case 0: break;
                    default: cout << "Invalid choice! Try again.\n"; break;
                    }
                } while (pChoice != 0);
                break;
            }
            case 5: {
                int cChoice;
                do {
                    cChoice = menu.showCommercialMenu();
                    switch (cChoice) {
                    case 1: break;
                    case 2: break;
                    case 3: break;
                    case 4: break;
                    case 5: break;
                    case 0: break;
                    default: cout << "Invalid choice! Try again.\n"; break;
                    }
                } while (cChoice != 0);
                break;
            }
            case 6: {
                int popChoice;
                do {
                    popChoice = menu.showPopulationMenu();
                    switch (popChoice) {
                    case 1: break;
                    case 2: break;
                    case 3: break;
                    case 4: break;
                    case 5: break;
                    case 6: break;
                    case 0: break;
                    default: cout << "Invalid choice! Try again.\n"; break;
                    }
                } while (popChoice != 0);
                break;
            }
            case 0:
                cout << "Exiting Smart City Management System...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
                break;
            }
        } while (choice != 0);
    }

};
