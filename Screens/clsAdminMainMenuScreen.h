#pragma once
#include <iostream>

#include "clsTopScreen.h"
#include "clsInputValidate.h"

#include "clsAdminStudentsScreen.h"
#include "clsAdminRegistrationsScreen.h"
#include "clsAdminGradesScreen.h"
#include "clsAdminAttendanceScreen.h"
#include "clsAdminStatisticsScreen.h"
#include "clsAdminSettingsScreen.h"

using namespace std;

class clsAdminMainMenuScreen : protected clsTopScreen
{
private:

    enum enAdminMenu
    {
        ManageStudents = 1,
        ManageRegistrations = 2,
        ManageGrades = 3,
        AttendanceMonitor = 4,
        SystemStatistics = 5,
        AdminSettings = 6,
        Logout = 7
    };


    static short _ReadChoice()
    {
        cout << "\nChoose What do you want to do? [1 to 7]: ";

        short choice =
            clsInputValidate::ReadshNumberBetween(1, 7);

        return choice;
    }


    static void _GoBackToMenu()
    {
        cout << "\nPress any key to go back to Admin Menu...";
        system("pause>0");
    }


    static void _ShowManageStudents()
    {
        clsAdminStudentsScreen::Show();
    }


    static void _ShowManageRegistrations()
    {
        clsAdminRegistrationsScreen::Show();
    }


    static void _ShowManageGrades()
    {
        clsAdminGradesScreen::Show();
    }


    static void _ShowAttendanceMonitor()
    {
        clsAdminAttendanceScreen::Show();
    }


    static void _ShowStatistics()
    {
        clsAdminStatisticsScreen::Show();
    }


    static void _ShowAdminSettings()
    {
        clsAdminSettingsScreen::Show();
    }


public:

    static void ShowAdminMainMenu()
    {

        while (true)
        {
            system("cls");

            ShowScreenHeader("Admin Main Menu");

            cout << "\n=========================================\n";
            cout << "\t\tAdmin Menu";
            cout << "\n=========================================\n";

            cout << "\t[1] Manage Students\n";
            cout << "\t[2] Manage Registrations\n";
            cout << "\t[3] Manage Grades\n";
            cout << "\t[4] Attendance Monitor\n";
            cout << "\t[5] System Statistics\n";
            cout << "\t[6] Admin Settings\n";
            cout << "\t[7] Logout\n";

            cout << "\n=========================================\n";


            switch ((enAdminMenu)_ReadChoice())
            {

            case ManageStudents:
                _ShowManageStudents();
                break;


            case ManageRegistrations:
                _ShowManageRegistrations();
                break;


            case ManageGrades:
                _ShowManageGrades();
                break;


            case AttendanceMonitor:
                _ShowAttendanceMonitor();
                break;


            case SystemStatistics:
                _ShowStatistics();
                break;


            case AdminSettings:
                _ShowAdminSettings();
                break;


            case Logout:
                return;
            }
        }
    }
};