#pragma once
#include <iostream>
#include "clsTopScreen.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"

using namespace std;

class clsAdminGradesScreen : protected clsTopScreen
{
private:
    static void _AddOrUpdate()
    {
        system("cls");
        clsAdmin::stScore s;

        cout << "Student ID: ";
        s.StudentId = clsInputValidate::ReadIntNumber();

        cout << "Course ID: ";
        s.CourseId = clsInputValidate::ReadString();

        cout << "Quiz (0-10): ";
        s.Quiz = clsInputValidate::ReadshNumberBetween(0, 10);

        cout << "Mid (0-30): ";
        s.Mid = clsInputValidate::ReadshNumberBetween(0, 30);

        cout << "Practical (0-20): ";
        s.Practical = clsInputValidate::ReadshNumberBetween(0, 20);

        cout << "Final (0-40): ";
        s.Final = clsInputValidate::ReadshNumberBetween(0, 40);

        clsAdmin::AddOrUpdateScore(s);
        cout << "\nSaved successfully.\n";
        system("pause");
    }

    static void _Delete()
    {
        system("cls");
        cout << "Student ID: ";
        int sid = clsInputValidate::ReadIntNumber();
        cout << "Course ID: ";
        string cid = clsInputValidate::ReadString();

        if (clsAdmin::DeleteScore(sid, cid))
            cout << "\nDeleted successfully.\n";
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
            cout << "================ Manage Grades ================\n";
            cout << "1) Add / Update Grade (Scores)\n";
            cout << "2) Delete Grade\n";
            cout << "3) Back\n";
            cout << "================================================\n";
            cout << "Choose: ";

            int c = clsInputValidate::ReadIntNumber();
            switch (c)
            {
            case 1: _AddOrUpdate(); break;
            case 2: _Delete(); break;
            case 3: return;
            default: cout << "\nInvalid.\n"; system("pause");
            }
        }
    }
};