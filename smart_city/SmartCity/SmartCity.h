#pragma once
#include "Menu.h"
#include "../Transport/TransportSystem.h"
#include "../Education/EducationSystem.h"
#include "../Medicine/MedicalSystem.h"
#include "../Commercial/MallSystem.h"
#include "../Population/PopulationSystem.h"
#include "../Public/FacilitySystem.h"
#include "CityLogger.h"

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
		int randInt(int min, int max) {
			if (max <= min) return min;
			return (db->randomNumber() % (max - min + 1)) + min;
		}

		int randChoice(int n) {
			if (n <= 0) return 0;
			return db->randomNumber() % n;
		}

		char randGender() {
			return (db->randomNumber() % 2) ? 'M' : 'F';
		}

		string makeCNIC(int idx) {
			unsigned int r = db->randomNumber();
			return "CNIC-" + to_string(r) + "-" + to_string(idx);
		}

		void seedData() {
			// Prepare sector names and ensure they exist
			const int sectorsCount = 10;
			string sectors[10];
			for (int i = 0; i < sectorsCount; ++i) {
				sectors[i] = "Sector-" + to_string(i + 1);
				db->ensureSectorExists(sectors[i]);
			}

			// Prepare street names
			string streets[20];
			for (int i = 0; i < 20; ++i) {
				streets[i] = "Street-" + to_string(i + 1);
			}

			// 1) Create 200 random-occupation people (excluding doctor/student/faculty)
			string occupations[] = { "engineer", "teacher_assistant", "clerk", "driver", "chef",
				"barber", "plumber", "electrician", "security", "salesman", "artist", "carpenter" };
			int occupationsCount = 12;

			for (int i = 0; i < 200; ++i) {
				string name = "Citizen-" + to_string(i + 1);
				int age = randInt(20, 65);
				char g = randGender();
				string cnic = makeCNIC(i + 1);
				string sector = sectors[randChoice(sectorsCount)];
				string street = streets[randChoice(20)];
				int houseNo = randInt(1, 200);
				string occ = occupations[randChoice(occupationsCount)];

				Person* p = new Person(name, age, g, cnic, street, houseNo, occ, sector);
				db->insertPerson(p);
			}

			// 2) Create 10 hospitals, each with 20 doctors
			for (int h = 0; h < 10; ++h) {
				string hid = "HOSP-" + to_string(h + 1);
				string hname = "Hospital-" + to_string(h + 1);
				string sector = sectors[randChoice(sectorsCount)];
				int beds = randInt(10, 200);
				int totalSpecs = randInt(1, 5);
				Hospital* hosp = new Hospital(hname, hid, beds, sector, totalSpecs);

				// Add placeholder specializations
				for (int sIdx = 0; sIdx < totalSpecs; ++sIdx) {
					if (hosp->specialization) hosp->specialization[sIdx] = "Spec-" + to_string(sIdx + 1);
				}

				// Create 20 doctors
				for (int d = 0; d < 20; ++d) {
					int globalIndex = h * 20 + d + 1;
					string name = "Dr-" + to_string(globalIndex);
					int age = randInt(28, 65);
					char g = randGender();
					string cnic = makeCNIC(globalIndex + 10000);
					string street = streets[randChoice(20)];
					int houseNo = randInt(1, 500);
					string specialization = "Gen-" + to_string(randChoice(5) + 1);

					Doctor* doc = new Doctor(name, age, g, cnic, street, houseNo, "doctor", sector, specialization);
					db->insertPerson(doc);
					hosp->doctorsTable.insert(doc);
				}

				medical.addHospital(hosp);
			}

			// 3) Create 10 pharmacies, each with 50 medicines
			for (int p = 0; p < 10; ++p) {
				string pid = "PHARM-" + to_string(p + 1);
				string pname = "Pharmacy-" + to_string(p + 1);
				string sector = sectors[randChoice(sectorsCount)];
				int medCount = 50;
				Pharmacy* pharmacy = new Pharmacy(pid, pname, sector, medCount);

				medical.addPharmacy(pharmacy);

				Pharmacy* dbPharm = db->searchPharmacy(pid);
				if (dbPharm) {
					for (int m = 0; m < medCount; ++m) {
						string medName = "Med-" + to_string(p + 1) + "-" + to_string(m + 1);
						string formula = "Formula-" + to_string(m + 1);
						float price = static_cast<float>(randInt(100, 2000));
						Medicine* med = new Medicine(medName, formula, price);
						medical.addMedicine(med, dbPharm);
					}
				}
			}

			// 4) Create 10 malls, each with 50 items
			for (int m = 0; m < 10; ++m) {
				string mid = "MALL-" + to_string(m + 1);
				string mname = "Mall-" + to_string(m + 1);
				string sector = sectors[randChoice(sectorsCount)];
				Mall* mall = new Mall(mid, mname, sector);

				commercial.addMall(mall);

				Mall* dbMall = db->searchMall(mid);
				if (dbMall) {
					for (int it = 0; it < 50; ++it) {
						string prodName = "Item-" + to_string(m + 1) + "-" + to_string(it + 1);
						string category = "Category-" + to_string((it % 8) + 1);
						float price = static_cast<float>(randInt(200, 15000));
						Product prod(prodName, price, category);
						commercial.addProduct(prod, dbMall);
					}
				}
			}

			// 5) Create 10 schools, each with 10 teachers and 10 students
			for (int s = 0; s < 10; ++s) {
				string sid = "SCH-" + to_string(s + 1);
				string sname = "School-" + to_string(s + 1);
				string sector = sectors[randChoice(sectorsCount)];
				float rating = static_cast<float>(randInt(1, 5));
				int numSubjects = randInt(1, 6);
				School* school = new School(sid, sname, sector, rating, numSubjects);

				// Fill subjects
				for (int subj = 0; subj < numSubjects; ++subj) {
					if (school->subjects) school->subjects[subj] = "Subject-" + to_string(subj + 1);
				}

				// Add department and class
				string deptName = "General";
				school->addDepartment(deptName);
				school->addClass(deptName, "Class-A");

				// Create 10 teachers
				for (int t = 0; t < 10; ++t) {
					int idx = s * 20 + t + 1;
					string fname = "Faculty-" + to_string(s + 1) + "-" + to_string(t + 1);
					int age = randInt(25, 65);
					char g = randGender();
					string cnic = makeCNIC(idx + 30000);
					string street = streets[randChoice(20)];
					int houseNo = randInt(1, 400);

					Faculty* f = new Faculty(fname, age, g, cnic, street, houseNo, "faculty", sector,
						"Subject-" + to_string(randChoice(6) + 1));
					db->insertPerson(f);
					Department* dept = school->searchDepartment(deptName);
					if (dept) dept->insertFaculty(f);
				}

				// Create 10 students
				for (int st = 0; st < 10; ++st) {
					int idx = s * 20 + 10 + st + 1;
					string stname = "Student-" + to_string(s + 1) + "-" + to_string(st + 1);
					int age = randInt(6, 25);
					char g = randGender();
					string cnic = makeCNIC(idx + 40000);
					string street = streets[randChoice(20)];
					int houseNo = randInt(1, 400);
					double gpa = static_cast<double>(randInt(200, 400)) / 100.0;

					Student* stu = new Student(stname, age, g, cnic, street, houseNo, "student", gpa);
					db->insertPerson(stu);
					school->addStudent(stu, deptName, "Class-A");
				}

				education.registerSchool(school);
			}

			// 6) Create 10 public facilities
			for (int f = 0; f < 10; ++f) {
				string fid = "FAC-" + to_string(f + 1);
				string fname = "Facility-" + to_string(f + 1);
				string ftype = (f % 2 == 0) ? "Park" : "PowerPlant";
				string sector = sectors[randChoice(sectorsCount)];
				Facility fac(ftype, fid, fname, sector);
				db->insertFacility(fac);
			}

			// 7) Create 10 bus stops
			string createdBusStopIds[10];
			for (int b = 0; b < 10; ++b) {
				string stopId = "BUSSTOP-" + to_string(b + 1);
				string stopName = "BusStop-" + to_string(b + 1);
				string sector = sectors[randChoice(sectorsCount)];
				float lat = static_cast<float>(randInt(0, 1000));
				float lon = static_cast<float>(randInt(0, 1000));
				db->insertBusStop(*new BusStop(stopName, stopId, sector, lat, lon));
				createdBusStopIds[b] = stopId;
			}

			// 8) Create bus company and 10 buses with routes
			string companyName = "CityTransit";
			db->insertBusCompany(new BusCompany(companyName));

			for (int bi = 0; bi < 10; ++bi) {
				string busNo = "BUS-" + to_string(bi + 1);
				db->insertBusToCompany(companyName, new Bus(busNo, companyName));

				Bus* busPtr = db->searchBusInCompany(companyName, busNo);
				if (busPtr) {
					// Track which stop indices we've used
					bool usedStops[10];
					for (int i = 0; i < 10; ++i) usedStops[i] = false;

					int distinctCount = 0;
					int attempts = 0;

					// Try to get 5 distinct stops
					while (distinctCount < 5 && attempts < 50) {
						int idx = randChoice(10);
						if (!usedStops[idx]) {
							usedStops[idx] = true;
							distinctCount++;
						}
						attempts++;
					}

					// Collect selected indices
					int selectedIndices[5];
					int selectedCount = 0;
					for (int i = 0; i < 10 && selectedCount < 5; ++i) {
						if (usedStops[i]) {
							selectedIndices[selectedCount] = i;
							selectedCount++;
						}
					}

					// Fill remaining slots if needed
					while (selectedCount < 5) {
						selectedIndices[selectedCount] = randChoice(10);
						selectedCount++;
					}

					// Add stops to bus route
					for (int k = 0; k < 5; ++k) {
						int chosen = selectedIndices[k % 5];
						string stopId = createdBusStopIds[chosen];
						busPtr->addStop(stopId);
					}
				}
			}
		}
};
