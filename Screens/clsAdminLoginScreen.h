#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "clsTopScreen.h"
#include "clsInputValidate.h"
#include "clsAdminMainMenuScreen.h"
using namespace std;

class clsAdminLoginScreen : protected clsTopScreen
{
private:
    static bool _CheckAdmin(const string& user, const string& pass)
    {
        ifstream in("Admins.txt");
        if (!in) return (user == "admin" && pass == "1234"); 

        string line;
        while (getline(in, line))
        {
            size_t p = line.find("#//#");
            if (p == string::npos) continue;
            string u = line.substr(0, p);
            string pw = line.substr(p + 4);
            if (u == user && pw == pass) return true;
        }
        return false;
    }

public:
    static void ShowAdminLoginScreen()
    {
        system("cls");
        ShowScreenHeader("Admin Login");

        cout << "\nAdmin Username: ";
        string user = clsInputValidate::ReadString();

        cout << "Admin Password: ";
        string pass = clsInputValidate::ReadString();

        while (!_CheckAdmin(user, pass))
        {
            cout << "\nInvalid admin credentials!\n";
            cout << "Admin Username: ";
            user = clsInputValidate::ReadString();
            cout << "Admin Password: ";
            pass = clsInputValidate::ReadString();
        }
        clsAdminMainMenuScreen::ShowAdminMainMenu();
    }
};
