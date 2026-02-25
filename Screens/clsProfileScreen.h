#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsTopScreen.h"
#include "clsStudent.h"
#include "Global.h"
using namespace std;

class clsProfileScreen : protected clsTopScreen
{
private:


    static void _PrintInfo()
    {
        cout << "\n Student Info";
        cout << "\n================================\n";
        cout << " ID: " << CurrentUser.StudentId;
        cout << "\n Name: " << CurrentUser.FullName;
        cout << "\n Password: " << CurrentUser.Password;
        cout << "\n Email: " << CurrentUser.Email;
        cout << "\n Phone: " << CurrentUser.Phone;
        cout << "\n Faculty Of: " << CurrentUser.Faculty;
        cout << "\n Deparment: " << CurrentUser.Department;
        cout << "\n Level: " << CurrentUser.Level;
        cout << "\n================================\n";
    }
public:
    static void ShowProfileScreen()
    {
        system("cls");
        ShowScreenHeader("Profile Screen");

        if (CurrentUser.IsEmpty())
        {
            cout << "\nNo user logged in.\n";
            cout << "Please login first.\n";
            return;
        }
        string currentPass;
        cout << "\nPlease Enter Your Current Password: ";
        currentPass = clsInputValidate::ReadString();

        while (currentPass != CurrentUser.Password)
        {
            cout << "\nThe password is incorrect! Try again.\n";
            cout << "\nPlease Enter Your Current Password: ";
            currentPass = clsInputValidate::ReadString();
        }
        _PrintInfo();

   }
};
