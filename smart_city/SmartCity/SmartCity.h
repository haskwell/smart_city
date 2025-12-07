#pragma once
#include "Menu.h"
#include "../Transport/TransportSystem.h"
#include "../Education/EducationSystem.h"
#include "../Medicine/MedicalSystem.h"
#include "../Commercial/MallSystem.h"
#include "../Population/PopulationSystem.h"
#include "../Public/FacilitySystem.h"
#include "CityLogger.h"
#include <set>
#include <vector>

using namespace std;

class SmartCity {
public:
    Database* db;

    Menu menu;
    TransportSystem transport;
    EducationSystem education;
    MedicalSystem medical;
    MallSystem commercial;
    PopulationSystem population;
    PublicSystem publicServices;

	CityLogger logger;

    SmartCity()
        : db(new Database()),
        transport(db, &logger),
        education(db, &logger),
        medical(db, &logger),
        commercial(db, &logger),
        population(db, &logger),
        publicServices(db, &logger)
    {
    }

    void run() {
        int choice;
        do {
            choice = menu.showMainMenu();
            switch (choice) {
            case 1: runTransport(); break;
            case 2: runEducation(); break;
            case 3: runMedicine(); break;
            case 4: runPublicServices(); break;
            case 5: runCommercial(); break;
            case 6: runPopulation(); break;
            case 7: printCityGraph(); break;
            case 0:
                cout << "Thank you for using Smart City Management System!\nGoodbye!\n";
                break;
            }
        } while (choice != 0);
    }
    ~SmartCity() {
        delete db;
    }
private:
    void runTransport() {
        int tChoice;
        do {
            tChoice = menu.showTransportMenu();
            switch (tChoice) {
            case 1: transport.registerCompanyHandler(); break;
            case 2: transport.registerBusHandler(); break;
            case 3: transport.addBusStopHandler(); break;
            case 4: transport.addBusRouteHandler(); break;
            case 5: transport.busSimulationWrapper(); break;
            case 6: transport.findShortestPathByTypeHandler(); break;
            case 7: transport.searchBusHandler(); break;
            case 8: transport.listAllCompanies(); break;
            case 9: transport.listAllBusStops(); break;
            }
        } while (tChoice != 0);
    }

    void runEducation() {
        int eChoice;
        do {
            eChoice = menu.showEducationMenu();
            switch (eChoice) {
            case 1: education.registerSchoolsHandler(); break;
            case 2: education.addFacultyHandler(); break;
            case 3: education.addStudentsHandler(); break;
            case 4: education.addDepartmentHandler(); break;
            case 5: education.addClassHandler(); break;
            case 6: education.searchSchoolBySubjectHandler(); break;
            case 7: education.showRanking(); break;
            case 8: education.locateNearestSchoolHandler(); break;
            case 9: education.listAllSchoolsHandler(); break;
            }
        } while (eChoice != 0);
    }

    void runMedicine() {
        int mChoice;
        do {
            mChoice = menu.showMedicineMenu();
            switch (mChoice) {
            case 1: medical.registerHospitalsHandler(); break;
            case 2: medical.registerPharmaciesHandler(); break;
            case 3: medical.addDoctorHandler(); break;
            case 4: medical.addPatientHandler(); break;
            case 5: medical.bookEmergencyBedHandler(); break;
            case 6: medical.searchDoctorHandler(); break;
            case 7: medical.searchPatientHandler(); break;
            case 8: medical.searchMedicineHandler(); break;
            case 9: medical.nearestHospitalLookupHandler(); break;
            case 10: medical.nearestPharmacyLookupHandler(); break;
            case 11: medical.listAllHospitalsHandler(); break;
            case 12: medical.listAllDoctorsHandler(); break;
            case 13: medical.listAllPharmaciesHandler(); break;
            case 14: medical.listAllMedicinesHandler(); break;
            }
        } while (mChoice != 0);
    }

    void runPublicServices() {
        int pChoice;
        do {
            pChoice = menu.showPublicMenu();
            switch (pChoice) {
            case 1: publicServices.addFacilityHandler(); break;
            case 2: publicServices.findNearestUtilityHandler(); break;
            case 3: publicServices.listAllFacility(); break;
            }
        } while (pChoice != 0);
    }

    void runCommercial() {
        int cChoice;
        do {
            cChoice = menu.showCommercialMenu();
            switch (cChoice) {
            case 1: commercial.registerMallsHandler(); break;
            case 2: commercial.addItemsHandler(); break;
            case 3: commercial.itemSearchHandler(); break;
            case 4: commercial.findNearestMallHandler(); break;
            case 5: commercial.listAllMallsHandler(); break;
            case 6: commercial.listAllItemsHandler(); break;
            }
        } while (cChoice != 0);
    }

    void runPopulation() {
        int popChoice;
        do {
            popChoice = menu.showPopulationMenu();
            switch (popChoice) {
            case 1: population.addPeopleHandler(); break;
            case 2: population.searchByCNICHandler(); break;
            case 3: population.generateReportHandler(); break;
            case 4: population.searchSectorHandler(); break;
            case 5: population.searchStreetHandler(); break;
            case 6: population.searchHouseHandler(); break;
            case 7: population.printHierarchyHandler(); break;
            case 8: population.printSectorGridHandler(); break;
            case 9: population.printBuildingsGridHandler(); break;
            }
        } while (popChoice != 0);
    }

    void printCityGraph() {
        logger.Title("CITY GRAPH ADJACENCY LIST");
        db->printEntireGraph();
        logger.Info("End of City Graph");
        menu.pressEnterToContinue();
	}
	public:
	void seedData()
	{
		// deterministic-ish randomness using Database RNG
		auto randInt = [this](int min, int max) -> int {
			if (max <= min) return min;
			return (this->db->randomNumber() % (max - min + 1)) + min;
			};

		auto randChoice = [this](int n) -> int {
			if (n <= 0) return 0;
			return this->db->randomNumber() % n;
			};

		auto randGender = [this](void) -> char {
			return (this->db->randomNumber() % 2) ? 'M' : 'F';
			};

		// Prepare some sector and street names
		const int sectorsCount = 10;
		vector<string> sectors;
		for (int i = 0; i < sectorsCount; ++i) {
			string s = "Sector-" + to_string(i + 1);
			sectors.push_back(s);
			// ensure sector exists in DB grid/hierarchy
			db->ensureSectorExists(s);
		}

		vector<string> streets;
		for (int i = 0; i < 20; ++i) {
			streets.push_back("Street-" + to_string(i + 1));
		}

		// Helper to generate unique CNIC-like id
		auto makeCNIC = [this](int idx) -> string {
			// Use RNG + idx to reduce collisions
			unsigned int r = db->randomNumber();
			return "CNIC-" + to_string(r) + "-" + to_string(idx);
			};

		// 1) 200 random-occupation people (excluding doctor/student/faculty)
		vector<string> occupations = { "engineer", "teacher_assistant", "clerk", "driver", "chef", "barber", "plumber", "electrician", "security", "salesman", "artist", "carpenter" };
		for (int i = 0; i < 200; ++i) {
			string name = "Citizen-" + to_string(i + 1);
			int age = randInt(20, 65);
			char g = randGender();
			string cnic = makeCNIC(i + 1);
			string sector = sectors[randChoice((int)sectors.size())];
			string street = streets[randChoice((int)streets.size())];
			int houseNo = randInt(1, 200);
			string occ = occupations[randChoice((int)occupations.size())];

			Person* p = new Person(name, age, g, cnic, street, houseNo, occ, sector);
			db->insertPerson(p);
		}

		// 2) Create 10 hospitals, each with 20 doctors (total 200 doctors).
		for (int h = 0; h < 10; ++h) {
			string hid = "HOSP-" + to_string(h + 1);
			string hname = "Hospital-" + to_string(h + 1);
			string sector = sectors[randChoice((int)sectors.size())];
			int beds = randInt(10, 200);
			int totalSpecs = randInt(1, 5);
			Hospital* hosp = new Hospital(hname, hid, beds, sector, totalSpecs);

			// Add some placeholder specializations
			for (int sIdx = 0; sIdx < totalSpecs; ++sIdx) {
				if (hosp->specialization) hosp->specialization[sIdx] = "Spec-" + to_string(sIdx + 1);
			}

			// Create 20 doctors and add each to population and hospital immediately
			for (int d = 0; d < 20; ++d) {
				int globalIndex = h * 20 + d + 1;
				string name = "Dr-" + to_string(globalIndex);
				int age = randInt(28, 65);
				char g = randGender();
				string cnic = makeCNIC(globalIndex + 10000);
				string street = streets[randChoice((int)streets.size())];
				int houseNo = randInt(1, 500);
				string specialization = "Gen-" + to_string(randChoice(5) + 1);

				Doctor* doc = new Doctor(name, age, g, cnic, street, houseNo, "doctor", sector, specialization);
				// Insert into population DB
				db->insertPerson(doc);
				// Add to the hospital's doctors table before registering hospital (on-creation)
				hosp->doctorsTable.insert(doc);
			}

			// Register hospital (this inserts into DB and registers beds in heap)
			medical.addHospital(hosp);
		}

		// 3) Create 10 pharmacies, each with 50 medicines
		for (int p = 0; p < 10; ++p) {
			string pid = "PHARM-" + to_string(p + 1);
			string pname = "Pharmacy-" + to_string(p + 1);
			string sector = sectors[randChoice((int)sectors.size())];
			int medCount = 50;
			Pharmacy* pharmacy = new Pharmacy(pid, pname, sector, medCount);

			// Register pharmacy (adds to DB)
			medical.addPharmacy(pharmacy);

			// Fetch pointer from DB (insertPharmacy copies into table; search returns address inside DB)
			Pharmacy* dbPharm = db->searchPharmacy(pid);
			if (dbPharm) {
				for (int m = 0; m < medCount; ++m) {
					string medName = "Med-" + to_string(p + 1) + "-" + to_string(m + 1);
					string formula = "Formula-" + to_string(m + 1);
					float price = static_cast<float>(randInt(100, 2000));
					Medicine* med = new Medicine(medName, formula, price);
					// addMedicine will insert into pharmacy's medicineTable
					medical.addMedicine(med, dbPharm);
				}
			}
		}

		// 4) Create 10 malls, each with 50 items (add items during mall creation)
		for (int m = 0; m < 10; ++m) {
			string mid = "MALL-" + to_string(m + 1);
			string mname = "Mall-" + to_string(m + 1);
			string sector = sectors[randChoice((int)sectors.size())];
			Mall* mall = new Mall(mid, mname, sector);

			// add mall to DB (copies into DB)
			commercial.addMall(mall);

			// Get pointer to mall inside DB
			Mall* dbMall = db->searchMall(mid);
			if (dbMall) {
				for (int it = 0; it < 50; ++it) {
					string prodName = "Item-" + to_string(m + 1) + "-" + to_string(it + 1);
					string category = "Category-" + to_string((it % 8) + 1);
					float price = static_cast<float>(randInt(200, 15000));
					Product prod(prodName, price, category);
					// addProduct will check duplicates and insert into the mall's product table
					commercial.addProduct(prod, dbMall);
				}
			}
		}

		// 5) Create 10 schools, each with 10 teachers and 10 students (teachers/faculty + students added to population and school on-creation)
		for (int s = 0; s < 10; ++s) {
			string sid = "SCH-" + to_string(s + 1);
			string sname = "School-" + to_string(s + 1);
			string sector = sectors[randChoice((int)sectors.size())];
			float rating = static_cast<float>(randInt(1, 5));
			int numSubjects = randInt(1, 6);
			School* school = new School(sid, sname, sector, rating, numSubjects);

			// Fill subjects (simple placeholders)
			for (int subj = 0; subj < numSubjects; ++subj) {
				if (school->subjects) school->subjects[subj] = "Subject-" + to_string(subj + 1);
			}

			// Add a default department & class
			string deptName = "General";
			school->addDepartment(deptName);
			school->addClass(deptName, "Class-A");

			// Create 10 teachers (Faculty) and 10 students and insert into population & school
			for (int t = 0; t < 10; ++t) {
				int idx = s * 20 + t + 1;
				string fname = "Faculty-" + to_string(s + 1) + "-" + to_string(t + 1);
				int age = randInt(25, 65);
				char g = randGender();
				string cnic = makeCNIC(idx + 30000);
				string street = streets[randChoice((int)streets.size())];
				int houseNo = randInt(1, 400);

				Faculty* f = new Faculty(fname, age, g, cnic, street, houseNo, "faculty", sector, "Subject-" + to_string(randChoice(6) + 1));
				db->insertPerson(f);
				// insert into school's department faculty list
				Department* dept = school->searchDepartment(deptName);
				if (dept) dept->insertFaculty(f);
			}

			for (int st = 0; st < 10; ++st) {
				int idx = s * 20 + 10 + st + 1;
				string stname = "Student-" + to_string(s + 1) + "-" + to_string(st + 1);
				int age = randInt(6, 25);
				char g = randGender();
				string cnic = makeCNIC(idx + 40000);
				string street = streets[randChoice((int)streets.size())];
				int houseNo = randInt(1, 400);
				double gpa = static_cast<double>(randInt(200, 400)) / 100.0; // 2.00 - 4.00

				Student* stu = new Student(stname, age, g, cnic, street, houseNo, "student", gpa);
				db->insertPerson(stu);

				// add student to school (department + class)
				school->addStudent(stu, deptName, "Class-A");
			}

			// register the school (inserts into DB)
			education.registerSchool(school);
		}

		// 6) Create 10 public facilities
		for (int f = 0; f < 10; ++f) {
			string fid = "FAC-" + to_string(f + 1);
			string fname = "Facility-" + to_string(f + 1);
			string ftype = (f % 2 == 0) ? "Park" : "PowerPlant";
			string sector = sectors[randChoice((int)sectors.size())];
			Facility fac(ftype, fid, fname, sector);
			db->insertFacility(fac);
		}

		// 7) Create 10 bus stops across random sectors
		vector<string> createdBusStopIds;
		for (int b = 0; b < 10; ++b) {
			string stopId = "BUSSTOP-" + to_string(b + 1);
			string stopName = "BusStop-" + to_string(b + 1);
			string sector = sectors[randChoice((int)sectors.size())];
			float lat = static_cast<float>(randInt(0, 1000));
			float lon = static_cast<float>(randInt(0, 1000));
			db->insertBusStop(*new BusStop(stopName, stopId, sector, lat, lon));
			createdBusStopIds.push_back(stopId);
		}

		// 8) Create a bus company and 10 buses; give each bus a route of 5 stops
		string companyName = "CityTransit";
		db->insertBusCompany(new BusCompany(companyName));
		for (int bi = 0; bi < 10; ++bi) {
			string busNo = "BUS-" + to_string(bi + 1);
			// insert bus into company
			db->insertBusToCompany(companyName, new Bus(busNo, companyName));

			// retrieve bus and add 5 stops (choose 5 random stops, allow repeats)
			Bus* busPtr = db->searchBusInCompany(companyName, busNo);
			if (busPtr) {
				// ensure at least 5 distinct stops if possible
				set<int> used;
				int attempts = 0;
				while ((int)used.size() < 5 && attempts < 50) {
					int idx = randChoice((int)createdBusStopIds.size());
					used.insert(idx);
					attempts++;
				}
				// if not enough distinct, just fill up to 5 picks
				vector<int> indices;
				for (int id : used) indices.push_back(id);
				while ((int)indices.size() < 5) indices.push_back(randChoice((int)createdBusStopIds.size()));

				for (int k = 0; k < 5; ++k) {
					int chosen = indices[k % indices.size()];
					string stopId = createdBusStopIds[chosen];
					busPtr->addStop(stopId);
				}
			}
		}

		// Done seeding - build graph edges after all nodes are present so pathfinding works reasonably
		db->makeEdges();
	}
};
