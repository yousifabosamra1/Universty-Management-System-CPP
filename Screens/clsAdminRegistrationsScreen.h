#pragma once
#include <iostream>
#include <vector>
#include "clsTopScreen.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"

using namespace std;

class clsAdminRegistrationsScreen : protected clsTopScreen
{
private:
    static void _ViewStudentRegistrations()
    {
        system("cls");
        cout << "Enter Student ID: ";
        int id = clsInputValidate::ReadIntNumber();

        auto courses = clsAdmin::GetStudentEnrollments(id);
        cout << "\nCourses registered (" << courses.size() << "):\n";
        cout << "---------------------------------\n";
        for (auto& c : courses) cout << c << "\n";
        cout << "---------------------------------\n";
        system("pause");
    }

    static void _ForceRegister()
    {
        system("cls");
        cout << "Enter Student ID: ";
        int id = clsInputValidate::ReadIntNumber();
        cout << "Enter Course ID: ";
        string cid = clsInputValidate::ReadString();

        if (clsAdmin::ForceRegisterCourse(id, cid))
            cout << "\nRegistered successfully.\n";
        else
            cout << "\nAlready registered.\n";

        system("pause");
    }

    static void _Unregister()
    {
        system("cls");
        cout << "Enter Student ID: ";
        int id = clsInputValidate::ReadIntNumber();
        cout << "Enter Course ID to remove: ";
        string cid = clsInputValidate::ReadString();

        if (clsAdmin::UnregisterCourse(id, cid))
            cout << "\nRemoved successfully.\n";
        else
            cout << "\nNot found.\n";

        system("pause");
    }

public:
    static void Show()
    {
        while (true)
        {
            system("cls");
            cout << "============= Manage Registrations =============\n";
            cout << "1) View Student Registrations\n";
            cout << "2) Force Register Course (Admin)\n";
            cout << "3) Unregister Course\n";
            cout << "4) Back\n";
            cout << "================================================\n";
            cout << "Choose: ";

            int c = clsInputValidate::ReadIntNumber();
            switch (c)
            {
            case 1: _ViewStudentRegistrations(); break;
            case 2: _ForceRegister(); break;
            case 3: _Unregister(); break;
            case 4: return;
            default: cout << "\nInvalid.\n"; system("pause");
            }
        }
    }
};