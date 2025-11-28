#pragma once
#include "EducationEntities.h"
#include "SchoolGraph.h"
#include "SchoolMaxHeap.h"
//nigger
class EducationSystem {
public:
	SchoolGraph schoolGraph;
	MaxHeap schoolMinHeap;

	EducationSystem(){}

	void registerSchool(School school){}
	void registerStudent(Person student){}
	void registerFaculty(Person person){}
	School* searchSchoolGraph(string name){}
	School* searchSchoolSubjects(string subject){}
	void showRanking(){}
};