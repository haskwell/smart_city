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


class Faculty : public Person {
public:
    string subject;
    Faculty* nextFaculty;
    Faculty(string n = "", int a = -99999, char g = 'M',
        string cnic = "", string s = "", int house = 0, string o = "",
        string sec = "", string subj = "")
        : Person(n, a, g, cnic, s, house, o, sec), subject(subj), nextFaculty(nullptr) {
    }

    ~Faculty() override {}
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
    Faculty* facultyHead;
    Department* nextDepartment;
    string departmentName;

    Department(string name = "") : facultyHead(nullptr), nextDepartment(nullptr), classHead(nullptr), departmentName(name) {}

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
    void insertFaculty(Faculty* toAdd)
    {
        if (!facultyHead)
        {
            facultyHead = toAdd;
            return;
        }
        Faculty* curr = facultyHead;
        while (curr->nextFaculty)
        {
            curr = curr->nextFaculty;
        }
        curr->nextFaculty = toAdd;
    }

    Faculty* searchFaculty(string name) {
        Faculty* curr = facultyHead;
        while (curr)
        {
            if (curr->name == name) {
                return curr;
            }
            curr = curr->nextFaculty;
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
    double latitude;
    double longitude;

    School(string id = 0,
        string n = "",
        string sec = "",
        float r = 0.0,
        int subCount = 0)
        : schoolID(id),
        latitude(0.0),
        longitude(0.0),
        schoolName(n),
        sector(sec),
        rating(r),
        maxSubject(subCount),
        departmentHead(nullptr)
    {
        if (maxSubject > 0) {
            subjects = new string[maxSubject];
            for (int i = 0; i < maxSubject; i++)
                subjects[i] = "";
        }
        else {
            subjects = nullptr;
        }
    }

    int addStudent(Student* toAdd, string department, string classname)
    {
        Department* destDept = searchDepartment(department);

        if (!destDept)
        {
            return -1;
        }

        Class* destClass = destDept->searchClass(classname);

        if (!destClass)
        {
            return -2;
        }

        destClass->addStudent(toAdd);
        return 0;
    }

    // =====================================================
    // Add Department
    // =====================================================
    void addDepartment(string name)
    {
        Department* d = new Department;

        d->departmentName = name;

        if (!departmentHead) {
            departmentHead = d;
            return;
        }

        Department* curr = departmentHead;
        while (curr->nextDepartment)
            curr = curr->nextDepartment;

        curr->nextDepartment = d;
    }

    // =====================================================
    // Search Department
    // =====================================================
    Department* searchDepartment(string deptName)
    {

        Department* curr = departmentHead;
        while (curr) {
            if (curr->departmentName == deptName)
                return curr;
            curr = curr->nextDepartment;
        }
        return nullptr;
    }

    // =====================================================
    // Add Class to Department
    // =====================================================
    void addClass(string deptName, string className)
    {
        Department* dept = searchDepartment(deptName);
        if (!dept)
        {
            cout << "\033[31mDepartment doesn't exist!\033[0m\n";
            return;
        }

        Class* cls = new Class;
        cls->className = className;
        dept->insertClass(cls);
    }

    Class* searchClass(string deptName, string className)
    {
        Department* dept = searchDepartment(deptName);
        if (!dept) {
            cout << "\033[31mDepartment doesn't exist!\033[0m\n";
            return nullptr;
        }

        Class* cls = dept->searchClass(className);
        return cls;
    }

    // =====================================================
    // Add Student to Class
    // =====================================================
    void addStudent(string deptName, string className, Student* stu)
    {
        if (!stu) {
            cout << "\033[31m[ERROR] Student pointer is NULL! Cannot add student.\033[0m\n";
            return;
        }

        Class* cls = searchClass(deptName, className);
        if (!cls) {
            cout << "\033[31m[ERROR] Cannot add student. Class is NULL!\033[0m\n";
            return;
        }

        cls->addStudent(stu);
    }

    // =====================================================
    // Search Student across School
    // =====================================================
    Student* searchStudent(string studentName)
    {
        if (!departmentHead)
        {
            return nullptr;
        }

        Department* dept = departmentHead;
        while (dept)
        {
            Class* cls = dept->classHead;
            while (cls) {
                Student* stu = cls->searchStudent(studentName);
                if (stu) return stu;
                cls = cls->nextClass;
            }
            dept = dept->nextDepartment;
        }
        return nullptr;
    }

    // =====================================================
    // Destructor
    // =====================================================
    ~School() {
        if (subjects != nullptr) {
            delete[] subjects;
            subjects = nullptr;
        }
    }
};
