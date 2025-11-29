#pragma once
#include "HospitalHashTable.h"
#include "PharmacyHashTable.h"
#include "SchoolHashTable.h"
#include "PeopleHashTable.h"

class Database {


public:
	HospitalHashTable hospitalTable;
	PharmacyHashTable pharmacyTable;
	SchoolHashTable schoolTable;
	PeopleHashTable peopleTable;
	Database() {}
	~Database() {}

	void insertHospital(const Hospital& hospital) {
		hospitalTable.insert(hospital);
	}

	void insertPharmacy(const Pharmacy& pharmacy) {
		pharmacyTable.insert(pharmacy);
	}

	void insertSchool(const School& school) {
		schoolTable.insert(school);
	}

	void insertPerson(const Person& person) {
		peopleTable.insert(person);
	}

	Hospital searchHospital(const string& hospitalID) {
		Hospital* hospital = hospitalTable.search(hospitalID);
		return *hospital;
	}

	Pharmacy searchPharmacy(const string& pharmacyID) {
		Pharmacy* pharmacy = pharmacyTable.search(pharmacyID);
		return *pharmacy;
	}

	School searchSchool(const string& schoolID) {
		School* school = schoolTable.search(schoolID);
		return *school;
	}

	Person searchPerson(const string& personCNIC) {
		Person* person = peopleTable.search(personCNIC);
		return *person;
	}

};