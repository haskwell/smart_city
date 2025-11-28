#pragma once
#include "HospitalGraph.h"
#include "PharmacyGraph.h"
#include "HospitalEntities.h"

class MedicalSystem{
    HospitalGraph hospitaGraph;
    PharmacyGraph pharmacyGraph;

    void addDoctor(Person* p, string hospitalName){}
    void addPatient(Person* p, string hospitalName){}
    void addHospital(Hospital* h){}
    void requestEmergencyBeds(int numBeds){}
    void addPharmacy(Pharmacy* p){}
    void addMedicine(Medicine m, string pharmacyName){}
    void searchHospitalGraph(string hospitalName){}
    void searchMedicine(string name){}
};