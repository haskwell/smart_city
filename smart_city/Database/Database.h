#pragma once
#include "HospitalHashTable.h"
#include "PharmacyHashTable.h"
#include "SchoolHashTable.h"
#include "PeopleHashTable.h"
#include "MallHashTable.h"
#include "FacilityHashTable.h"
#include "BusStopHashTable.h"
#include "BusCompaniesHashTable.h"
#include "SectorHashTable.h"
#include "CityHierarchy.h"
#include <string>
using namespace std;

class Database {
    HospitalHashTable hospitals;
    PharmacyHashTable pharmacies;
    SchoolHashTable schools;
    PeopleHashTable people;
    MallHashTable malls;
    FacilityHashTable facilities;
    BusCompaniesHashTable busCompanies;
    BusStopHashTable busStops;
    SectorHashTable sectors;

    CityHierarchy cityHierarchy;

public:

    Database() {}
    ~Database() {}

    bool doSectorsExist() {
        return !(cityHierarchy.sectors == nullptr);
	}

    Sector* getCityHierarchySectors() {
        return cityHierarchy.sectors;
    }

    House* getHouse(const string& sectorName, const string& streetName, int houseNo) {
		return cityHierarchy.getHouse(sectorName, streetName, houseNo);
	}

    BusCompaniesHashTable& getBuses() 
    {
        return busCompanies;
    }
    void ensureSectorExists(const string& sectorName) {
        if (sectors.search(sectorName) == nullptr) {
            Sector* newSector = new Sector();
            newSector->name = sectorName;
            sectors.insert(*newSector);
            cityHierarchy.addSector(newSector);
        }
    }

    void insertHospital(const Hospital& hospital) {
        hospitals.insert(hospital);
        ensureSectorExists(hospital.sector);
        Sector* sec = sectors.search(hospital.sector);
        sec->insertHospital(hospital.id);
    }

    void insertPharmacy(const Pharmacy& pharmacy) {
        pharmacies.insert(pharmacy);
        ensureSectorExists(pharmacy.sector);
        Sector* sec = sectors.search(pharmacy.sector);
        sec->insertPharmacy(pharmacy.id);
    }

    void insertSchool(const School& school) {
        schools.insert(school);
        ensureSectorExists(school.sector);
        Sector* sec = sectors.search(school.sector);
        sec->insertSchool(school.schoolID);
    }

    void insertPerson(Person* person) {
        people.insert(person);
        cityHierarchy.addPerson(person);
        ensureSectorExists(person->sector);
    }

    void insertMall(Mall& mall) {
        malls.insert(mall);
        ensureSectorExists(mall.sector);
        Sector* sec = sectors.search(mall.sector);
        sec->insertMall(mall.mallId);
    }

    void insertSector(Sector& sector) {
        sectors.insert(sector);
        cityHierarchy.addSector(&sector);
    }

    void insertFacility(Facility& facility) {
        facilities.insert(facility);
        ensureSectorExists(facility.sector);
		Sector* sec = sectors.search(facility.sector);
		sec->insertPublicFacility(facility.id);
    }

    void insertBusCompany(BusCompany& company) {
        busCompanies.insert(company);
    }

    void insertBusStop(BusStop& busStop) {
        busStops.insert(busStop);
		ensureSectorExists(busStop.sector);
		Sector* sec = sectors.search(busStop.sector);
		sec->insertBusStop(busStop.stopId);
    }

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

    Mall* searchMall(const string& mallID) {
        return malls.search(mallID);
    }

    Sector* searchSector(const string& sectorName) {
        return sectors.search(sectorName);
    }

    BusCompany* searchBusCompany(const string& companyId) {
        return busCompanies.search(companyId);
    }

    BusStop* searchBusStop(const string& stopId) {
        return busStops.search(stopId);
    }

    Facility* searchFacility(string& facilityId) {
        return facilities.search(facilityId);
    }

    Bus* searchBusInCompany(const string& companyName, const string& busNo) {
        return busCompanies.searchBusInCompany(companyName, busNo);
	}

    void insertBusToCompany(const string& companyName, Bus* b) {
        busCompanies.insertBusToCompany(companyName, b);
	}

    // Get hash table sizes
    int getHospitalTableSize() { return hospitals.tableSize; }
    int getPharmacyTableSize() { return pharmacies.tableSize; }
    int getSchoolTableSize() { return schools.tableSize; }
    int getPeopleTableSize() { return people.tableSize; }
    int getMallTableSize() { return malls.tableSize; }
    int getFacilityTableSize() { return facilities.tableSize; }
    int getBusCompaniesTableSize() { return busCompanies.tableSize; }
    int getSectorsTableSize() { return sectors.tableSize; }
    int getBusStopsTableSize() { return busStops.tableSize; }

    HospitalNode* getHospitalAt(int i) { return hospitals.table[i]; }
    PharmacyNode* getPharmacyAt(int i) { return pharmacies.table[i]; }
    SchoolNode* getSchoolAt(int i) { return schools.table[i]; }
    PersonNode* getPersonAt(int i) { return people.table[i]; }
    MallNode* getMallAt(int i) { return malls.table[i]; }
    FacilityNode* getFacilityAt(int i) { return facilities.table[i]; }
    BusCompaniesNode* getBusCompanyAt(int i) { return busCompanies.table[i]; }
    SectorNode* getSectorAt(int i) { return sectors.table[i]; }
    BusStopNode* getBusStopAt(int i) { return busStops.table[i]; }

};
