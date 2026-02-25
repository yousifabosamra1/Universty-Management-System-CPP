#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsTopScreen.h"
#include "clsMainMenueScreen.h"
#include "clsStudent.h"
#include "clsInputValidate.h"
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

class clsEditProfileScreen: protected clsTopScreen
{
private:

    static void _GoToXY(short x, short y)
    {
        COORD c{ x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    static short _GetCursorY()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.dwCursorPosition.Y;
    }

    static void _ClearLine(short y)
    {
        _GoToXY(0, y);
        cout << string(150, ' ');   
        _GoToXY(0, y);
    }

    static string _SelectHorizontal(const string& title,
        const vector<string>& options,
        const string& currentValue)
    {
        if (options.empty()) return currentValue;

        int idx = 0;
        for (int i = 0; i < (int)options.size(); i++)
            if (options[i] == currentValue) { idx = i; break; }

        cout << "\n" << title << "\n";
        cout << "Use Left/Right then Enter (Esc = cancel)\n";

        short lineY = _GetCursorY(); 

        auto draw = [&]()
            {
                _ClearLine(lineY);

                for (int i = 0; i < (int)options.size(); i++)
                {
                    if (i == idx)
                    {
                        clsStudent::setColor(10);
                        cout << "[ " << options[i] << " ]  ";
                        clsStudent::setColor(7);
                    }
                    else
                    {
                        cout << options[i] << "  ";
                    }
                }
            };

        draw();

        while (true)
        {
            int key = _getch();

            if (key == 0 || key == 224)
            {
                key = _getch();
                if (key == 75) { idx = (idx - 1 + (int)options.size()) % (int)options.size(); draw(); }
                else if (key == 77) { idx = (idx + 1) % (int)options.size(); draw(); } 
            }
            else if (key == 13) 
            {
                cout << "\n";
                return options.at(idx);
            }
            else if (key == 27) 
            {
                cout << "\n";
                return currentValue;
            }
        }
    }

    

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
    static void _ReadUpdateInfo()
    {
      
        cout << "\nEnter FullName: ";
        CurrentUser.FullName = clsInputValidate::ReadString();

        cout << "Enter Email: ";
        CurrentUser.Email = clsInputValidate::ReadString();

        cout << "Enter Phone: ";
        CurrentUser.Phone = clsInputValidate::ReadString();



     
        vector<string> depts = clsStudent::_GetDepartmentsByFaculty(CurrentUser.Faculty);
        CurrentUser.Department = _SelectHorizontal(
            "Choose Department (" + CurrentUser.Faculty + "):",
            depts,
            CurrentUser.Department
        );

    }
public:
	static void ShowEditProfileScren()
	{
		ShowScreenHeader("Edit Profile");

        int Id=0;
        cout << "\nPlease Enter ID? ";
        Id = clsInputValidate::ReadIntNumber();

        while (!(Id == CurrentUser.StudentId))
        {
            cout << "\nThis ID is Not Correct! Enter The Another ID: ";
            Id = clsInputValidate::ReadIntNumber();
        }

        _PrintInfo();
        cout << "\n\n----------------------------------\n";
        cout << "Update Info ";
        cout << "\n----------------------------------\n";
        _ReadUpdateInfo();
        clsStudent S;

       
            CurrentUser.Update(Id);
        

        _PrintInfo();
	}
};

