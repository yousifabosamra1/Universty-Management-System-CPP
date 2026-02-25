#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsTopScreen.h"
#include "Global.h"
#include "clsCourse.h"

using namespace std;

class clsTimetableScreen : protected clsTopScreen
{
private:

    static string _GetCourseName(const string& id)
    {
        if (id == "CI101") return "Intro to Programming";
        if (id == "CI102") return "Discrete Math";
        if (id == "CI103") return "Computer Fundamentals";
        if (id == "CI104") return "English 1";
        if (id == "CI105") return "Critical Thinking";
        if (id == "CI106") return "Intro to Cyber";
        if (id == "CI107") return "Basics of Networks";

        if (id == "CS201") return "OOP";
        if (id == "CS202") return "Data Structures";
        if (id == "CS203") return "Problem Solving";

        if (id == "IS201") return "Database 1";
        if (id == "IT201") return "Network Fundamentals";

        if (id == "AI201") return "Math for AI";

        if (id == "CY201") return "Security Basics";
        if (id == "CY202") return "Linux for Security";
        if (id == "CY203") return "Networking for Security";

        return "Unknown Course";
    }
   

    static string _Day1() { return "Sat"; }
    static string _Day2() { return "Mon"; }
    static string _Day3() { return "Wed"; }

    static string _TimeSlot(int index)
    {

        switch (index % 4)
        {
        case 0: return "09:00 - 10:30";
        case 1: return "11:00 - 12:30";
        case 2: return "13:00 - 14:30";
        default:return "15:00 - 16:30";
        }
    }

public:
    static void ShowTimeTableScreen()
    {
        ShowScreenHeader("Attendance Schedule");

        vector<string> ids = clsCourse::_LoadMyCourseIDs();

        system("cls");
        cout << "\n==================================================Attendance Schedule===================================================\n";
        cout << "Student: " << CurrentUser.StudentId
            << " | " << CurrentUser.FullName << "\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n";

        if (ids.empty())
        {
            cout << "No registered courses to build attendance schedule.\n";
            cout << "====================================================\n";
            system("pause");
            return;
        }

        cout << "| " << left << setw(20) << "CourseID";
        cout << "| " << left << setw(40) << "CourseName";
        cout << "| " << left << setw(10) << "Day";
        cout << "| " << left << setw(25) << "Time";
        cout << "\n------------------------------------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < (int)ids.size(); i++)
        {
            string c = ids[i];
            string name = _GetCourseName(c);
            string time = _TimeSlot(i);

            cout << "| " << left << setw(20) << c;
            cout << "| " << left << setw(40) << name;
            cout << "| " << left << setw(10) << _Day1();
            cout << "| " << left << setw(25) << time << "\n";
        }

        cout << "------------------------------------------------------------------------------------------------------------------------\n\n";
       
    }
};