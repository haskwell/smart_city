#pragma once
#include "Menu.h"
#include "../Transport/TransportSystem.h"
#include "../Education/EducationSystem.h"
#include "../Medicine/MedicalSystem.h"
#include "../Commercial/MallSystem.h"
#include "../Population/PopulationSystem.h"
#include "../Public/FacilitySystem.h"
#include "../Database/Database.h"
#include "CityLogger.h"
#include <fstream>
using namespace std;

class SmartCity {
public:
    Database* db;

    Menu menu;
    TransportSystem transport;
    EducationSystem education;
    MedicalSystem medical;
    MallSystem commercial;
    PopulationSystem population;
    PublicSystem publicServices;

	CityLogger logger;

    SmartCity()
        : db(new Database()),
        transport(db, &logger),
        education(db, &logger),
        medical(db, &logger),
        commercial(db, &logger),
        population(db, &logger),
        publicServices(db, &logger)
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
            case 7: printCityGraph(); break;
            case 0:
                cout << "Thank you for using Smart City Management System!\nGoodbye!\n";
                break;
            }
        } while (choice != 0);
    }
    ~SmartCity() {
        delete db;
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
            case 4: transport.addBusRouteHandler(); break;
            case 5: transport.busSimulationWrapper(); break;
            case 6: transport.findShortestPathByTypeHandler(); break;
            case 7: transport.searchBusHandler(); break;
            case 8: transport.listAllCompanies(); break;
            case 9: transport.listAllBusStops(); break;
            case 10: transport.printBusHistory(); break;
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
            case 7: education.showRanking(); break;
            case 8: education.locateNearestSchoolHandler(); break;
            case 9: education.listAllSchoolsHandler(); break;
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
            case 10: medical.nearestPharmacyLookupHandler(); break;
            case 11: medical.listAllHospitalsHandler(); break;
            case 12: medical.listAllDoctorsHandler(); break;
            case 13: medical.listAllPharmaciesHandler(); break;
            case 14: medical.listAllMedicinesHandler(); break;
            }
        } while (mChoice != 0);
    }

    void runPublicServices() {
        int pChoice;
        do {
            pChoice = menu.showPublicMenu();
            switch (pChoice) {
            case 1: publicServices.addFacilityHandler(); break;
            case 2: publicServices.findNearestUtilityHandler(); break;
            case 3: publicServices.listAllFacility(); break;
            }
        } while (pChoice != 0);
    }

    void runCommercial() {
        int cChoice;
        do {
            cChoice = menu.showCommercialMenu();
            switch (cChoice) {
            case 1: commercial.registerMallsHandler(); break;
            case 2: commercial.addItemsHandler(); break;
            case 3: commercial.itemSearchHandler(); break;
            case 4: commercial.findNearestMallHandler(); break;
            case 5: commercial.listAllMallsHandler(); break;
            case 6: commercial.listAllItemsHandler(); break;
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
            case 7: population.printHierarchyHandler(); break;
            case 8: population.printSectorGridHandler(); break;
            case 9: population.printBuildingsGridHandler(); break;
            case 10: population.drawPopulationHeatmap(); break;
            }
        } while (popChoice != 0);
    }

    void printCityGraph() {
        logger.Title("CITY GRAPH ADJACENCY LIST");
        db->printEntireGraph();
        logger.Info("End of City Graph");
        menu.pressEnterToContinue();
	}
public:
    void seedFromCSV() {

        ifstream fileStops("stops.csv");
        if (!fileStops.is_open()) {
            cout << "Could not open stops.csv!\n";
            return;
        }

        string line;
        getline(fileStops, line);

        while (getline(fileStops, line)) {
            if (line.empty()) continue;

            int pos1 = line.find(',');
            int pos2 = line.find(',', pos1 + 1);

            string stopId = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string coords = line.substr(pos2 + 1);

            // Remove quotes
            if (!coords.empty() && coords.front() == '"') coords.erase(0, 1);
            if (!coords.empty() && coords.back() == '"') coords.pop_back();

            // Parse latitude and longitude
            int commaPos = coords.find(',');
            float lat = 0.0f, lon = 0.0f;
            if (commaPos != string::npos) {
                lat = stof(coords.substr(0, commaPos));
                lon = stof(coords.substr(commaPos + 1));
            }

            // Determine sector
            string sector;
            if (name.size() >= 2 && name[1] == '-') {
                int spacePos = name.find(' ');
                if (spacePos != string::npos) {
                    sector = name.substr(0, spacePos);
                }
                else {
                    sector = name;
                }
            }
            else {
                sector = name;
            }

            db->insertBusStop(*new BusStop(name, stopId, sector, lat, lon));
        }

        fileStops.close();

        cout << "Bus stops seeded successfully.\n";
        
        ifstream fileBus("buses.csv");
        if (!fileBus.is_open()) {
            cout << "Could not open bus.csv!\n";
            return;
        }

        getline(fileBus, line);

        while (getline(fileBus, line)) {
            if (line.empty()) continue;

            int pos1 = line.find(',');
            int pos2 = line.find(',', pos1 + 1);
            int pos3 = line.find(',', pos2 + 1);

            string busNo = line.substr(0, pos1);
            string company = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string currentStopId = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string routeStr = line.substr(pos3 + 1);

            if (!db->searchBusCompany(company)) {
                db->insertBusCompany(new BusCompany(company));
            }

            Bus* bus = new Bus(busNo, company);
            db->insertBusToCompany(company, bus);

            // Parse route
            int start = 0, end;
            while ((end = routeStr.find('>', start)) != string::npos) {
                string stopId = routeStr.substr(start, end - start);
                // Remove whitespace
                while (!stopId.empty() && stopId.front() == ' ') stopId.erase(0, 1);
                while (!stopId.empty() && stopId.back() == ' ') stopId.pop_back();

                bus->addStop(stopId);
                start = end + 1;
            }

            // Add last stop
            string lastStop = routeStr.substr(start);
            while (!lastStop.empty() && lastStop.front() == ' ') lastStop.erase(0, 1);
            while (!lastStop.empty() && lastStop.back() == ' ') lastStop.pop_back();
            bus->addStop(lastStop);
        }

        fileBus.close();
        
        cout << "Buses seeded successfully.\n";
        ifstream fileHospitals("hospitals.csv");

        if (!fileHospitals.is_open()) {
            cout << "Could not open hospitals.csv!\n";
            return;
        }

        getline(fileHospitals, line);

        while (getline(fileHospitals, line)) {
            if (line.empty()) continue;

            string hospitalId, name, sector, specStr;
            int beds = 0;

            int pos = 0, next;

            // HospitalID
            next = line.find(',', pos);
            hospitalId = line.substr(pos, next - pos);
            pos = next + 1;

            // Name
            next = line.find(',', pos);
            name = line.substr(pos, next - pos);
            pos = next + 1;

            // Sector
            next = line.find(',', pos);
            sector = line.substr(pos, next - pos);
            pos = next + 1;

            // EmergencyBeds
            next = line.find(',', pos);
            beds = stoi(line.substr(pos, next - pos));
            pos = next + 1;

            // Specializations
            specStr = line.substr(pos);
            if (!specStr.empty() && specStr.front() == '"') specStr.erase(0, 1);
            if (!specStr.empty() && specStr.back() == '"') specStr.pop_back();

            const int MAX_SPECS = 10;
            string specializations[MAX_SPECS];
            int specCount = 0;

            int start = 0, end;
            while ((end = specStr.find(',', start)) != string::npos && specCount < MAX_SPECS) {
                string spec = specStr.substr(start, end - start);
                while (!spec.empty() && spec.front() == ' ') spec.erase(0, 1);
                while (!spec.empty() && spec.back() == ' ') spec.pop_back();
                specializations[specCount++] = spec;
                start = end + 1;
            }

            // Last specialization
            if (specCount < MAX_SPECS) {
                string lastSpec = specStr.substr(start);
                while (!lastSpec.empty() && lastSpec.front() == ' ') lastSpec.erase(0, 1);
                while (!lastSpec.empty() && lastSpec.back() == ' ') lastSpec.pop_back();
                if (!lastSpec.empty()) specializations[specCount++] = lastSpec;
            }

            Hospital* hosp = new Hospital(name, hospitalId, beds, sector, specCount);

            for (int i = 0; i < specCount; ++i) {
                if (hosp->specialization) hosp->specialization[i] = specializations[i];
            }

            medical.addHospital(hosp);
        }

        fileHospitals.close();

        cout << "Hospitals seeded successfully.\n";

        ifstream filePharmacies("pharmacies.csv");
        if (!filePharmacies.is_open()) {
            cout << "Could not open pharmacies.csv!\n";
            return;
        }

        getline(filePharmacies, line);

        while (getline(filePharmacies, line)) {
            if (line.empty()) continue;

            int pos1 = line.find(',');
            int pos2 = line.find(',', pos1 + 1);
            int pos3 = line.find(',', pos2 + 1);
            int pos4 = line.find(',', pos3 + 1);
            int pos5 = line.find(',', pos4 + 1);

            string pharmId = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string sector = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string medName = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string formula = line.substr(pos4 + 1, pos5 - pos4 - 1);
            string priceStr = line.substr(pos5 + 1);

            float price = 0.0f;
            if (!priceStr.empty()) price = stof(priceStr);

            Pharmacy* pharmacy = db->searchPharmacy(pharmId);
            if (!pharmacy) {
                pharmacy = new Pharmacy(pharmId, name, sector, 0);
                medical.addPharmacy(pharmacy);
            }

            Medicine* med = new Medicine(medName, formula, price);
            medical.addMedicine(med, pharmacy);
        }

        filePharmacies.close();
        cout << "Pharmacies seeded successfully.\n";

        ifstream filePopulation("population.csv");
        if (!filePopulation.is_open()) {
            cout << "Could not open population.csv!\n";
            return;
        }

        getline(filePopulation, line);

        while (getline(filePopulation, line)) {
            if (line.empty()) continue;

            int pos1 = line.find(',');
            int pos2 = line.find(',', pos1 + 1);
            int pos3 = line.find(',', pos2 + 1);
            int pos4 = line.find(',', pos3 + 1);
            int pos5 = line.find(',', pos4 + 1);
            int pos6 = line.find(',', pos5 + 1);

            string cnic = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string ageStr = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string sector = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string street = line.substr(pos4 + 1, pos5 - pos4 - 1);
            string houseNoStr = line.substr(pos5 + 1, pos6 - pos5 - 1);
            string occupation = line.substr(pos6 + 1);

            int age = 0, houseNo = 0;
            if (!ageStr.empty()) age = stoi(ageStr);
            if (!houseNoStr.empty()) houseNo = stoi(houseNoStr);

            char gender = 'M';

            Person* person = nullptr;

            if (occupation == "Doctor") {
                person = new Doctor(name, age, gender, cnic, street, houseNo, "doctor", sector, "General");
            }
            else if (occupation == "Student") {
                person = new Student(name, age, gender, cnic, street, houseNo, "student", 0.0);
            }
            else {
                person = new Person(name, age, gender, cnic, street, houseNo, occupation, sector);
            }

            db->insertPerson(person);
        }

        filePopulation.close();
        cout << "Population seeded successfully.\n";


        ifstream fileSchools("schools.csv");
        if (!fileSchools.is_open()) {
            cout << "Could not open schools.csv!\n";
            return;
        }

        getline(fileSchools, line);

        while (getline(fileSchools, line)) {
            if (line.empty()) continue;

            int pos1 = line.find(',');
            int pos2 = line.find(',', pos1 + 1);
            int pos3 = line.find(',', pos2 + 1);
            int pos4 = line.find(',', pos3 + 1);
            int pos5 = line.find(',', pos4 + 1);

            string schoolId = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string sector = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string ratingStr = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string subjectsStr = line.substr(pos4 + 1);

            float rating = 0.0f;
            if (!ratingStr.empty()) rating = stof(ratingStr);

            // Remove quotes from subjects
            if (!subjectsStr.empty() && subjectsStr.front() == '"') subjectsStr.erase(0, 1);
            if (!subjectsStr.empty() && subjectsStr.back() == '"') subjectsStr.pop_back();

            // Parse subjects
            const int MAX_SUBJECTS = 10;
            string subjects[MAX_SUBJECTS];
            int subjectCount = 0;
            int start = 0, end;
            while ((end = subjectsStr.find(',', start)) != string::npos && subjectCount < MAX_SUBJECTS) {
                string subj = subjectsStr.substr(start, end - start);
                while (!subj.empty() && subj.front() == ' ') subj.erase(0, 1);
                while (!subj.empty() && subj.back() == ' ') subj.pop_back();
                subjects[subjectCount++] = subj;
                start = end + 1;
            }

            if (subjectCount < MAX_SUBJECTS) {
                string lastSubj = subjectsStr.substr(start);
                while (!lastSubj.empty() && lastSubj.front() == ' ') lastSubj.erase(0, 1);
                while (!lastSubj.empty() && lastSubj.back() == ' ') lastSubj.pop_back();
                if (!lastSubj.empty()) subjects[subjectCount++] = lastSubj;
            }

            School* school = new School(schoolId, name, sector, rating, subjectCount);

            for (int i = 0; i < subjectCount; ++i) {
                if (school->subjects) school->subjects[i] = subjects[i];
            }

            education.registerSchool(school);
        }

        fileSchools.close();
        cout << "Schools seeded successfully.\n";

    
    }

    void seedRandomCity() {
        const int SECTORS = 20;
        const int BUILDINGS_PER_SECTOR = 3;
        const int TOTAL_PEOPLE = 1000;
        const int DOCTORS = 200;
        const int FACULTY = 200;
        const int STUDENTS = 200;
        const int MEDICINES_TOTAL = 1000;
        const int ITEMS_TOTAL = 1000;

        // Prepare sector names and ensure they exist in DB
        string* sectorNames = new string[SECTORS];
        for (int i = 0; i < SECTORS; i++) {
            sectorNames[i] = "Sector-" + to_string(i + 1);
            db->ensureSectorExists(sectorNames[i]);
        }

        // Arrays to collect created IDs for later assignment
        int maxSlots = SECTORS * BUILDINGS_PER_SECTOR;
        string* hospitalIds = new string[maxSlots];
        int hospitalCount = 0;
        string* schoolIds = new string[maxSlots];
        int schoolCount = 0;
        string* pharmacyIds = new string[maxSlots];
        int pharmacyCount = 0;
        string* mallIds = new string[maxSlots];
        int mallCount = 0;

        int medsRemaining = MEDICINES_TOTAL;
        int itemsRemaining = ITEMS_TOTAL;

        for (int s = 0; s < SECTORS; s++) {
            string sector = sectorNames[s];
            for (int b = 0; b < BUILDINGS_PER_SECTOR; b++) {
                // type selection: 0 hospital,1 pharmacy,2 school,3 mall,4 busStop,5 public facility
                int t = db->randomNumber() % 6;

                if (t == 0) {
                    // Hospital
                    string id = "H-" + sector + "-" + to_string(b);
                    string name = "Hospital " + id;
                    int beds = 50 + (db->randomNumber() % 51); // 50-100
                    int specs = 3 + (db->randomNumber() % 3); // 3-5
                    Hospital* hosp = new Hospital(name, id, beds, sector, specs);
                    // Fill specialization strings
                    for (int k = 0; k < specs; k++) {
                        if (hosp->specialization) hosp->specialization[k] = string("Spec-") + to_string(k + 1);
                    }
                    medical.addHospital(hosp);
                    hospitalIds[hospitalCount++] = id;
                }
                else if (t == 1) {
                    // Pharmacy
                    string id = "PH-" + sector + "-" + to_string(b);
                    string name = "Pharmacy " + id;
                    Pharmacy* ph = new Pharmacy(id, name, sector, 0);
                    db->insertPharmacy(*ph);
                    pharmacyIds[pharmacyCount++] = id;

                    // Add medicines immediately to this pharmacy
                    if (medsRemaining > 0) {
                        // choose up to 40 per pharmacy to try to exhaust medsRemaining across created pharmacies
                        int cap = 40;
                        int toAdd = (medsRemaining > cap) ? (int)(db->randomNumber() % cap + 10) : medsRemaining;
                        if (toAdd <= 0) toAdd = 1;
                        Pharmacy* regPh = db->searchPharmacy(id);
                        for (int m = 0; m < toAdd; m++) {
                            string medName = "Med-" + id + "-" + to_string(m);
                            string formula = "Formula-" + to_string((db->randomNumber() % 999) + 1);
                            float price = (float)((db->randomNumber() % 10000) + 50) / 10.0f;
                            Medicine* med = new Medicine(medName, formula, price);
                            medical.addMedicine(med, regPh);
                        }
                        medsRemaining -= toAdd;
                    }
                }
                else if (t == 2) {
                    // School - create and add default department/class immediately
                    string id = "SC-" + sector + "-" + to_string(b);
                    string name = "School " + id;
                    float rating = (float)((db->randomNumber() % 50)) / 10.0f; // 0.0 - 4.9
                    int subjects = 3;
                    School* school = new School(id, name, sector, rating, subjects);
                    // populate subjects
                    for (int k = 0; k < subjects; k++) {
                        if (school->subjects) school->subjects[k] = string("Sub-") + to_string(k + 1);
                    }
                    // create a default department and class so we can add faculty/students later
                    school->addDepartment("Dept-1");
                    school->addClass("Dept-1", "Class-A");
                    education.registerSchool(school);
                    schoolIds[schoolCount++] = id;
                }
                else if (t == 3) {
                    // Mall
                    string id = "MALL-" + sector + "-" + to_string(b);
                    string name = "Mall " + id;
                    Mall* mall = new Mall(id, name, sector);

                    // Add items immediately to this mall to approach ITEMS_TOTAL
                    if (itemsRemaining > 0) {
                        int cap = 50;
                        int toAdd = (itemsRemaining > cap) ? (int)(db->randomNumber() % cap + 10) : itemsRemaining;
                        if (toAdd <= 0) toAdd = 1;
                        for (int it = 0; it < toAdd; ++it) {
                            string prodName = "Item-" + id + "-" + to_string(it);
                            float price = (float)((db->randomNumber() % 20000) + 99) / 10.0f;
                            string category = string("Cat-") + to_string((db->randomNumber() % 6) + 1);
                            Product p(prodName, price, category);
                            commercial.addProduct(p, mall);
                        }
                        itemsRemaining -= toAdd;
                    }
                    // now register mall
                    commercial.addMall(mall);
                    mallIds[mallCount++] = id;
                }
                else if (t == 4) {
                    // Bus Stop
                    string id = "BS-" + sector + "-" + to_string(b);
                    string name = "BusStop " + id;
                    db->insertBusStop(*new BusStop(name, id, sector, 0.0f, 0.0f));
                }
                else {
                    // Public Facility
                    string id = "F-" + sector + "-" + to_string(b);
                    string name = "Facility " + id;
                    string type = "Type" + to_string((db->randomNumber() % 6) + 1);
                    Facility* f = new Facility(type, id, name, sector);
                    db->insertFacility(*f);
                }
            }
        }

        // If any medicines or items remain unallocated
        if (medsRemaining > 0 && pharmacyCount > 0) {
            int idx = 0;
            while (medsRemaining > 0) {
                string targetId = pharmacyIds[idx % pharmacyCount];
                Pharmacy* ph = db->searchPharmacy(targetId);
                int toAdd = (medsRemaining > 20) ? 20 : medsRemaining;
                for (int m = 0; m < toAdd; m++) {
                    string medName = "Med-" + targetId + "-ext-" + to_string(medsRemaining);
                    string formula = "Formula-ext";
                    float price = (float)((db->randomNumber() % 10000) + 10) / 10.0f;
                    Medicine* med = new Medicine(medName, formula, price);
                    medical.addMedicine(med, ph);
                }
                medsRemaining -= toAdd;
                idx++;
            }
        }

        if (itemsRemaining > 0 && mallCount > 0) {
            int idx = 0;
            while (itemsRemaining > 0) {
                string targetId = mallIds[idx % mallCount];
                Mall* mall = db->searchMall(targetId);
                int toAdd = (itemsRemaining > 30) ? 30 : itemsRemaining;
                for (int it = 0; it < toAdd; ++it) {
                    string prodName = "Item-" + targetId + "-ext-" + to_string(itemsRemaining);
                    float price = (float)((db->randomNumber() % 10000) + 50) / 10.0f;
                    string category = string("Cat-ext-") + to_string((db->randomNumber() % 5) + 1);
                    Product p(prodName, price, category);
                    commercial.addProduct(p, mall);
                }
                itemsRemaining -= toAdd;
                idx++;
            }
        }

        // Ensure at least one hospital and one school exist for assignment
        if (hospitalCount == 0) {
            string id = "H-Default-1";
            Hospital* hosp = new Hospital("Hospital Default", id, 100, sectorNames[0], 2);
            medical.addHospital(hosp);
            hospitalIds[hospitalCount++] = id;
        }
        if (schoolCount == 0) {
            string id = "SC-Default-1";
            School* school = new School(id, "School Default", sectorNames[0], 3.5f, 3);
            school->addDepartment("Dept-1");
            school->addClass("Dept-1", "Class-A");
            education.registerSchool(school);
            schoolIds[schoolCount++] = id;
        }
        if (pharmacyCount == 0) {
            string id = "PH-Default-1";
            Pharmacy* ph = new Pharmacy(id, "Pharmacy Default", sectorNames[0], 0);
            db->insertPharmacy(*ph);
            pharmacyIds[pharmacyCount++] = id;
        }
        if (mallCount == 0) {
            string id = "MALL-Default-1";
            Mall* mall = new Mall(id, "Mall Default", sectorNames[0]);
            for (int it = 0; it < 20; ++it) {
                string prodName = "Item-" + id + "-" + to_string(it);
                Product p(prodName, 9.99f + it, string("Cat-") + to_string(it % 3 + 1));
                commercial.addProduct(p, mall);
            }
            commercial.addMall(mall);
            mallIds[mallCount++] = id;
        }

        // Create people and assign them.
        int totalCreated = 0;
        int doctorCreated = 0;
        int facultyCreated = 0;
        int studentCreated = 0;
        int otherCreated = 0;

        for (int i = 0; i < TOTAL_PEOPLE; i++) {
            string cnic = string("30000-") + string("1000000-") + to_string(i);
            string name = string("Person-") + to_string(i + 1);
            int age = 18 + (db->randomNumber() % 60);
            char gender = (db->randomNumber() % 2 == 0) ? 'M' : 'F';
            string street = string("Street-") + to_string((db->randomNumber() % 50) + 1);
            int houseNo = (db->randomNumber() % 200) + 1;
            Person* person = nullptr;

            if (doctorCreated < DOCTORS) {
                string specialization = "General";
                person = new Doctor(name, age, gender, cnic, street, houseNo, "doctor", sectorNames[db->randomNumber() % SECTORS], specialization);
                db->insertPerson(person);
                // Assign to a hospital
                string hid = hospitalIds[doctorCreated % hospitalCount];
                medical.addDoctor(person, hid);
                doctorCreated++;
            }
            else if (facultyCreated < FACULTY) {
                // Faculty
                person = new Faculty(name, age, 'F', cnic, street, houseNo, "faculty", sectorNames[0], "math");
                db->insertPerson(person);
                // Assign to a school
                string sid = schoolIds[facultyCreated % schoolCount];
                School* sch = db->searchSchool(sid);
                if (!sch->searchDepartment("Dept-1")) sch->addDepartment("Dept-1");
                Department* dept = sch->searchDepartment("Dept-1");
                if (dept) dept->insertFaculty(dynamic_cast<Faculty*>(person));
                facultyCreated++;
            }
            else if (studentCreated < STUDENTS) {
                // Student
                person = new Student(name, age, 'F', cnic, street, houseNo, "student", 4.0, sectorNames[0]);
                db->insertPerson(person);
                // Assign to a school class
                string sid = schoolIds[studentCreated % schoolCount];
                School* sch = db->searchSchool(sid);
                if (!sch->searchDepartment("Dept-1")) sch->addDepartment("Dept-1");
                if (!sch->searchClass("Dept-1", "Class-A")) sch->addClass("Dept-1", "Class-A");
                sch->addStudent("Dept-1", "Class-A", dynamic_cast<Student*>(person));
                studentCreated++;
            }
            else {
                // general person
                person = new Person(name, age, gender, cnic, street, houseNo, "citizen", sectorNames[db->randomNumber() % SECTORS]);
                db->insertPerson(person);
                otherCreated++;
            }
            totalCreated++;
        }

        // Final log
        logger.Info("Seeded random city:");
        logger.Info("  Sectors created: " + to_string(SECTORS));
        logger.Info("  Hospitals created: " + to_string(hospitalCount));
        logger.Info("  Pharmacies created: " + to_string(pharmacyCount));
        logger.Info("  Schools created: " + to_string(schoolCount));
        logger.Info("  Malls created: " + to_string(mallCount));
        logger.Info("  People created: " + to_string(totalCreated) + " (Doctors: " + to_string(doctorCreated) + ", Faculty: " + to_string(facultyCreated) + ", Students: " + to_string(studentCreated) + ", Others: " + to_string(otherCreated) + ")");
        logger.Info("  Medicines remaining unallocated (should be 0): " + to_string(medsRemaining));
        logger.Info("  Items remaining unallocated (should be 0): " + to_string(itemsRemaining));

        delete[] sectorNames;
        delete[] hospitalIds;
        delete[] schoolIds;
        delete[] pharmacyIds;
        delete[] mallIds;
    }

};