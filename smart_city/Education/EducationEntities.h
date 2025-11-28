#pragma once
#include <string>
#include "../Population/PopulationEntities.h"
using namespace std;

class Student : public Person {
public:
    double gpa;
    Student* nextStudent;

    Student(string n = "",
        int a = -99999,
        char g = 'M',
        string cnic = "",
        string s = "",
        int house = 0,
        string o = "",
        double gpaVal = 0.0)
        : Person(n, a, g, cnic, s, house, o), gpa(gpaVal), nextStudent(nullptr)
    {
    }
};

class Class {
public:
    Student* Studenthead;
    Class* nextClass;
    string className;

    Class(string name = "") : nextClass(nullptr), Studenthead(nullptr), className(name) {}

    //takes in Student object pointer, adds it to student inkedList starting from StudentHead
    void addStudent(Student* toAdd) {
        if (!Studenthead)
        {
            Studenthead = toAdd;
            return;
        }

        Student* currStudent = nullptr;
        currStudent = Studenthead;

        while (currStudent->nextStudent)
        {
            currStudent = currStudent->nextStudent;
        }

        currStudent->nextStudent = toAdd;
    }

    //takes in Student object pointer, searches it in linkedList starting from StudentHead, and returns it
    Student* searchStudent(string name) {
        Student* currStudent = Studenthead;

        while (currStudent)
        {
            if (currStudent->name == name)
            {
                return currStudent;
            }
            currStudent = currStudent->nextStudent;
        }
        return nullptr;
    }
};

class Department {
public:
    Class* classHead;
    Department* nextDepartment;
    string departmentName;

    Department(string name = "") : nextDepartment(nullptr), classHead(nullptr), departmentName(name) {}

    //Takes in class object pointer, adds it to LinkedList starting from classHead
    void insertClass(Class* toAdd) {
        if (!classHead)
        {
            classHead = toAdd;
            return;
        }

        Class* currClass = nullptr;
        currClass = classHead;
        while (currClass->nextClass)
        {
            currClass = currClass->nextClass;
        }

        currClass->nextClass = toAdd;
    }

    //Takes in class object pointer, searches it in LinkedList starting from classHead, and returns it
    Class* searchClass(string className) {
        Class* currClass = classHead;

        while (currClass)
        {
            if (currClass->className == className)
            {
                return currClass;
            }
            currClass = currClass->nextClass;
        }
        return nullptr;
    }
};

class School {
public:
    Department* departmentHead;
    int maxSubject;
    string* subjects;
    string schoolName;
    float rating;
    string sector;
    string schoolID;

    School(string id = 0,
        string n = "",
        string sec = "",
        float r = 0.0,
        int subCount = 0
    )
        : schoolID(id),
        schoolName(n),
        sector(sec),
        rating(r),
        maxSubject(subCount),
        departmentHead(nullptr)
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
    //takes in department object pointer, adds to linkedList starting from departmentHead
    void insertDepartment(Department* toAdd)
    {
        if (!departmentHead)
        {
            departmentHead = toAdd;
            return;
        }

        Department* currDepartment = departmentHead;

        while (currDepartment->nextDepartment)
        {
            currDepartment = currDepartment->nextDepartment;
        }

        currDepartment->nextDepartment = toAdd;
        return;
    }
    //takes in department object pointer, searches it in linkedList starting from departmentHead, and returns;
    Department* searchDepartment(string departmentName) {
        Department* currDepartment = departmentHead;

        while (currDepartment)
        {
            if (currDepartment->departmentName == departmentName)
            {
                return currDepartment;
            }
            currDepartment = currDepartment->nextDepartment;
        }

        return nullptr;
    }

    ~School() {
        if (subjects != nullptr) {
            delete[] subjects;
            subjects = nullptr;
        }
    }
};