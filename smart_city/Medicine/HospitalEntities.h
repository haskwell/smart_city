#pragma once
#include <string>
#include "../Population/PopulationEntities.h"
#include "DoctorsHashTable.h"
#include "PatientHashTable.h"
#include "MedicineHashTable.h"
using namespace std;

class Doctor : public Person {
public:
    string specialization;

    Doctor(string n = "",
        int a = -99999,
        char g = 'M',
        string cnic = "",
        string s = "",
        int house = 0,
        string o = "",
        string sec = "",
        string spec = "")
        : Person(n, a, g, cnic, s, house, o, sec),
        specialization(spec) {
	}
};

class Hospital {
public:
    string name;
    string id;
    int emergencyBeds;
    int occupiedBeds;
    string sector;
    string* specialization;
    int totalSpecializations;

    PatientHashTable patientTable;
    DoctorsHashTable doctorsTable;

    Hospital(string n = "",
        string i = "",
        int beds = 0,
        string sec = "",
        int specCount = 0)
        : name(n),
        id(i),
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
