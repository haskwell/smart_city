#pragma once
#include "HospitalEntities.h"
#include "../Database/Database.h"
#include <iostream>
#include <string>
using namespace std;

class MedicalSystem {
private:
    Database* db;

public:
    MedicalSystem(Database* database = nullptr) : db(database) {}

    void addHospital(Hospital* h) {
        if (!db) return;

        // If the hash table is uninitialized, create it with default size 101
        if (db->hospitals.tableSize == 0) {
            db->hospitals = HospitalHashTable(101);
        }

        db->hospitals.insert(*h);
    }

    void addPharmacy(Pharmacy* p) {
        if (!db) return;

        if (db->pharmacies.tableSize == 0) {
            db->pharmacies = PharmacyHashTable(101);
        }

        db->pharmacies.insert(*p);
    }

    void addDoctor(Person* p, const string& hospitalID) {
        if (!db) return;

        Hospital* hospital = db->hospitals.search(hospitalID);
        if (hospital) {
            hospital->doctorsTable.insert(p);
        }
        else {
            cout << "Error: Hospital with ID " << hospitalID << " not found.\n";
        }
    }

    void addPatient(Person* p, const string& hospitalID) {
        if (!db) return;

        Hospital* hospital = db->hospitals.search(hospitalID);
        if (hospital) {
			hospital->patientTable.insert(p);
        }
        else {
            cout << "Error: Hospital with ID " << hospitalID << " not found.\n";
        }
    }

    void addMedicine(const Medicine& m, const string& pharmacyID) {
        if (!db) return;

        Pharmacy* pharmacy = db->pharmacies.search(pharmacyID);
        if (pharmacy) {
            pharmacy->addMedicine();
            cout << "Medicine " << m.name << " added to Pharmacy " << pharmacy->name << endl;
        }
        else {
            cout << "Error: Pharmacy with ID " << pharmacyID << " not found.\n";
        }
    }

    Doctor* searchDoctor(const string& cnic) {

        Person* p = db->people.search(cnic);
        Doctor* d = dynamic_cast<Doctor*>(p);
        if (!d) {
            cout << "This person is not a doctor\n";
            return nullptr;
        }
        return d;

    }

    Person* searchPatient(const string& cnic) {
        return db->people.search(cnic);
    }

    void requestEmergencyBeds(int numBeds) {
        cout << ">>> Request Emergency Beds - Not implemented yet\n";
    }

    void searchHospitalGraph(const string& hospitalName) {
        cout << ">>> Search Hospital Graph - Not implemented yet\n";
    }

    void searchMedicine(const string& name) {
        cout << ">>> Search Medicine - Not implemented yet\n";
    }

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

        Hospital* newHospital = new Hospital(name, ID, emergencyBeds, sector, totalSpecializations);

        if (totalSpecializations > 0) {
            cout << "Enter the " << totalSpecializations << " specializations below:\n";
            for (int i = 0; i < totalSpecializations; i++) {
                cout << "  " << (i + 1) << ". ";
                getline(cin, newHospital->specialization[i]);
            }
        }

        addHospital(newHospital);

        cout << "\n>>> Success: " << name << " has been registered.\n\n";
    }

    void registerPharmaciesHandler() {
        string ID, name, location;
        int totalMedicines;

        cout << "\n----------------------------------------\n";
        cout << "      REGISTER NEW PHARMACY\n";
        cout << "----------------------------------------\n";

        cout << "Enter Pharmacy ID: ";
        cin >> ID;
        cin.ignore();

        cout << "Enter Pharmacy Name: ";
        getline(cin, name);

        cout << "Enter Pharmacy Location: ";
        getline(cin, location);

        cout << "Enter Total Number of Medicines: ";
        cin >> totalMedicines;
        cin.ignore();

        Pharmacy* newPharmacy = new Pharmacy(name, ID, location, totalMedicines);

        //if (totalMedicines > 0) {
        //    cout << "Enter the " << totalMedicines << " medicines below:\n";
        //    for (int i = 0; i < totalMedicines; i++) {
        //        string medName;
        //        cout << "  " << (i + 1) << ". ";
        //        getline(cin, medName);
        //        Medicine m(medName);
        //        newPharmacy->addMedicine(m);
        //    }
        //}

        // Insert into the database
        addPharmacy(newPharmacy);

        cout << "\n>>> Success: " << name << " has been registered.\n\n";
    }

    void addDoctorHandler() {
        cout << "\n----------------------------------------\n";
        cout << "      REGISTER NEW DOCTOR\n";
        cout << "----------------------------------------\n";

        string cnic;
		cout << "Enter Doctor's CNIC: ";
        //cin.ignore();
		getline(cin, cnic);
		Doctor* newDoctor = searchDoctor(cnic);
        if (newDoctor == nullptr) {
            cout << "Doctor not found in the population database. Please add the doctor to the population first.\n\n";
            return;
        }
        string hospitalID;
        cout << "Enter Hospital ID to associate the doctor with: ";
        cin >> hospitalID;
        cin.ignore();
        addDoctor(newDoctor, hospitalID);
		cout << "\n>>> Success: Doctor " << newDoctor->name << " has been added to Hospital ID " << hospitalID << ".\n\n";

    }

    void addPatientHandler() {
        cout << "\n----------------------------------------\n";
        cout << "      REGISTER NEW PATIENT\n";
        cout << "----------------------------------------\n";
    
        string cnic;
        cout << "Enter Patient's CNIC: ";
        //cin.ignore();
        getline(cin, cnic);
        Person* newPatient = searchPatient(cnic);
        if (newPatient == nullptr) {
            cout << "Person not found in the population database. Please add the person to the population first.\n\n";
            return;
        }
        string hospitalID;
        cout << "Enter Hospital ID to associate the patient with: ";
        cin >> hospitalID;
        cin.ignore();
        addPatient(newPatient, hospitalID);
        cout << "\n>>> Success: Patient " << newPatient->name << " has been added to Hospital ID " << hospitalID << ".\n\n";

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
