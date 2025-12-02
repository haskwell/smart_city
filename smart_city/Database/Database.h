#pragma once
#include "HospitalHashTable.h"
#include "PharmacyHashTable.h"
#include "SchoolHashTable.h"
#include "PeopleHashTable.h"
#include"MallHashTable.h"
//#include"ShopHashTable.h"

#include <string>
using namespace std;

class Database {
public:
    HospitalHashTable hospitals;
    PharmacyHashTable pharmacies;
    SchoolHashTable schools;
    PeopleHashTable people;

    MallHashTable malls;
	//ShopHashTable shops;

    Database() {}
    ~Database() {}

    void insertHospital(const Hospital& hospital) {
        hospitals.insert(hospital);
    }

    void insertPharmacy(const Pharmacy& pharmacy) {
        pharmacies.insert(pharmacy);
    }

    void insertSchool(const School& school) {
        schools.insert(school);
    }

    void insertPerson(Person* person) {
        people.insert(person);
    }

    // Return pointers so caller can check for nullptr
    Hospital* searchHospital(const string& hospitalID) {
        return hospitals.search(hospitalID);
    }

    Pharmacy* searchPharmacy(const string& pharmacyID) {
        return pharmacies.search(pharmacyID);
    }

    School* searchSchool(const string& schoolID) {
        return schools.search(schoolID);
    }

    Person* searchPerson(const string& personCNIC) {
        return people.search(personCNIC);
    }
};
