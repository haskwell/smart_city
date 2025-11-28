#pragma once
#include "EducationEntities.h"
#include "SchoolMaxHeap.h"
#include <iostream>

using namespace std;
class EducationSystem {
public:
	MaxHeap schoolMinHeap;

    School* school;
	EducationSystem(): school(nullptr){}

	void registerSchool(School* toAdd){
        if (!school)
        {
            school = toAdd;
        }
        else//could change this to make a linked list of schools
        {
            cout << "\033[33m" << "A school already exists in the system." << "\033[0m" << endl;
        }
	}
	void registerStudent(Person student){}
	void registerFaculty(Person person){}
	School* searchSchoolGraph(string name){}
	School* searchSchoolSubjects(string subject){}
	void showRanking(){}


    School* searchSchool(string schoolName)
    {
        //im making this function assume we are gunna have mutliple schools,
        // idk how they are gunna be stored
        //for now either returns the only school, or nullptr
        if (school->schoolName == schoolName)
        {
            return school;
        }
        else
        {
            return nullptr;
        }
    }

    //the functions are below supposed to be called in the menu,
    //the required function will be called automatically after the input is done
    
    //takes input of school's attributes, and then calls registerSchool
    void registerSchoolINPUT()
    {
        bool correctName = false;
        string name;

        do {
            cout << "Enter School Name: ";
            cin.ignore(); // clear any leftover newline
            getline(cin, name);
            if (name.empty()) {
                cout << "\033[33m" << "Enter a valid School Name" << "\033[0m" << endl;
                correctName = false;
            }
            else {
                correctName = true;
            }
        } while (!correctName);

        string ID;
        cout << "Enter School ID: ";
        cin >> ID;

        string sector;
        cout << "Enter Sector: ";
        cin >> sector;

        float rating;
        cout << "Enter Rating: ";
        cin >> rating;

        int subCount;
        cout << "Enter Number of Subjects: ";
        cin >> subCount;

        School* newSchool = new School(ID, name, sector, rating, subCount);

        // Input subjects if any
        if (subCount > 0) {
            cin.ignore(); // clear newline
            for (int i = 0; i < subCount; i++) {
                cout << "Enter subject " << (i + 1) << ": ";
                getline(cin, newSchool->subjects[i]);
            }
        }
        // Register the school
        registerSchool(newSchool);
    }

    //takes input of student's attributes, and then calls registerStudent
    //right now its not doing shit
    void registerStudentINPUT()
    {
        string name;
        cout << "Enter School Name";
        cin >> name;

        School* tempSchool = searchSchool(name);
        if (!tempSchool)
        {
            cout << "\033[33m" << "School does not Exist! Enter valid School name" << "\033[0m" << endl;
            return;
        }
    }

};