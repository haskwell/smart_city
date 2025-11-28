#pragma once
#include "HospitalEntities.h"

class MedicalSystem{
public:
    void addDoctor(Person* p, string hospitalName){}
    void addPatient(Person* p, string hospitalName){}
    void addHospital(Hospital* h){}
    void requestEmergencyBeds(int numBeds){}
    void addPharmacy(Pharmacy* p){}
    void addMedicine(Medicine m, string pharmacyName){}
    void searchHospitalGraph(string hospitalName){}
    void searchMedicine(string name){}
};