#pragma once
#include "HospitalEntities.h"
#include "../Database/Database.h"
#include <iostream>
#include <string>
using namespace std;

class MedicalSystem {
private:
    Database* db;

    void pressEnterToContinue() {
        cout << "Press Enter to continue...";
        cin.ignore();
	}

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
		Doctor* d = dynamic_cast<Doctor*>(p);
        Hospital* hospital = db->hospitals.search(hospitalID);
        if (hospital) {
            hospital->doctorsTable.insert(d);
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

    void addMedicine(const Medicine& m, Pharmacy* pharmacy) {
        if (!db) return;
        if(!pharmacy) return; 
        if (pharmacy) {
			pharmacy->medicineTable.insert(m);
            cout << "Medicine " << m.name << " added to Pharmacy " << pharmacy->name << endl;
        }
        else {
            cout << "Error: Pharmacy with ID " << pharmacy->id << " not found.\n";
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

    Medicine* searchMedicine(const string& name, Pharmacy* pharmacy) {
		return pharmacy->medicineTable.search(name);
    }

    Doctor* searchDoctorInHospital(const string& name, const string& hospitalId) {
		Hospital* hospital = db->hospitals.search(hospitalId);
        if (!hospital) {
            cout << "Hospital " << hospitalId << " not found.\n";
            return nullptr;
        }

		Doctor* doc = hospital->doctorsTable.search(name);
        
        if (!doc) {
            cout << "Doctor " << name << " not found in Hospital " << hospitalId << ".\n";
            return nullptr;
        }

        return doc;
	}

    Person* searchPatientInHospital(const string& name, const string& hospitalId) {
        Hospital* hospital = db->hospitals.search(hospitalId);
        if (!hospital) {
            cout << "Hospital " << hospitalId << " not found.\n";
            return nullptr;
        }
        Person* p = hospital->patientTable.search(name);
        if (!p) {
            cout << "Patient " << name << " not found in Hospital " << hospitalId << ".\n";
            return nullptr;
        }
        return p;
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

        Pharmacy* newPharmacy = new Pharmacy(name, ID, location, totalMedicines);
        addPharmacy(newPharmacy);
        cin.ignore();
        if (totalMedicines > 0) {
            cout << "Enter the " << totalMedicines << " medicines below:\n";
            for (int i = 0; i < totalMedicines; i++) {
                string medName, formula;
				float price;
                cout << "Medicine " << (i + 1) << " Name: ";
                getline(cin, medName);
                cout << "Medicine " << (i + 1) << " Formula: ";
                getline(cin, formula);
                cout << "Medicine " << (i + 1) << " Price: ";
                cin >> price;
                cin.ignore();
				Medicine m(medName, formula, price);
				addMedicine(m, newPharmacy);
            }
        }

        // Insert into the database

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
		string name, hospitalName;
		cout << "Enter Doctor's name to search: ";
		getline(cin, name);
		cout << "Enter the name of the hospital the doctor is associated with: ";
		getline(cin, hospitalName);
        cin.ignore();
		Doctor* doc = searchDoctorInHospital(name, hospitalName);

        if (doc) {
            cout << "\nDoctor Found:\n";
            cout << "Name: " << doc->name << "\n";
            cout << "CNIC: " << doc->CNIC << "\n";
            cout << "Specialization: " << doc->specialization << "\n\n";
        }
        else {
			cout << "Doctor " << name << " not found in Hospital " << hospitalName << ".\n\n";
        }
    }

    void searchPatientHandler() {
        string name, hospitalName;
        cout << "Enter Patient's name to search: ";
        getline(cin, name);
        cout << "Enter the name of the hospital the patient is associated with: ";
        getline(cin, hospitalName);
        cin.ignore();
        Person* p = searchPatientInHospital(name, hospitalName);

        if (p) {
			cout << "\nPatient Found:\n";
            cout << "Name: " << p->name << "\n";
			cout << "CNIC: " << p->CNIC << "\n\n";
        }
        else {
            cout << "Patient " << name << " not found in Hospital " << hospitalName << ".\n\n";
        }
    }

    void addMedicineHandler() {

        cout << "\n----------------------------------------\n";
        cout << "      ADD MEDICINE\n";
        cout << "----------------------------------------\n";

        string pharmId;
        cout << "Enter Pharmacy name: ";
        getline(cin, pharmId);
		Pharmacy* pharmacy = db->pharmacies.search(pharmId);
        if (pharmacy == nullptr) {
            cout << "Pharmacy not found in the population database. Please add the pharmacy to the database first.\n\n";
            return;
        }
		string name, formula;
		float price;
		cout << "Enter Medicine Name: ";
		getline(cin, name);
		cout << "Enter Medicine Formula: ";
		getline(cin, formula);
		cout << "Enter Medicine Price: ";
		cin >> price;
		Medicine m(name, formula, price);
        cin.ignore();
        addMedicine(m, pharmacy);
		cout << "\n>>> Success: Medicine " << name << " has been added to Pharmacy " << pharmacy->name << ".\n\n";
    }

    void searchMedicineHandler() {
		cout << "\n----------------------------------------\n";
        cout << "      SEARCH MEDICINE\n";
		cout << "----------------------------------------\n";
        string name;
        cout << "Enter Medicine Name to search: ";
        getline(cin, name);
		cout << "Enter Pharmacy name the medicine is in: ";
		string pharmId;
		getline(cin, pharmId);
		Pharmacy* pharmacy = db->pharmacies.search(pharmId);
        Medicine* m = searchMedicine(name, pharmacy);
        if (!m) {
			cout << "Medicine " << name << " not found in Pharmacy " << pharmacy->name << ".\n\n";
        }
        else {
            cout << "\nMedicine Found:\n";
            cout << "Name: " << m->name << "\n";
            cout << "Formula: " << m->formula << "\n";
            cout << "Price: " << m->price << "\n\n";
		}
    }

    void listAllHospitalsHandler() {
		for (int i = 0; i < db->hospitals.tableSize; i++) {
            HospitalNode* current = db->hospitals.table[i];
            while (current) {
                cout << "Hospital ID: " << current->data.id << ", Name: " << current->data.name << ", Sector: " << current->data.sector << endl;
                current = current->next;
            }
        }

		pressEnterToContinue();
    }

    void listAllDoctorsHandler() {

		for (int i = 0; i < db->hospitals.tableSize; i++) {
            HospitalNode* current = db->hospitals.table[i];
            while (current) {
                cout << "Hospital ID: " << current->data.id << ", Name: " << current->data.name << endl;
                
				for (int j = 0; j < current->data.doctorsTable.tableSize; j++) {
                    DoctorNode* docCurrent = current->data.doctorsTable.table[j];
                    while (docCurrent) {
                        cout << "  Doctor Name: " << docCurrent->data->name << ", CNIC: " << docCurrent->data->CNIC << ", Specialization: " << docCurrent->data->specialization << endl;
                        docCurrent = docCurrent->next;
                    }
                }
                
                current = current->next;
            }
        }
		pressEnterToContinue();
	}

    void listAllPharmaciesHandler() {
        for (int i = 0; i < db->pharmacies.tableSize; i++) {
            PharmacyNode* current = db->pharmacies.table[i];
            while (current) {
                cout << "Pharmacy ID: " << current->data.id << ", Name: " << current->data.name << ", Sector: " << current->data.sector << endl;
                current = current->next;
            }
        }
		pressEnterToContinue();
	}

    void listAllMedicinesHandler() {
        for (int i = 0; i < db->pharmacies.tableSize; i++) {
            PharmacyNode* current = db->pharmacies.table[i];
            while (current) {
                cout << "Pharmacy ID: " << current->data.id << ", Name: " << current->data.name << endl;

                for (int j = 0; j < current->data.medicineTable.tableSize; j++) {
                    MedicineNode* medCurrent = current->data.medicineTable.table[j];
                    while (medCurrent) {
                        cout << "  Medicine Name: " << medCurrent->data.name << ", Formula: " << medCurrent->data.formula << ", Price: " << medCurrent->data.price << endl;
                        medCurrent = medCurrent->next;
                    }
                }

                current = current->next;
            }
        }
        pressEnterToContinue();
    }

    void nearestHospitalLookupHandler() {
        cout << ">>> Nearest Hospital Lookup - Not implemented yet\n\n";
    }
};
