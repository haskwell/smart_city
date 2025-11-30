#pragma once
#include "Menu.h"
#include "../Transport/TransportSystem.h"
#include "../Education/EducationSystem.h"
#include "../Medicine/MedicalSystem.h"
#include "../Commercial/MallSystem.h"
#include "../Population/PopulationSystem.h"
#include "../Public/FacilitySystem.h"
#include "CityLogger.h"

using namespace std;

class SmartCity {
public:
    Menu menu;
    TransportSystem transport;
    EducationSystem education;
    MedicalSystem medical;
    MallSystem commercial;
    PopulationSystem population;
    PublicSystem publicServices;

	CityLogger logger;

public:
    Database db;

    SmartCity()
        : transport(&db, &logger),
        education(&db, &logger),
        medical(&db, &logger),
        commercial(&db, &logger),
        population(&db, &logger),
        publicServices(&db, &logger)
    {
    }

    void run() {
        int choice;
        do {
            choice = menu.showMainMenu();
            switch (choice) {
            case 1: runTransport(); break;
            case 2: runEducation(); break;
            case 3: runMedicine(); break;
            case 4: runPublicServices(); break;
            case 5: runCommercial(); break;
            case 6: runPopulation(); break;
            case 0:
                cout << "Thank you for using Smart City Management System!\nGoodbye!\n";
                break;
            }
        } while (choice != 0);
    }

private:
    void runTransport() {
        int tChoice;
        do {
            tChoice = menu.showTransportMenu();
            switch (tChoice) {
            case 1: transport.registerCompanyHandler(); break;
            case 2: transport.registerBusHandler(); break;
            case 3: transport.addBusStopHandler(); break;
            case 4: transport.connectStopsHandler(); break;
            case 5: transport.busSimulation(); break;
            case 6: transport.shortestRouteHandler(); break;
            case 7: transport.searchBusHandler(); break;
            }
        } while (tChoice != 0);
    }

    void runEducation() {
        int eChoice;
        do {
            eChoice = menu.showEducationMenu();
            switch (eChoice) {
            case 1: education.registerSchoolsHandler(); break;
            case 2: education.addFacultyHandler(); break;
            case 3: education.addStudentsHandler(); break;
            case 4: education.addDepartmentHandler(); break;
            case 5: education.addClassHandler(); break;
            case 6: education.searchSchoolBySubjectHandler(); break;
            case 7: education.rankSchoolsHandler(); break;
            case 8: education.locateNearestSchoolHandler(); break;
            }
        } while (eChoice != 0);
    }

    void runMedicine() {
        int mChoice;
        do {
            mChoice = menu.showMedicineMenu();
            switch (mChoice) {
            case 1: medical.registerHospitalsHandler(); break;
            case 2: medical.registerPharmaciesHandler(); break;
            case 3: medical.addDoctorHandler(); break;
            case 4: medical.addPatientHandler(); break;
            case 5: medical.bookEmergencyBedHandler(); break;
            case 6: medical.searchDoctorHandler(); break;
            case 7: medical.searchPatientHandler(); break;
            case 8: medical.searchMedicineHandler(); break;
            case 9: medical.nearestHospitalLookupHandler(); break;
            case 10: medical.listAllHospitalsHandler(); break;
            case 11: medical.listAllDoctorsHandler(); break;
            case 12: medical.listAllPharmaciesHandler(); break;
            case 13: medical.listAllMedicinesHandler(); break;
            }
        } while (mChoice != 0);
    }

    void runPublicServices() {
        int pChoice;
        do {
            pChoice = menu.showPublicMenu();
            switch (pChoice) {
            case 1: publicServices.addUtilityHandler(); break;
            case 2: publicServices.findNearestUtilityHandler(); break;
            }
        } while (pChoice != 0);
    }

    void runCommercial() {
        int cChoice;
        do {
            cChoice = menu.showCommercialMenu();
            switch (cChoice) {
            case 1: commercial.registerMallsHandler(); break;
            case 2: commercial.registerShopsHandler(); break;
            case 3: commercial.addItemsHandler(); break;
            case 4: commercial.itemSearchHandler(); break;
            case 5: commercial.findNearestMallHandler(); break;
            }
        } while (cChoice != 0);
    }

    void runPopulation() {
        int popChoice;
        do {
            popChoice = menu.showPopulationMenu();
            switch (popChoice) {
            case 1: population.addPeopleHandler(); break;
            case 2: population.searchByCNICHandler(); break;
            case 3: population.generateReportHandler(); break;
            case 4: population.searchSectorHandler(); break;
            case 5: population.searchStreetHandler(); break;
            case 6: population.searchHouseHandler(); break;
            case 7: population.printAllPeople(); break;
            }
        } while (popChoice != 0);
    }
};
