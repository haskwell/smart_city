#pragma once
#include "EducationEntities.h"
#include "SchoolMaxHeap.h"
#include"../Database/Database.h"

using namespace std;

class EducationSystem {
private:
	Database* db;
    CityLogger* logger;

    void pressEnterToContinue() {
        logger->Prompt("Press Enter to continue...");
        cin.ignore();
    }

    void cls() {
        cout << "\033[2J\033[H";
    }
public:
	MaxHeap schoolMinHeap;

    EducationSystem(Database* d = nullptr, CityLogger* log = nullptr) : db(d), logger(log) {}

    void registerSchool(const School* s) {
        if (!db) return;

        // If the hash table is uninitialized, create it with default size 101
        if (db->schools.tableSize == 0) {
            db->schools = SchoolHashTable(101);
        }

        db->schools.insert(*s);
    }

    void registerStudent(Person student){}
	void registerFaculty(Person person){}
	School* searchSchoolGraph(string name){}
	School* searchSchoolSubjects(string subject){}
	void showRanking(){}

    void registerSchoolsHandler() {
        string schoolID, name, sector;
        float rating;
        int numSubjects;

        cls();

        logger->Title("REGISTER NEW SCHOOL");

        logger->Prompt("Enter School ID: ");
        cin >> schoolID;
        cin.ignore();

        logger->Prompt("Enter School Name: ");
        getline(cin, name);

        logger->Prompt("Enter School Sector: ");
        getline(cin, sector);

        logger->Prompt("Enter School Rating (0.0 - 5.0): ");
        cin >> rating;

        logger->Prompt("Enter Number of Subjects Offered: ");
        cin >> numSubjects;
        cin.ignore();

        // Create school object
        School* newSchool = new School(schoolID, name, sector, rating, numSubjects);

        // Input subjects
        if (numSubjects > 0) {
            logger->Prompt("Enter the subjects:");
            for (int i = 0; i < numSubjects; i++) {
                logger->Prompt("  " + to_string(i + 1) + ". ");
                getline(cin, newSchool->subjects[i]);
            }
        }

        // Register the school
        registerSchool(newSchool);

        logger->Ok("\"" + name + "\" has been registered.");

        pressEnterToContinue();
    }



    void addFacultyHandler() {
       
    }

    void addStudentsHandler() {
        cout << ">>> Add Students - Not implemented yet\n\n";
    }

    void addDepartmentHandler() {
        cout << ">>> Add Department - Not implemented yet\n\n";
    }

    void addClassHandler() {
        cout << ">>> Add Class - Not implemented yet\n\n";
    }

    void searchSchoolBySubjectHandler() {
        cout << ">>> Search School by Subject - Not implemented yet\n\n";
    }

    void rankSchoolsHandler() {
        cout << ">>> Rank Schools - Not implemented yet\n\n";
    }

    void locateNearestSchoolHandler() {
        cout << ">>> Locate Nearest School - Not implemented yet\n\n";
    }
};