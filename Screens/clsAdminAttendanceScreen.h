#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsTopScreen.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"

using namespace std;

class clsAdminAttendanceScreen : protected clsTopScreen
{
private:
    static string _Slot(int i)
    {
        switch (i % 4)
        {
        case 0: return "09:00 - 10:30";
        case 1: return "11:00 - 12:30";
        case 2: return "13:00 - 14:30";
        default:return "15:00 - 16:30";
        }
    }

    static void _ShowForStudent()
    {
        system("cls");
        cout << "Enter Student ID: ";
        int sid = clsInputValidate::ReadIntNumber();

        auto ids = clsAdmin::GetStudentEnrollments(sid);
        if (ids.empty())
        {
            cout << "\nNo registered courses.\n";
            system("pause");
            return;
        }

        cout << "\n=========== Attendance Schedule (Fake) ===========\n";
        cout << "Student ID: " << sid << "\n";
        cout << "CourseID | Day | Time\n";
        cout << "--------------------------------------------------\n";

        for (int i = 0; i < (int)ids.size(); i++)
        {
            string time = _Slot(i);
            cout << ids[i] << " | Sat | " << time << "\n";
            cout << ids[i] << " | Mon | " << time << "\n";
            cout << ids[i] << " | Wed | " << time << "\n";
            cout << "--------------------------------------------------\n";
        }

        system("pause");
    }

public:
    static void Show()
    {
        while (true)
        {
            system("cls");
            cout << "============= Attendance Monitor =============\n";
            cout << "1) View Student Attendance Schedule\n";
            cout << "2) Back\n";
            cout << "=============================================\n";
            cout << "Choose: ";

            int c = clsInputValidate::ReadIntNumber();
            switch (c)
            {
            case 1: _ShowForStudent(); break;
            case 2: return;
            default: cout << "\nInvalid.\n"; system("pause");
            }
        }
    }
};