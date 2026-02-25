#pragma once
#include <iostream>
#include "clsTopScreen.h"
#include "clsInputValidate.h"
#include "clsAdmin.h"

using namespace std;

class clsAdminSettingsScreen : protected clsTopScreen
{
private:
    static void _AddAdmin()
    {
        system("cls");
        cout << "New Admin Username: ";
        string u = clsInputValidate::ReadString();
        cout << "New Admin Password: ";
        string p = clsInputValidate::ReadString();

        if (clsAdmin::AddAdmin(u, p))
            cout << "\nAdmin added.\n";
        else
            cout << "\nUsername already exists.\n";

        system("pause");
    }

    static void _ChangePassword()
    {
        system("cls");
        cout << "Admin Username: ";
        string u = clsInputValidate::ReadString();
        cout << "New Password: ";
        string p = clsInputValidate::ReadString();

        if (clsAdmin::ChangeAdminPassword(u, p))
            cout << "\nPassword changed.\n";
        else
            cout << "\nAdmin not found.\n";

        system("pause");
    }

    static void _RemoveAdmin()
    {
        system("cls");
        cout << "Admin Username to remove: ";
        string u = clsInputValidate::ReadString();

        if (clsAdmin::RemoveAdmin(u))
            cout << "\nAdmin removed.\n";
        else
            cout << "\nAdmin not found.\n";

        system("pause");
    }

public:
    static void Show()
    {
        while (true)
        {
            system("cls");
            cout << "================ Admin Settings ================\n";
            cout << "1) Add Admin\n";
            cout << "2) Change Admin Password\n";
            cout << "3) Remove Admin\n";
            cout << "4) Back\n";
            cout << "================================================\n";
            cout << "Choose: ";

            int c = clsInputValidate::ReadIntNumber();
            switch (c)
            {
            case 1: _AddAdmin(); break;
            case 2: _ChangePassword(); break;
            case 3: _RemoveAdmin(); break;
            case 4: return;
            default: cout << "\nInvalid.\n"; system("pause");
            }
        }
    }
};