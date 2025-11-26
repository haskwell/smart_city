#pragma once
#include "EducationEntities.h"
#include "SchoolGraph.h"
#include "SchoolMinHeap.h"

class EducationSystem {
public:
	SchoolGraph schoolGraph;
	MinHeap schoolMinHeap;

	void registerSchool(School school){}
	void registerStudent(Person student){}
	void registerFaculty(Person person){}
	School* searchSchoolGraph(string name){}
	School* searchSchoolSubjects(string subject){}
	void showRanking(){}
};