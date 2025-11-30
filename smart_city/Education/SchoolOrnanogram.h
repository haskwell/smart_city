#pragma once
#include "EducationEntities.h"
#include <iostream>
using namespace std;

class SchoolHierarchy {
public:
    School* parentSchool;

    SchoolHierarchy() : parentSchool(nullptr) {}
    void addDepartment(string deptName)
    {
        Department* toAdd = new Department;
        toAdd->departmentName = deptName;

        if (!parentSchool->departmentHead)
        {
            parentSchool->departmentHead = toAdd;
            return;
        }

        Department* curr = parentSchool->departmentHead;
        while (curr->nextDepartment)
            curr = curr->nextDepartment;

        curr->nextDepartment = toAdd;
    }

    Department* searchDepartment(string deptName)
    {
        Department* curr = parentSchool->departmentHead;

        while (curr)
        {
            if (curr->departmentName == deptName)
                return curr;

            curr = curr->nextDepartment;
        }
        return nullptr;
    }


    void addClass(string deptName, string className)
    {
        Department* dept = searchDepartment(deptName);
        if (!dept) {
            cout << "\033[33mDepartment not found!\033[0m\n";
            return;
        }

        Class* cls = new Class;  // no parameter constructor used
        cls->className = className;

        dept->insertClass(cls);
    }

    Class* searchClass(string deptName, string className)
    {
        Department* dept = searchDepartment(deptName);
        if (!dept) return nullptr;

        return dept->searchClass(className);
    }

    void addStudent(string deptName, string className, Student* stu)
    {
        Class* cls = searchClass(deptName, className);
        if (!cls) {
            cout << "\033[33mClass not found!\033[0m\n";
            return;
        }

        cls->addStudent(stu);
    }

    Student* searchStudent(string studentName)
    {
        Department* dept = parentSchool->departmentHead;

        while (dept)
        {
            Class* cls = dept->classHead;

            while (cls)
            {
                Student* stu = cls->searchStudent(studentName);
                if (stu) return stu;

                cls = cls->nextClass;
            }

            dept = dept->nextDepartment;
        }

        return nullptr;
    }
};
