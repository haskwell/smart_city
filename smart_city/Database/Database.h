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
#include "SectorGrid.h"
#include "CityGraph.h"
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
	SectorGrid sectorGrid;

    CityHierarchy cityHierarchy;
	GraphManager cityGraph;

public:

    Database() {
		sectorGrid.setUpGrid(625, 625);
    }

    void convertToGlobal(int &x, int &y, int gX, int gY) {
        x = gX + x;
        y = gY + y;
    }

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

    Coords ensureSectorExists(const string& sectorName) {
        if (sectors.search(sectorName) == nullptr) {
            Sector* newSector = new Sector();
            newSector->name = sectorName;
            sectors.insert(*newSector);
            cityHierarchy.addSector(newSector);
            return sectorGrid.addSectorIntoGrid(newSector->name);
        }
        else {
            return sectorGrid.getCoordsBySector(sectorName);
        }
    }

    void insertHospital(Hospital& hospital) {
        hospitals.insert(hospital);
        Coords secCoords = ensureSectorExists(hospital.sector);   // Get sector's top-left coordinates
        Sector* sec = sectors.search(hospital.sector);
        Coords localCoords = sec->insertHospital(hospital.id);    // Local sector coordinates
        convertToGlobal(localCoords.x, localCoords.y, secCoords.x, secCoords.y);
        hospital.latitude = localCoords.x;
        hospital.longitude = localCoords.y;
        cityGraph.add(hospital.id, hospital.latitude, hospital.longitude, cityGraph.hospitalTag);
    }

    void insertPharmacy(Pharmacy& pharmacy) {
        pharmacies.insert(pharmacy);
        Coords secCoords = ensureSectorExists(pharmacy.sector);
        Sector* sec = sectors.search(pharmacy.sector);
        Coords localCoords = sec->insertPharmacy(pharmacy.id);
        convertToGlobal(localCoords.x, localCoords.y, secCoords.x, secCoords.y);
        pharmacy.latitude = localCoords.x;
        pharmacy.longitude = localCoords.y;
        cityGraph.add(pharmacy.id, pharmacy.latitude, pharmacy.longitude, cityGraph.pharmacyTag);
    }

    void insertSchool(School& school) {
        schools.insert(school);
        Coords secCoords = ensureSectorExists(school.sector);
        Sector* sec = sectors.search(school.sector);
        Coords localCoords = sec->insertSchool(school.schoolID);
        convertToGlobal(localCoords.x, localCoords.y, secCoords.x, secCoords.y);
        school.latitude = localCoords.x;
        school.longitude = localCoords.y;
        cityGraph.add(school.schoolID, school.latitude, school.longitude, cityGraph.schoolTag);
    }

    void insertPerson(Person* person) {
        people.insert(person);
        cityHierarchy.addPerson(person);
        ensureSectorExists(person->sector);
		Sector* sec = sectors.search(person->sector);
        sectorGrid.addSectorIntoGrid(sec->name);
    }

    void insertMall(Mall& mall) {
        malls.insert(mall);
        Coords secCoords = ensureSectorExists(mall.sector);
        Sector* sec = sectors.search(mall.sector);
        Coords localCoords = sec->insertMall(mall.mallId);
        convertToGlobal(localCoords.x, localCoords.y, secCoords.x, secCoords.y);
        mall.latitude = localCoords.x;
        mall.longitude = localCoords.y;
        cityGraph.add(mall.mallId, mall.latitude, mall.longitude, cityGraph.commercialTag);
    }

    void insertSector(Sector& sector) {
        sectors.insert(sector);
        cityHierarchy.addSector(&sector);
		sectorGrid.addSectorIntoGrid(sector.name);
    }

    void printSectorsInGrid() {
        for (int i = 0; i < sectorGrid.rows; i++) {
            for (int j = 0; j < sectorGrid.cols; j++) {
                if (sectorGrid.grid[i][j] != "") {
                    cout << sectorGrid.grid[i][j] << "\t";
                } else {
                    cout << "-\t";
                }
            }
            cout << endl;
        }
	}

    void printEntireGraph() {
		cityGraph.printEntireGraph();
    }

    void insertFacility(Facility& facility) {
        facilities.insert(facility);
        Coords secCoords = ensureSectorExists(facility.sector);
        Sector* sec = sectors.search(facility.sector);
        Coords localCoords = sec->insertPublicFacility(facility.id);
        convertToGlobal(localCoords.x, localCoords.y, secCoords.x, secCoords.y);
        facility.latitude = localCoords.x;
        facility.longitude = localCoords.y;
    }

    void insertBusCompany(BusCompany& company) {
        busCompanies.insert(company);
    }

    void insertBusStop(BusStop& busStop) {
        busStops.insert(busStop);
        Coords secCoords = ensureSectorExists(busStop.sector);
        Sector* sec = sectors.search(busStop.sector);
        Coords localCoords = sec->insertBusStop(busStop.stopId);
        convertToGlobal(localCoords.x, localCoords.y, secCoords.x, secCoords.y);
        busStop.latitude = localCoords.x;
        busStop.longitude = localCoords.y;
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

    void makeEdges() {
		cityGraph.makeEdges();
    }

    BusCompaniesHashTable& getBuses()
    {
        return busCompanies;
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
