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
    School* searchSchoolGraph(string name) {}
    School* searchSchoolSubjects(string subject) {}
    void showRanking() {}

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
        cls();
        logger->Title("Register Faculty");

        string cnic;
        logger->Prompt("Enter Faculty CNIC: ");
        getline(cin, cnic);

        if (cnic == "") {
            logger->Warning("Enter a valid CNIC");
            pressEnterToContinue();
            return;
        }

        Person* basePerson = db->searchPerson(cnic);
        if (!basePerson) {
            logger->Warning("Person with this CNIC does not exist!");
            pressEnterToContinue();
            return;
        }

        Faculty* facultyPtr = dynamic_cast<Faculty*>(basePerson);


        string schoolId;
        logger->Prompt("Enter School ID: ");
        getline(cin, schoolId);

        if (schoolId == "") {
            logger->Warning("Enter a valid School ID");
            pressEnterToContinue();
            return;
        }

        School* destSchool = db->searchSchool(schoolId);
        if (!destSchool) {
            logger->Warning("School does not exist!");
            pressEnterToContinue();
            return;
        }

        string deptName;
        logger->Prompt("Enter Department Name: ");
        getline(cin, deptName);

        if (deptName == "") {
            logger->Warning("Enter a valid department name");
            pressEnterToContinue();
            return;
        }

        Department* destDept = destSchool->searchDepartment(deptName);
        if (!destDept) {
            logger->Warning("Department does not exist!");
            pressEnterToContinue();
            return;
        }

        string subject;
        logger->Prompt("Enter Subject Faculty Teaches: ");
        getline(cin, subject);

        if (subject == "") {
            logger->Warning("Enter a valid subject");
            pressEnterToContinue();
            return;
        }

        facultyPtr->subject = subject;
        destDept->insertFaculty(facultyPtr);

        logger->Ok("Faculty successfully registered!");
        pressEnterToContinue();
        cls();
    }
    void addStudentsHandler() {
        string schoolId;

        cls();
        logger->Title("REGISTER NEW STUDENT");

        string cnic;
        logger->Prompt("Enter Student CNIC: ");
        getline(cin, cnic);

        if (cnic == "") {
            logger->Error("Enter Valid CNIC");
            return;
        }

        Person* basePerson = db->searchPerson(cnic);

        if (!basePerson) {
            logger->Error("Person with this CNIC does not exist in the system!");
            return;
        }

        Student* toAdd = dynamic_cast<Student*>(basePerson);

        logger->Prompt("Enter School ID: ");
        getline(cin, schoolId);

        School* destSchool = db->searchSchool(schoolId);

        if (!destSchool)
        {
            logger->Error("School Not Found!");
            return;
        }

        string deptName;
        logger->Prompt("Enter Department Name: ");
        cin.ignore();
        getline(cin, deptName);
        if (deptName == "")
        {
            logger->Error("Enter Valid Department Name");
            return;
        }

        Department* destDept = destSchool->searchDepartment(deptName);

        if (!destDept)
        {
            logger->Error("Department Doesnt Exist");
            return;
        }

        string className;
        logger->Prompt("Enter Class Name: ");
        getline(cin, className);

        if (className == "") {
            logger->Error("Enter Valid Class Name");
            return;
        }

        Class* destClass = destDept->searchClass(className);
        if (!destClass)
        {
            logger->Error("Class Not Found in This Department");
            return;
        }



        int code = destSchool->addStudent(toAdd, deptName, className);

        if (code == -1) {
            logger->Warning("Department Not Found(unexpected) ");
            return;
        }
        if (code == -2) {
            logger->Warning("Class Not Found(unexpected)");
            return;
        }

        if (code == 0) {
            logger->Ok("Student Successfully Added!");
        }
        else
        {
            logger->Error("Unknown Error Adding Student!");
        }
        pressEnterToContinue();
        cls();
    }
    void addDepartmentHandler() {
        cls();
        logger->Title("ADD NEW DEPARTMENT");

        string schoolId;
        logger->Prompt("Enter School ID: ");
        getline(cin, schoolId);

        School* destSchool = db->searchSchool(schoolId);
        if (!destSchool) {
            logger->Error("School Not Found!");
            pressEnterToContinue();
            return;
        }

        string deptName;
        logger->Prompt("Enter Department Name: ");
        getline(cin, deptName);

        if (deptName == "") {
            logger->Error("Enter a Valid Department Name");
            pressEnterToContinue();
            return;
        }

        Department* existingDept = destSchool->searchDepartment(deptName);
        if (existingDept)
        {
            logger->Warning("Department Already Exists!");
            pressEnterToContinue();
            return;
        }

        destSchool->addDepartment(deptName);
        logger->Ok("Department Successfully Added!");
        pressEnterToContinue();
        cls();
        return;
    }
    void addClassHandler() {
        cls();
        logger->Title("ADD NEW CLASS");

        string schoolId;
        logger->Prompt("Enter School ID: ");
        getline(cin, schoolId);

        School* destSchool = db->searchSchool(schoolId);
        if (!destSchool) {
            logger->Error("School Not Found!");
            pressEnterToContinue();
            return;
        }

        string deptName;
        logger->Prompt("Enter Department Name: ");
        getline(cin, deptName);

        if (deptName == "") {
            logger->Error("Enter a Valid Department Name");
            pressEnterToContinue();
            return;
        }

        Department* destDept = destSchool->searchDepartment(deptName);
        if (!destDept) {
            logger->Error("Department Not Found!");
            pressEnterToContinue();
            return;
        }

        string className;
        logger->Prompt("Enter Class Name: ");
        getline(cin, className);

        if (className == "") {
            logger->Error("Enter a Valid Class Name");
            pressEnterToContinue();
            return;
        }

        Class* existingClass = destDept->searchClass(className);
        if (existingClass) {
            logger->Warning("Class Already Exists!");
            pressEnterToContinue();
            return;
        }

        destSchool->addClass(deptName, className);
        logger->Ok("Class Successfully Added!");
        pressEnterToContinue();
        cls();
        return;
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