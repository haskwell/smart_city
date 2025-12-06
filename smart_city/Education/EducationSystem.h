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
    MaxHeap schoolMaxHeap;

    EducationSystem(Database* d = nullptr, CityLogger* log = nullptr) : db(d), logger(log) {}

    //convert this to int AND REMOVE DB NULLPTR CHECK
    void registerSchool(School* s) {
        if (!db) return;
        db->insertSchool(*s);
    }

    void showRanking() {
        string* top3 = nullptr;
        top3 = schoolMaxHeap.getTop3();
        logger->Title("Top 3 Schools by Rating");
        for (int i = 0; i < 3; i++)
        {
            if (top3[i] == "")
            {
                continue;
            }

            School* tempSchool = db->searchSchool(top3[i]);
            if (tempSchool)
            {
                displaySchoolInfo(tempSchool);
            }
            cout << "\n\n";
        }
    }

    void displaySchoolInfo(School* tempSchool) {
        if (!tempSchool) {
            logger->Error("Null School Pointer!");
            return;
        }
        logger->Info("School ID: " + tempSchool->schoolID);
        logger->Info("School Name: " + tempSchool->schoolName);
        logger->Info("Sector: " + tempSchool->sector);
        logger->Info("Rating: " + to_string(tempSchool->rating));
        logger->Info("Max Subjects: " + to_string(tempSchool->maxSubject));

        // Subjects
        if (tempSchool->subjects && tempSchool->maxSubject > 0) {
            logger->Info("Subjects Offered:");
            for (int i = 0; i < tempSchool->maxSubject; i++) {
                logger->Info("  - " + tempSchool->subjects[i]);
            }
        }
        else {
            logger->Warning("No Subjects Listed");
        }

        // Departments
        if (!tempSchool->departmentHead) {
            logger->Warning("No Departments Added Yet");
        }
        else {
            logger->Info("Departments:");
            Department* curr = tempSchool->departmentHead;
            while (curr) {
                logger->Info("  - " + curr->departmentName);
				// Classes in Department
                if (curr->classHead) {
                    logger->Info("    Classes:");
                    Class* classCurr = curr->classHead;
                    while (classCurr) {
                        logger->Info("      * " + classCurr->className);
                        
						//students in class
                        if (classCurr->Studenthead) {
                            logger->Info("        Students:");
                            Student* studentCurr = classCurr->Studenthead;
                            while (studentCurr) {
                                logger->Info("          - " + studentCurr->name + " (CNIC: " + studentCurr->CNIC + ")");
                                studentCurr = studentCurr->nextStudent;
                            }
                        }
                        else {
                            logger->Warning("        No Students Added Yet");
						}
                        
                        classCurr = classCurr->nextClass;
                    }
                }
                else {
                    logger->Warning("    No Classes Added Yet");
                }
                curr = curr->nextDepartment;
            }
        }
    }

    //ADD INPUT VALIDATION
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
        schoolMaxHeap.insert(newSchool->schoolID, newSchool->rating);
        logger->Ok("\"" + name + "\" has been registered.");

        pressEnterToContinue();
    }

    //ADD INPUT VALIDATION
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
		if (!facultyPtr) {
            logger->Warning("Person with this CNIC is not a Faculty member!");
            pressEnterToContinue();
            return;
        }

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

    //ADD INPUT VALIDATION
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
        if (!toAdd) {
			logger->Error("Person with this CNIC is not a Student!");
			return;
        }

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
    }

    //ADD INPUT VALIDATION
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

    //ADD INPUT VALIDATION
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

    //implement this by using a simple search over the hash table
    void searchSchoolBySubjectHandler() {
        cout << ">>> Search School by Subject - Not implemented yet\n\n";
    }

    //LEAVE THIS ALONE
    void locateNearestSchoolHandler() {
        cout << ">>> Locate Nearest School - Not implemented yet\n\n";
    }

    void listAllSchoolsHandler()
    {
        cls();
		for (int i = 0; i < db->getSchoolTableSize(); i++)
        {
            SchoolNode* tempSchool = db->getSchoolAt(i);
            if (tempSchool)
            {
				displaySchoolInfo(&tempSchool->data);
            }
            cout << "\n\n";
        }
		pressEnterToContinue();
    }
};