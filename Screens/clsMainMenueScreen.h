#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsTopScreen.h"
#include <Windows.h>
#include "clsStudent.h"
#include "clsProfileScreen.h"
#include "clsEditProfileScreen.h"
#include "clsRegisterScreen.h"
#include "clsSubjectScreen.h"
#include "clsTimetableScreen.h"
#include "clsPasswordScreen.h"
#include "clsMainSystemScreen.h"
#include "clsGradesScreen.h"
using namespace std;

class clsMainMenueScreen :protected clsTopScreen
{
private:
    enum _enMenue{Profile=1,EditProfile=2,Register=3,Subject=4,TimeTable=5,Grade=6,Password=7,Logout=8};
    static short _ReadChoiseMenue()
    {
        short log;
        cout << "\n\t\t\t\tChoise [1] Or [8]";
        log = clsInputValidate::ReadshNumberBetween(1, 8);
        return log;
    }
    static  void _GoBackToMainMenueScreen(string message = "Press Any key to back to main meanue... ")
    {
        cout << message;
        system("pause>0");
        ShowMainMenueScreen();
    }
    static void _ProfileScreen()
    {
        clsProfileScreen::ShowProfileScreen();
    }
    static void _EditProfileScreen()
    {
        clsEditProfileScreen::ShowEditProfileScren();
    }
    static void _RegisterScreen()
    {
        clsRegisterScreen::ShowRegisterScreen();
    }
    static void _SubjectScreen()
    {
        clsSubjectScreen::ShowSubjectScreen();
    }
    static void _TimeTableScreen()
    {
        clsTimetableScreen::ShowTimeTableScreen();
    }
    static void _GradesScreen()
    {
        clsGradesScreen::ShowGradesScreen();
    }
    static void _PasswordScreen()
    {
        clsPasswordScreen::ShowPasswordScreen();
    }
    static void _ChoiseMenueOpthion(_enMenue Menue)
    {
        switch (Menue)
        {
            case _enMenue::Profile:
            {
                system("cls");
                _ProfileScreen();
                _GoBackToMainMenueScreen();
                break;
            }
            case _enMenue::EditProfile:
            {
                system("cls");
                _EditProfileScreen();
                _GoBackToMainMenueScreen();
                break;
            }
            case _enMenue::Register:
            {
                system("cls");
                _RegisterScreen();
                _GoBackToMainMenueScreen();
                break;
            }
            case _enMenue::Subject:
            {
                system("cls");
                _SubjectScreen();
                _GoBackToMainMenueScreen();
                break;
            }
            case _enMenue::TimeTable:
            {
                system("cls");
                _TimeTableScreen();
                _GoBackToMainMenueScreen();
                break;
            }
            case _enMenue::Grade:
            {
                system("cls");
                _GradesScreen();
                _GoBackToMainMenueScreen();
                break;
            }
            case _enMenue::Password:
            {
                system("cls");
                _PasswordScreen();
                _GoBackToMainMenueScreen();
                break;
            }
            case _enMenue::Logout:
            {
                system("cls");
                break;
            }
        }
    }
public:
	static void ShowMainMenueScreen()
	{
		system("cls");
        ShowScreenHeader("Main Menue");

        cout << "\t\t\t\t\t========================================\n";
        cout << "\t\t\t\t\t|              STUDENT MENU            |\n";
        cout << "\t\t\t\t\t========================================\n\n";

        cout << "\t\t\t\t\t|  ----------------   ---------------- |\n";
        cout << "\t\t\t\t\t|  |  1) PROFILE  |   |  2)  EDIT    | |\n";
        cout << "\t\t\t\t\t|  ----------------   ---------------- |\n\n";
                                                                            
        cout << "\t\t\t\t\t|                                      |\n";
        cout << "\t\t\t\t\t|  ----------------   ---------------- |\n";
        cout << "\t\t\t\t\t|  | 3) REGISTER  |   |  4) SUBJECTS | |\n";
        cout << "\t\t\t\t\t|  ----------------   ---------------- |\n\n";
                                                                             
        cout << "\t\t\t\t\t|                                      |\n";
        cout << "\t\t\t\t\t|  ----------------   ---------------- |\n";
        cout << "\t\t\t\t\t|  | 5) TIMETABLE |   |  6) GRADES   | |\n";
        cout << "\t\t\t\t\t|  ----------------   ---------------- |\n\n";

        cout << "\t\t\t\t\t|                                      |\n";
        cout << "\t\t\t\t\t|  ----------------   ---------------- |\n";
        cout << "\t\t\t\t\t|  | 7) PASSWORD  |   |  8) LOGOUT   | |\n";
        cout << "\t\t\t\t\t|  ----------------   ---------------- |\n";

        cout << "\n\t\t\t\t\t========================================\n";
        _ChoiseMenueOpthion((_enMenue)_ReadChoiseMenue());
    }
};

