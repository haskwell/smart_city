#pragma once
#include "EducationEntities.h"
#include "SchoolMaxHeap.h"
#include"../Database/Database.h"

using namespace std;

class EducationSystem {
private:
	Database* db;

public:
	MaxHeap schoolMinHeap;

    EducationSystem(Database* d = nullptr) : db(d) {}

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

        cout << "\n----------------------------------------\n";
        cout << "      REGISTER NEW SCHOOL\n";
        cout << "----------------------------------------\n";

        cout << "Enter School ID: ";
        cin >> schoolID;
        cin.ignore();

        cout << "Enter School Name: ";
        getline(cin, name);

        cout << "Enter School Sector: ";
        getline(cin, sector);

        cout << "Enter School Rating (0.0 - 5.0): ";
        cin >> rating;

        cout << "Enter Number of Subjects Offered: ";
        cin >> numSubjects;
        cin.ignore();

        // Create school object
        School* newSchool = new School(schoolID, name, sector, rating, numSubjects);

        // Input subjects if any
        if (numSubjects > 0) {
            cout << "Enter the subjects:\n";
            for (int i = 0; i < numSubjects; i++) {
                cout << "  " << (i + 1) << ". ";
                getline(cin, newSchool->subjects[i]);
            }
        }

        // Register the school (inserts into heap and DB)
        registerSchool(newSchool);

        cout << "\n>>> Success: \"" << name << "\" has been registered.\n\n";
    }


    void addFacultyHandler() {
        cout << ">>> Add Faculty - Not implemented yet\n\n";
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