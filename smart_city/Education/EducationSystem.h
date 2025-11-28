#pragma once
#include "EducationEntities.h"
#include "SchoolMaxHeap.h"

class EducationSystem {
public:
	MaxHeap schoolMinHeap;

	EducationSystem(){}

	void registerSchool(School school){}
	void registerStudent(Person student){}
	void registerFaculty(Person person){}
	School* searchSchoolGraph(string name){}
	School* searchSchoolSubjects(string subject){}
	void showRanking(){}

    void registerSchoolsHandler() {
        cout << ">>> Register Schools - Not implemented yet\n\n";
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