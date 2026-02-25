#pragma once
#include <iostream>
#include <iomanip>
#include "clsTopScreen.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"

using namespace std;

class clsAdminStudentsScreen : protected clsTopScreen
{
private:
    static void _ViewAll()
    {
        system("cls");
        cout << "==================== All Students ====================\n";
        auto students = clsAdmin::GetAllStudents();
        if (students.empty())
        {
            cout << "No students found.\n";
            system("pause");
            return;
        }

        cout << left << setw(10) << "ID" << setw(25) << "Name"
            << setw(22) << "Faculty" << setw(18) << "Dept"
            << setw(6) << "Lv" << "\n";
        cout << "------------------------------------------------------\n";

        for (auto& s : students)
        {
            cout << left << setw(10) << s.Id
                << setw(25) << s.FullName
                << setw(22) << s.Faculty
                << setw(18) << s.Department
                << setw(6) << s.Level << "\n";
        }
        cout << "======================================================\n";
        system("pause");
    }

    static void _FindById()
    {
        system("cls");
        cout << "Enter Student ID: ";
        int id = clsInputValidate::ReadIntNumber();

        clsAdmin::stStudent s;
        if (!clsAdmin::FindStudentById(id, s))
        {
            cout << "\nNot found.\n";
            system("pause");
            return;
        }

        cout << "\nFOUND:\n";
        cout << "ID: " << s.Id << "\nName: " << s.FullName << "\nEmail: " << s.Email
            << "\nPhone: " << s.Phone << "\nFaculty: " << s.Faculty
            << "\nDept: " << s.Department << "\nLevel: " << s.Level << "\n";
        system("pause");
    }

    static void _ResetPassword()
    {
        system("cls");
        cout << "Enter Student ID: ";
        int id = clsInputValidate::ReadIntNumber();

        cout << "Enter New Password: ";
        string pass = clsInputValidate::ReadString();

        if (clsAdmin::ResetStudentPassword(id, pass))
            cout << "\nPassword reset successfully.\n";
        else
            cout << "\nStudent not found.\n";

        system("pause");
    }

    static void _DeleteStudent()
    {
        system("cls");
        cout << "Enter Student ID to delete: ";
        int id = clsInputValidate::ReadIntNumber();

        if (clsAdmin::DeleteStudent(id))
            cout << "\nDeleted successfully (student + enrollments + scores).\n";
        else
            cout << "\nStudent not found.\n";

        system("pause");
    }

public:
    static void Show()
    {
        while (true)
        {
            system("cls");
            cout << "================ Manage Students ================\n";
            cout << "1) View All Students\n";
            cout << "2) Find Student By ID\n";
            cout << "3) Reset Student Password\n";
            cout << "4) Delete Student\n";
            cout << "5) Back\n";
            cout << "=================================================\n";
            cout << "Choose: ";

            int c = clsInputValidate::ReadIntNumber();

            switch (c)
            {
            case 1: _ViewAll(); break;
            case 2: _FindById(); break;
            case 3: _ResetPassword(); break;
            case 4: _DeleteStudent(); break;
            case 5: return;
            default:
                cout << "\nInvalid.\n"; system("pause");
            }
        }
    }
};