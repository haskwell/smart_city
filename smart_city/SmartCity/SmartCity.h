#pragma once
#include "Menu.h"
#include "../Transport/TransportSystem.h"
#include "../Education/EducationSystem.h"
#include "../Medicine/MedicalSystem.h"
#include "../Commercial/MallSystem.h"
#include "../Population/PopulationSystem.h"
#include "../Public/FacilitySystem.h"
using namespace std;

class SmartCity {
    Menu menu;
    TransportSystem transport;
    EducationSystem education;
    MedicalSystem medical;
    MallSystem commercial;
    PopulationSystem population;
    PublicSystem publicServices;


public:
    Database db;

    SmartCity()
        : transport(&db),
        education(&db),
        medical(&db),
        commercial(&db),
        population(&db),
        publicServices(&db)
    {
    }

    void run() {
        int choice;
        do {
            choice = menu.showMainMenu();

            switch (choice) {
            case 1: { // Transport Module
                int tChoice;
                do {
                    tChoice = menu.showTransportMenu();
                    switch (tChoice) {
                    case 1: transport.registerCompanyHandler();     break;
                    case 2: transport.registerBusHandler();        break;
                    case 3: transport.addBusStopHandler();          break;
                    case 4: transport.connectStopsHandler();        break;
                    case 5: transport.busSimulation();              break;
                    case 6: transport.shortestRouteHandler();       break;
                    case 7: transport.searchBusHandler();           break;
                    case 0: cout << "Returning to main menu...\n\n"; break;
                    default: cout << "Invalid choice! Try again.\n\n"; break;
                    }
                } while (tChoice != 0);
                break;
            }

            case 2: { // Education Module
                int eChoice;
                do {
                    eChoice = menu.showEducationMenu();
                    switch (eChoice) {
                    case 1: education.registerSchoolsHandler();         break;
                    case 2: education.addFacultyHandler();              break;
                    case 3: education.addStudentsHandler();             break;
                    case 4: education.addDepartmentHandler();           break;
                    case 5: education.addClassHandler();                break;
                    case 6: education.searchSchoolBySubjectHandler();   break;
                    case 7: education.rankSchoolsHandler();             break;
                    case 8: education.locateNearestSchoolHandler();     break;
                    case 0: cout << "Returning to main menu...\n\n"; break;
                    default: cout << "Invalid choice! Try again.\n\n"; break;
                    }
                } while (eChoice != 0);
                break;
            }

            case 3: { // Medicine Module
                int mChoice;
                do {
                    mChoice = menu.showMedicineMenu();
                    switch (mChoice) {
                    case 1: medical.registerHospitalsHandler();        break;
                    case 2: medical.registerPharmaciesHandler();       break;
                    case 3: medical.addDoctorHandler();                break;
                    case 4: medical.addPatientHandler();               break;
                    case 5: medical.bookEmergencyBedHandler();         break;
                    case 6: medical.searchDoctorHandler();             break;
                    case 7: medical.searchPatientHandler();            break;
                    case 8: medical.searchMedicineHandler();           break;
                    case 9: medical.nearestHospitalLookupHandler();    break;
                    case 0: cout << "Returning to main menu...\n\n"; break;
                    default: cout << "Invalid choice! Try again.\n\n"; break;
                    }
                } while (mChoice != 0);
                break;
            }

            case 4: { // Public Services Module
                int pChoice;
                do {
                    pChoice = menu.showPublicMenu();
                    switch (pChoice) {
                    case 1: publicServices.addUtilityHandler();           break;
                    case 2: publicServices.findNearestUtilityHandler();   break;
                    case 0: cout << "Returning to main menu...\n\n"; break;
                    default: cout << "Invalid choice! Try again.\n\n"; break;
                    }
                } while (pChoice != 0);
                break;
            }

            case 5: { // Commercial Module
                int cChoice;
                do {
                    cChoice = menu.showCommercialMenu();
                    switch (cChoice) {
                    case 1: commercial.registerMallsHandler();       break;
                    case 2: commercial.registerShopsHandler();       break;
                    case 3: commercial.addItemsHandler();            break;
                    case 4: commercial.itemSearchHandler();             break;
                    case 5: commercial.findNearestMallHandler();     break;
                    case 0: cout << "Returning to main menu...\n\n"; break;
                    default: cout << "Invalid choice! Try again.\n\n"; break;
                    }
                } while (cChoice != 0);
                break;
            }

            case 6: { // Population Module
                int popChoice;
                do {
                    popChoice = menu.showPopulationMenu();
                    switch (popChoice) {
                    case 1: population.addPeopleHandler();       break;
                    case 2: population.searchByCNICHandler();    break;
                    case 3: population.generateReportHandler();  break;
                    case 0: cout << "Returning to main menu...\n\n"; break;
                    default: cout << "Invalid choice! Try again.\n\n"; break;
                    }
                } while (popChoice != 0);
                break;
            }

            case 0:
                cout << "Thank you for using Smart City Management System!\nGoodbye!\n";
                break;

            default:
                cout << "Invalid choice! Please select a valid option.\n\n";
                break;
            }
        } while (choice != 0);
    }

};
