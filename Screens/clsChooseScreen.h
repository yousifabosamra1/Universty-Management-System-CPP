#pragma once
#include <iostream>
#include <conio.h>

#include "clsTopScreen.h"
#include "clsMainSystemScreen.h"
#include "clsAdminLoginScreen.h"       

using namespace std;

class clsChooseScreen : protected clsTopScreen
{
private:
    enum enRole { Student = 1, Admin = 2 };

    static enRole _ReadRoleByArrows()
    {
        int idx = 0; 

        while (true)
        {
            system("cls");
            cout << "=============================\n";
            cout << " University System\n";
            cout << "=============================\n\n";
            cout << "Choose Role (UP/DOWN + Enter)\n\n";

            if (idx == 0)
            {
                cout << "> Student\n";
                cout << "  Admin\n";
            }
            else
            {
                cout << "  Student\n";
                cout << "> Admin\n";
            }

            int key = _getch();

            if (key == 224)
            {
                key = _getch();
                if (key == 72) idx = (idx - 1 + 2) % 2; 
                else if (key == 80) idx = (idx + 1) % 2; 
            }
            else if (key == 13) 
            {
                return (idx == 0) ? Student : Admin;
            }
        }
    }

public:

    static void ShowChooseScreen()
    {
        enRole role = _ReadRoleByArrows();

        if (role == Student)
        {
            clsMainSystemScreen::ShowChoiseLoginScreen();
        }
        else
        {
            clsAdminLoginScreen::ShowAdminLoginScreen();
        }
    }
};