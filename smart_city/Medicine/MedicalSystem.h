#pragma once
#include "HospitalEntities.h"
#include "HospitalMaxHeap.h"
#include "../Database/Database.h"
#include "../SmartCity/CityLogger.h"
#include <string>
using namespace std;

class MedicalSystem {
public:
    Database* db;
    CityLogger* logger;

    HospitalMaxHeap emergencyBedHeap;

    void pressEnterToContinue() {
        logger->Prompt("Press Enter to continue...");
        cin.ignore();
    }

    void cls() {
        cout << "\033[2J\033[H";
    }

public:
    MedicalSystem(Database* database = nullptr,
        CityLogger* log = nullptr) : db(database), logger(log) {
    }

    bool addHospital(Hospital* h) {
        if (!db) return false;

        if (db->searchHospital(h->id)) {
            logger->Warning("Hospital with ID '" + h->id + "' already exists!");
            delete h;
            return false;
        }

        db->insertHospital(*h);
        emergencyBedHeap.insert(h->id, h->emergencyBeds);
        return true;
    }

    bool addPharmacy(Pharmacy* p) {
        if (!db) return false;

        if (db->searchPharmacy(p->id)) {
            logger->Warning("Pharmacy with ID '" + p->id + "' already exists!");
            delete p;
            return false;
        }

        db->insertPharmacy(*p);
        return true;
    }

    bool addDoctor(Person* p, const string& hospitalID) {
        if (!db) return false;
        Doctor* d = dynamic_cast<Doctor*>(p);
        Hospital* hospital = db->searchHospital(hospitalID);
        if (hospital) {
            if (hospital->doctorsTable.search(d->name)) {
                logger->Warning("Doctor '" + d->name + "' is already working at " + hospital->name + "!");
                return false;
            }
            hospital->doctorsTable.insert(d);
            return true;
        }
        else {
            logger->Error("Hospital with ID " + hospitalID + " not found.");
            return false;
        }
    }

    bool addPatient(Person* p, const string& hospitalID) {
        if (!db) return false;
        Hospital* hospital = db->searchHospital(hospitalID);
        if (hospital) {
            if (hospital->patientTable.search(p->name)) {
                logger->Warning("Patient '" + p->name + "' is already admitted to " + hospital->name + "!");
                return false;
            }
            hospital->patientTable.insert(p);
            return true;
        }
        else {
            logger->Error("Hospital with ID " + hospitalID + " not found.");
            return false;
        }
    }

    bool addMedicine(Medicine* m, Pharmacy* pharmacy) {
        if (!db) return false;

        if (pharmacy) {
            if (pharmacy->medicineTable.search(m->name)) {
                logger->Warning("Medicine '" + m->name + "' already exists in " + pharmacy->name + "!");
                return false;
            }
            pharmacy->medicineTable.insert(m);
            logger->Ok("Medicine " + m->name + " added to Pharmacy " + pharmacy->name);
            return true;
        }
        else {
            logger->Error("Pharmacy not found.");
            return false;
        }
    }

    Doctor* searchDoctor(const string& cnic) {

        Person* p = db->searchPerson(cnic);
        Doctor* d = dynamic_cast<Doctor*>(p);
        if (!d) {
            logger->Error("This person is not a doctor");
            return nullptr;
        }
        return d;

    }

    Person* searchPatient(const string& cnic) {
        return db->searchPerson(cnic);
    }

    void requestEmergencyBeds(int numBeds) {

    }

    void searchHospitalGraph(const string& hospitalName) {
        logger->Info(">>> Search Hospital Graph - Not implemented yet");
    }

    Medicine* searchMedicine(const string& name, Pharmacy* pharmacy) {
        return pharmacy->medicineTable.search(name);
    }

    Doctor* searchDoctorInHospital(const string& name, const string& hospitalId) {
        Hospital* hospital = db->searchHospital(hospitalId);
        if (!hospital) {
            logger->Error("Hospital " + hospitalId + " not found.");
            return nullptr;
        }

        Doctor* doc = hospital->doctorsTable.search(name);

        if (!doc) {
            return nullptr;
        }

        return doc;
    }

    Person* searchPatientInHospital(const string& name, const string& hospitalId) {
        Hospital* hospital = db->searchHospital(hospitalId);
        if (!hospital) {
            logger->Error("Hospital " + hospitalId + " not found.");
            return nullptr;
        }
        Person* p = hospital->patientTable.search(name);
        if (!p) {
            return nullptr;
        }
        return p;
    }

    void registerHospitalsHandler() {
        string ID, name, sector;
        int totalSpecializations, emergencyBeds;

        cls();

        logger->Title("REGISTER NEW HOSPITAL");

        logger->Prompt("Enter Hospital ID: ");
        cin >> ID;
        cin.ignore();

        logger->Prompt("Enter Hospital Name: ");
        getline(cin, name);

        logger->Prompt("Enter Sector/Location: ");
        getline(cin, sector);

        logger->Prompt("Enter Number of Emergency Beds: ");
        cin >> emergencyBeds;

        logger->Prompt("Enter Total Number of Specializations: ");
        cin >> totalSpecializations;
        cin.ignore();

        Hospital* newHospital = new Hospital(name, ID, emergencyBeds, sector, totalSpecializations);

        if (totalSpecializations > 0) {
            logger->Prompt("Enter the " + to_string(totalSpecializations) + " specializations below:");
            for (int i = 0; i < totalSpecializations; i++) {
                logger->Prompt("\n  " + to_string(i + 1) + ". ");
                getline(cin, newHospital->specialization[i]);
            }
        }

        bool added = addHospital(newHospital);
        if (!added) {
            logger->Error("Registration Failed.");
            pressEnterToContinue();
            return;
        }
        logger->Ok(name + " has been registered.");
        pressEnterToContinue();
    }

    void registerPharmaciesHandler() {
        string ID, name, location;
        int totalMedicines;

        cls();

        logger->Title("REGISTER NEW PHARMACY");

        logger->Prompt("Enter Pharmacy ID: ");
        cin >> ID;
        cin.ignore();

        logger->Prompt("Enter Pharmacy Name: ");
        getline(cin, name);

        logger->Prompt("Enter Pharmacy Location: ");
        getline(cin, location);

        logger->Prompt("Enter Total Number of Medicines: ");
        cin >> totalMedicines;
        cin.ignore();

        Pharmacy* newPharmacy = new Pharmacy(name, ID, location, totalMedicines);
        bool added = addPharmacy(newPharmacy);

        if (!added) {
            logger->Error("Registration Failed.");
            pressEnterToContinue();
            return;
        }

        if (totalMedicines > 0) {
            logger->Prompt("Enter the " + to_string(totalMedicines) + " medicines below:");
            for (int i = 0; i < totalMedicines; i++) {
                string medName, formula;
                float price;
                logger->Prompt("\nMedicine " + to_string(i + 1) + " Name: ");
                getline(cin, medName);
                logger->Prompt("Medicine " + to_string(i + 1) + " Formula: ");
                getline(cin, formula);
                logger->Prompt("Medicine " + to_string(i + 1) + " Price: ");
                cin >> price;
                cin.ignore();
                Medicine* m = new Medicine(medName, formula, price);
                addMedicine(m, newPharmacy);
            }
        }

        logger->Ok(name + " has been registered.");
        pressEnterToContinue();
    }

    void addDoctorHandler() {

        cls();

        logger->Title("REGISTER NEW DOCTOR");

        string cnic;
        logger->Prompt("Enter Doctor's CNIC: ");
        getline(cin, cnic);
        Doctor* newDoctor = searchDoctor(cnic);
        if (newDoctor == nullptr) {
            logger->Error("Doctor not found in the population database. Please add the doctor to the population first.");
            pressEnterToContinue();
            return;
        }
        string hospitalID;
        logger->Prompt("Enter Hospital ID to associate the doctor with: ");
        cin >> hospitalID;
        cin.ignore();
        bool added = addDoctor(newDoctor, hospitalID);
        if (!added) {
            logger->Error("Registration Failed.");
            pressEnterToContinue();
            return;
        }
        logger->Ok("Doctor " + newDoctor->name + " has been added to Hospital ID " + hospitalID + ".");
        pressEnterToContinue();
    }

    void addPatientHandler() {

        cls();

        logger->Title("REGISTER NEW PATIENT");

        string cnic;
        logger->Prompt("Enter Patient's CNIC: ");
        getline(cin, cnic);
        Person* newPatient = searchPatient(cnic);
        if (newPatient == nullptr) {
            logger->Error("Person not found in the population database. Please add the person to the population first.");
            pressEnterToContinue();
            return;
        }
        string hospitalID;
        logger->Prompt("Enter Hospital ID to associate the patient with: ");
        cin >> hospitalID;
        cin.ignore();
        bool added = addPatient(newPatient, hospitalID);
        if (!added) {
            logger->Error("Registration Failed.");
            pressEnterToContinue();
            return;
        }
        logger->Ok("Patient " + newPatient->name + " has been added to Hospital ID " + hospitalID + ".");
        pressEnterToContinue();
    }

    void bookEmergencyBedHandler() {

        cls();

        logger->Prompt("How many beds are required: ");
        int bedsRequired;
        cin >> bedsRequired;
        string hospitalId = emergencyBedHeap.getMax();
        bool beds = emergencyBedHeap.updateBedCount(bedsRequired, hospitalId);
        if (!beds) {
            logger->Error("Not enough beds available");
            pressEnterToContinue();
            return;
        }
        else {
            logger->Ok("Beds booked successfully at hospital with ID: " + hospitalId);
        }

        pressEnterToContinue();
    }

    void searchDoctorHandler() {

        cls();

        string name, hospitalName;
        logger->Prompt("Enter Doctor's name to search: ");
        getline(cin, name);
        logger->Prompt("Enter the name of the hospital the doctor is associated with: ");
        getline(cin, hospitalName);
        Doctor* doc = searchDoctorInHospital(name, hospitalName);

        if (doc) {
            logger->Info("Doctor Found:");
            logger->Info("Name: " + doc->name);
            logger->Info("CNIC: " + doc->CNIC);
            logger->Info("Specialization: " + doc->specialization);
        }
        else {
            logger->Error("Doctor " + name + " not found in Hospital " + hospitalName + ".");
        }
        pressEnterToContinue();
    }

    void searchPatientHandler() {

        cls();

        string name, hospitalName;
        logger->Prompt("Enter Patient's name to search: ");
        getline(cin, name);
        logger->Prompt("Enter the name of the hospital the patient is associated with: ");
        getline(cin, hospitalName);
        Person* p = searchPatientInHospital(name, hospitalName);

        if (p) {
            logger->Info("Patient Found:");
            logger->Info("Name: " + p->name);
            logger->Info("CNIC: " + p->CNIC);
        }
        else {
            logger->Warning("Patient " + name + " not found in Hospital " + hospitalName + ".");
        }
        pressEnterToContinue();
    }

    void addMedicineHandler() {

        cls();

        logger->Title("ADD MEDICINE");

        string pharmId;
        logger->Prompt("Enter Pharmacy name: ");
        getline(cin, pharmId);
        Pharmacy* pharmacy = db->searchPharmacy(pharmId);
        if (pharmacy == nullptr) {
            logger->Error("Pharmacy not found in the population database. Please add the pharmacy to the database first.");
            pressEnterToContinue();
            return;
        }
        string name, formula;
        float price;
        logger->Prompt("Enter Medicine Name: ");
        getline(cin, name);
        logger->Prompt("Enter Medicine Formula: ");
        getline(cin, formula);
        logger->Prompt("Enter Medicine Price: ");
        cin >> price;
        Medicine* m = new Medicine(name, formula, price);
        cin.ignore();
        bool added = addMedicine(m, pharmacy);
        if (!added) {
            logger->Error("Failed to add medicine.");
            pressEnterToContinue();
            return;
        }
        logger->Ok("Medicine " + name + " has been added to Pharmacy " + pharmacy->name + ".");
        pressEnterToContinue();
    }

    void searchMedicineHandler() {

        cls();

        logger->Title("SEARCH MEDICINE");
        string name;
        logger->Prompt("Enter Medicine Name to search: ");
        getline(cin, name);
        logger->Prompt("Enter Pharmacy name the medicine is in: ");
        string pharmId;
        getline(cin, pharmId);
        Pharmacy* pharmacy = db->searchPharmacy(pharmId);
        if (!pharmacy) {
            logger->Warning("Pharmacy with ID " + pharmId + " not found.");
            pressEnterToContinue();
            return;
        }
        Medicine* m = searchMedicine(name, pharmacy);
        if (!m) {
            logger->Warning("Medicine " + name + " not found in Pharmacy " + pharmacy->name + ".");
        }
        else {
            logger->Info("Medicine " + name + " found in Pharmacy " + pharmacy->name + " with price " + to_string(m->price) + ".");
        }
        pressEnterToContinue();
    }

    void listAllHospitalsHandler() {

        cls();

        for (int i = 0; i < db->getHospitalTableSize(); i++) {
            HospitalNode* current = db->getHospitalAt(i);
            while (current) {
                logger->Info("Hospital ID: " + current->data.id + ", Name: " + current->data.name + ", Sector: " + current->data.sector);
                current = current->next;
            }
        }
        pressEnterToContinue();
    }

    void listAllDoctorsHandler() {

        cls();

        for (int i = 0; i < db->getHospitalTableSize(); i++) {
            HospitalNode* current = db->getHospitalAt(i);
            while (current) {
                logger->Info("Hospital ID: " + current->data.id + ", Name: " + current->data.name);
                for (int j = 0; j < current->data.doctorsTable.tableSize; j++) {
                    DoctorNode* docCurrent = current->data.doctorsTable.table[j];
                    while (docCurrent) {
                        logger->Info("  Doctor Name: " + docCurrent->data->name + ", CNIC: " + docCurrent->data->CNIC + ", Specialization: " + docCurrent->data->specialization);
                        docCurrent = docCurrent->next;
                    }
                }
                current = current->next;
            }
        }
        pressEnterToContinue();
    }

    void listAllPharmaciesHandler() {

        cls();

        for (int i = 0; i < db->getPharmacyTableSize(); i++) {
            PharmacyNode* current = db->getPharmacyAt(i);
            while (current) {
                logger->Info("Pharmacy ID: " + current->data.id + ", Name: " + current->data.name + ", Sector: " + current->data.sector);
                current = current->next;
            }
        }
        pressEnterToContinue();
    }

    void listAllMedicinesHandler() {

        cls();

        for (int i = 0; i < db->getPharmacyTableSize(); i++) {
            PharmacyNode* current = db->getPharmacyAt(i);
            while (current) {
                logger->Info("Pharmacy ID: " + current->data.id + ", Name: " + current->data.name);

                for (int j = 0; j < current->data.medicineTable.tableSize; j++) {
                    MedicineNode* medCurrent = current->data.medicineTable.table[j];
                    while (medCurrent) {
                        logger->Info("  Medicine Name: " + medCurrent->data->name + ", Formula: " + medCurrent->data->formula + ", Price: " + to_string(medCurrent->data->price));
                        medCurrent = medCurrent->next;
                    }
                }

                current = current->next;
            }
        }
        pressEnterToContinue();
    }

    void nearestHospitalLookupHandler() {
        cls();
        logger->Title("FIND SHORTEST PATH TO HOSPITAL");
        string startID;
        logger->Prompt("Enter Start Node ID: ");
        getline(cin, startID);
        string targetType = db->getHospitalTag();
        if (startID.empty()) {
            logger->Warning("Empty Field!");
            pressEnterToContinue();
            return;
        }
        string path = db->findPathByType(startID, targetType);
        if (path.empty()) {
            logger->Warning("No path found.");
        }
        else {
            logger->Info("Shortest Path: " + path);
        }
        logger->Info(path);
        pressEnterToContinue();
    }

    void nearestPharmacyLookupHandler() {
        cls();
        logger->Title("FIND SHORTEST PATH TO PHARMACY");
        string startID;
        logger->Prompt("Enter Start Node ID: ");
        getline(cin, startID);
        string targetType = db->getPharmacyTag();
        if (startID.empty()) {
            logger->Warning("Empty Field!");
            pressEnterToContinue();
            return;
        }
        string path = db->findPathByType(startID, targetType);
        if (path.empty()) {
            logger->Warning("No path found.");
        }
        else {
            logger->Info("Shortest Path: " + path);
        }
        logger->Info(path);
        pressEnterToContinue();
    }
};