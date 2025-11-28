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
};