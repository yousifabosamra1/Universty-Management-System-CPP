#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
#include "clsTopScreen.h"
#include "Global.h"
#include "clsStudent.h"
#include "clsCourse.h"

using namespace std;

class clsSubjectScreen : protected clsTopScreen
{
private:
   

    static vector<clsCourse::stCourseInfo> _Catalog()
    {

        return {
            {"CI101","Intro to Programming",3},{"CI102","Discrete Math",3},{"CI103","Computer Fundamentals",2},
            {"CI104","English 1",2},{"CI105","Critical Thinking",2},{"CI106","Intro to Cyber",2},{"CI107","Basics of Networks",2},

            {"CS201","OOP",3},{"CS202","Data Structures",3},{"CS203","Problem Solving",2},{"CS204","Computer Organization",3},
            {"CS205","C++ Projects",2},{"CS206","Git & Version Control",2},{"CS207","Intro to Algorithms",3},

            {"IS201","Database 1",3},{"IS202","SQL Lab",2},{"IS203","Data Modeling",2},{"IS204","Business Basics",2},
            {"IS205","Web Fundamentals",2},{"IS206","Excel for Data",2},{"IS207","Intro to Systems",3},

            {"IT201","Network Fundamentals",3},{"IT202","Routing Basics",3},{"IT203","Switching Basics",3},
            {"IT204","Windows Admin 1",2},{"IT205","Linux Basics",2},{"IT206","Virtualization",2},{"IT207","Troubleshooting",2},

            {"AI201","Math for AI",3},{"AI202","Python Basics",3},{"AI203","Data Analysis 1",2},{"AI204","Probability",3},
            {"AI205","Linear Algebra",3},{"AI206","Intro to ML",3},{"AI207","ML Lab 1",2},

            {"CY201","Security Basics",3},{"CY202","Linux for Security",2},{"CY203","Networking for Security",3},{"CY204","Web Basics",2},
            {"CY205","Ethical Hacking Intro",2},{"CY206","Cryptography Intro",2},{"CY207","Security Lab 1",2},
        };
    }
    static clsCourse::stCourseInfo _FindCourse(const string& id)
    {
        for (auto& c : _Catalog())
            if (c.CourseID == id) return c;


        return { id, "Unknown Course", 0 };
    }
    

public:
    static void ShowSubjectScreen()
    {
        ShowScreenHeader("My Registered Courses");

        vector<string> ids = clsCourse::_LoadMyCourseIDs();

        system("cls");
        cout << "==================== My Courses ====================\n";
        cout << "Student: " << CurrentUser.StudentId
            << " | " << CurrentUser.FullName << "\n";
        cout << "----------------------------------------------------\n";

        if (ids.empty())
        {
            cout << "No registered courses yet.\n";
            cout << "====================================================\n";
            system("pause");
            return;
        }

        int totalCH = 0;
        for (auto& id : ids)
        {
            clsCourse::stCourseInfo c = _FindCourse(id);
            totalCH += c.CreditHours;

            cout << c.CourseID << " | " << c.CourseName << " | CH: " << c.CreditHours << "\n";
        }

        cout << "----------------------------------------------------\n";
        cout << "Total Credit Hours: " << totalCH << "\n";
        cout << "====================================================\n";
      
    }
};