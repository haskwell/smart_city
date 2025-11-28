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

    void registerHospitalsHandler() {
        cout << ">>> Register Hospitals - Not implemented yet\n\n";
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