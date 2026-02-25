#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "clsTopScreen.h"
#include "Global.h"
#include "clsGrades.h"

using namespace std;

class clsGradesScreen : protected clsTopScreen
{
private:
   

public:
    static void ShowGradesScreen()
    {
        ShowScreenHeader("Grades (Realistic)");

        vector<string> myIds = clsGrades::_LoadMyCourseIDs();

        system("cls");
        cout << "==================== Results ====================\n";
        cout << "Student: " << CurrentUser.StudentId << " | " << CurrentUser.FullName << "\n";
        cout << "-------------------------------------------------\n";

        if (myIds.empty())
        {
            cout << "You have no registered courses.\n";
            cout << "=================================================\n";
            system("pause");
            return;
        }

        cout << left
            << setw(8) << "ID"
            << setw(22) << "Course"
            << setw(6) << "CH"
            << setw(6) << "Quiz"
            << setw(6) << "Mid"
            << setw(10) << "Prac"
            << setw(7) << "Final"
            << setw(7) << "Total"
            << setw(7) << "Grade"
            << "\n";

        cout << "-------------------------------------------------\n";

        double totalWeightedPoints = 0.0;
        int totalCH = 0;

        for (auto& cid : myIds)
        {
            clsGrades::stCourse c = clsGrades::_GetCourseInfo(cid);
            clsGrades::stScore s = clsGrades::_LoadScoreForCourse(CurrentUser.StudentId, cid);

            if (!s.Found)
            {
                cout << left
                    << setw(8) << c.CourseID
                    << setw(22) << c.CourseName
                    << setw(6) << c.CH
                    << setw(6) << "-"
                    << setw(6) << "-"
                    << setw(10) << "-"
                    << setw(7) << "-"
                    << setw(7) << "-"
                    << setw(7) << "N/A"
                    << "\n";
                continue;
            }

            int total = clsGrades::_Total100(s);
            string g = clsGrades::_Letter(total);
            double pts = clsGrades::_Points(g);

            cout << left
                << setw(8) << c.CourseID
                << setw(22) << c.CourseName
                << setw(6) << c.CH
                << setw(6) << s.Quiz
                << setw(6) << s.Mid
                << setw(10) << s.Practical
                << setw(7) << s.Final
                << setw(7) << total
                << setw(7) << g
                << "\n";

            totalWeightedPoints += pts * c.CH;
            totalCH += c.CH;
        }

        cout << "-------------------------------------------------\n";

        double gpa = (totalCH > 0) ? (totalWeightedPoints / totalCH) : 0.0;
        cout << "GPA (Weighted): " << fixed << setprecision(2) << gpa << "\n";
        cout << "=================================================\n";
        system("pause");
    }
};