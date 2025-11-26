#pragma once
#include <string>
#include "../Population/PopulationEntities.h"
using namespace std;

class Student : public Person {
public:
    double gpa;

    Student(string n = "",
        int a = -99999,
        char g = 'M',
        string cnic = "",
        string s = "",
        int house = 0,
        string o = "",
        double gpaVal = 0.0)
        : Person(n, a, g, cnic, s, house, o), gpa(gpaVal)
    {
    }

    void insertStudent(Student* toAdd){}
    Student* searchStudent(string name){}
};

class Class {
public:
    Student* head;
    Class* nextClass;

    Class() : nextClass(nullptr), head(nullptr) {}

    void addStudent(Student* toAdd){}
    Student* searchStudent(string name){}
    void insertClass(Class* toAdd){}
    Class* searchClass(string className){}
};

class Department {
public:
    Class* classHead;
    Department* nextDepartment;

    Department() : nextDepartment(nullptr), classHead(nullptr) {}

    void insertClass(Class* toAdd){}
    Class* searchClass(string className){}
    void insertDepartment(Department* toAdd){}
    Department* searchDepartment(string departmentName){}
};

class School {
public:
    Department* departmenthead;
    int maxSubject;
    string* subjects;
    float rating;
    string sector;
    string schoolID;
    string name;

    School(string id,
        string n,
        string sec,
        float r,
        int subCount)
        : schoolID(id),
        name(n),
        sector(sec),
        rating(r),
        maxSubject(subCount),
        departmenthead(nullptr)
    {
        if (maxSubject > 0) {
            subjects = new string[maxSubject];
            for (int i = 0; i < maxSubject; i++) {
                subjects[i] = "";
            }
        }
        else {
            subjects = nullptr;
        }
    }

    ~School() {
        if (subjects != nullptr) {
            delete[] subjects;
            subjects = nullptr;
        }
    }

    void insertDepartment(Department* toAdd){}
    Department* searchDepartment(string departmentName){}
};
