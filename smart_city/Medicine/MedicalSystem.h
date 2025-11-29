#pragma once
#include "HospitalEntities.h"
#include"../Database/Database.h"


class MedicalSystem{
private:
    Database* db;

public:

	MedicalSystem(Database* database = nullptr) : db(database) {}

    void addHospital(Hospital* h) {
        // Initialize DB table if needed
        if (db->hospitalTable.tableSize == 0) {
            db->hospitalTable.setUptable(101);
        }
        // Insert hospital into the central Database Hash Table
        db->hospitals.insert(*h);
    }

    void addPharmacy(Pharmacy* p) {
        if (db->pharmacies.tableSize == 0) {
            db->pharmacies.setUptable(101);
        }
        db->pharmacies.insert(*p);
    }

    // Adds a doctor to a SPECIFIC hospital found by ID
    void addDoctor(Person* p, string hospitalID) {
        // 1. Search for the hospital in the Database
        Hospital* targetHospital = db->hospitals.search(hospitalID);

        if (targetHospital != nullptr) {
            // 2. Add doctor to that hospital's internal table
            targetHospital->addDoctor(p);
        }
        else {
            cout << "Error: Hospital with ID " << hospitalID << " not found.\n";
        }
    }

    // Adds a patient to a SPECIFIC hospital found by ID
    void addPatient(Person* p, string hospitalID) {
        Hospital* targetHospital = db->hospitals.search(hospitalID);

        if (targetHospital != nullptr) {
            targetHospital->addPatient(p);
        }
        else {
            cout << "Error: Hospital with ID " << hospitalID << " not found.\n";
        }
    }

    // Adds a medicine to a SPECIFIC pharmacy found by ID
    void addMedicine(Medicine m, string pharmacyID) {
        // Assuming Database has a PharmacyHashTable named 'pharmacies'
        // You might need to add a search function to PharmacyHashTable similar to HospitalHashTable
        Pharmacy* targetPharma = db->searchPharmacy.search(pharmacyID);

        if (targetPharma != nullptr) {
            targetPharma->addMedicine(m);
            cout << "Medicine " << m.name << " added to Pharmacy " << targetPharma->name << endl;
        }
        else {
            cout << "Error: Pharmacy with ID " << pharmacyID << " not found.\n";
        }
    }

    void requestEmergencyBeds(int numBeds){}
    void searchHospitalGraph(string hospitalName){}
    void searchMedicine(string name){}

    void registerHospitalsHandler() {
        string ID, name, sector;
        int totalSpecializations, emergencyBeds;

        cout << "\n----------------------------------------\n";
        cout << "      REGISTER NEW HOSPITAL\n";
        cout << "----------------------------------------\n";

        cout << "Enter Hospital ID: ";
        cin >> ID;
        cin.ignore();

        cout << "Enter Hospital Name: ";
        getline(cin, name);

        cout << "Enter Sector/Location: ";
        getline(cin, sector);

        cout << "Enter Number of Emergency Beds: ";
        cin >> emergencyBeds;

        cout << "Enter Total Number of Specializations: ";
        cin >> totalSpecializations;
        cin.ignore();

        Hospital* newHospital = new Hospital(name, ID, nullptr, nullptr, emergencyBeds, sector, totalSpecializations);

        if (totalSpecializations > 0) {
            cout << "Enter the " << totalSpecializations << " specializations below:\n";
            for (int i = 0; i < totalSpecializations; i++) {
                cout << "  " << (i + 1) << ". ";
                getline(cin, newHospital->specialization[i]);
            }
        }

        this->addHospital(newHospital);

        cout << "\n>>> Success: " << name << " has been registered.\n\n";
    }

    void registerPharmaciesHandler() {
        cout << ">>> Register Pharmacies - Not implemented yet\n\n";
    }

    void bookEmergencyBedHandler() {
        cout << ">>> Book Emergency Bed - Not implemented yet\n\n";
    }

    void searchDoctorHandler() {
        cout << ">>> Search Doctor - Not implemented yet\n\n";
    }

    void searchPatientHandler() {
        cout << ">>> Search Patient - Not implemented yet\n\n";
    }

    void searchMedicineHandler() {
        cout << ">>> Search Medicine - Not implemented yet\n\n";
    }

    void nearestHospitalLookupHandler() {
        cout << ">>> Nearest Hospital Lookup - Not implemented yet\n\n";
    }
};