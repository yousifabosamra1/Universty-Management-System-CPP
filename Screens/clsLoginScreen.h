#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsTopScreen.h"
#include "clsMainMenueScreen.h"
#include "clsStudent.h"
#include "clsInputValidate.h"
#include "Global.h"
using namespace std;

class clsLoginScreen :protected clsTopScreen
{
private:

    static bool _Login()
    {
        short count = 0;
        bool LoginFaild = false;
        int id;
        string  password;
        do
        {

            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n";
                cout << "try again " << count << "/3\n\n";
            }

            cout << "Enter Username? ";
            cin >> id;

            cout << "Enter Password? ";
            cin >> password;

            CurrentUser = clsStudent::Find(id, password);

            LoginFaild = CurrentUser.IsEmpty();
            count++;

            if (count >= 3)
            {
                cout << "\n\nSorry, you've used up all your attempts, Please try again later\n";
                exit(0);
                return false;
            }
        } while (LoginFaild);

        clsMainMenueScreen::ShowMainMenueScreen();
        return true;

    }

public:
    static void ShowLoginScreen()
    {
        system("cls");
        ShowScreenHeader("Login");
        _Login();
    }

};

