#pragma once
#include <string>
#include "../Population/PopulationEntities.h"
#include "DoctorsHashTable.h"
#include "PatientHashTable.h"
#include "PharmacyHashTable.h"
using namespace std;

//hello

struct Medicine {
    string name;
    string formula;
    float price;

    Medicine(string n = "", string f = "", float p = 0.0f)
        : name(n), formula(f), price(p) {
    }
};

class Hospital {
public:
    string name;
    string id;
    Person* patients;
    int emergencyBeds;
    int occupiedBeds;
    string sector;
    string* specialization;
    int totalSpecializations;
    Person* doctors;

    PatientHashTable patientTable;
    DoctorsHashTable doctorsTable;

    Hospital(string n = "",
        string i = "",
        Person* p = nullptr, 
        Person* d = nullptr,
        int beds = 0,
        string sec = "",
        int specCount = 0)
        : name(n),
        id(i),
        doctors(d), 
        patients(p),
        occupiedBeds(0), 
        emergencyBeds(beds),
        sector(sec),
        totalSpecializations(specCount)
    {
        if (totalSpecializations > 0) {
            specialization = new string[totalSpecializations];
            for (int j = 0; j < totalSpecializations; j++)
                specialization[j] = "";
        }
        else {
            specialization = nullptr;
        }
    }

    void addPatient(Person* toAdd){}
    void addDoctor(Person* toAdd) {}
    bool requestEmergencybed(int noOfbeds){}


    ~Hospital() {
        if (specialization != nullptr) {
            delete[] specialization;
            specialization = nullptr;
        }
    }
};

class Pharmacy {
public:
    string id;
    string name;
    string sector;
    Medicine* medicine;
    int totalMedicines;

    MedicineHashTable medicineTable;

    Pharmacy(string i = "",
        string n = "",
        string sec = "",
        int medCount = 0)
        : id(i),
        name(n),
        sector(sec),
        totalMedicines(medCount)
    {
        if (totalMedicines > 0) {
            medicine = new Medicine[totalMedicines];
        }
        else {
            medicine = nullptr;
        }
    }
    void addMedicine(){}
    ~Pharmacy() {
        if (medicine != nullptr) {
            delete[] medicine;
            medicine = nullptr;
        }
    }
};
