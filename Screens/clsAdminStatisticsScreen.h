#pragma once
#include <iostream>
#include "clsTopScreen.h"
#include "clsAdmin.h"

using namespace std;

class clsAdminStatisticsScreen : protected clsTopScreen
{
public:
    static void Show()
    {
        ShowScreenHeader("System Statistics");

        auto s = clsAdmin::GetSystemStats();

        system("cls");
        cout << "================= System Stats =================\n";
        cout << "Students Count      : " << s.StudentsCount << "\n";
        cout << "Enrollments Count   : " << s.EnrollmentsCount << "\n";
        cout << "Scores Count        : " << s.ScoresCount << "\n";
        cout << "Admins Count        : " << s.AdminsCount << "\n";
        cout << "Most Registered CID : " << s.MostRegisteredCourseId
            << " (" << s.MostRegisteredCount << ")\n";
        cout << "=================================================\n";
        system("pause");
    }
};