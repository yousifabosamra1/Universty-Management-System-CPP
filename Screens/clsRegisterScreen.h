#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include "clsTopScreen.h"
#include "Global.h"
#include "clsStudent.h"
#include "clsCourse.h"

using namespace std;

class clsRegisterScreen : protected clsTopScreen
{
private:
  

    static int _ArrowMenu(const vector<string>& rows, const string& title)
    {
        if (rows.empty()) return -1;
        int idx = 0;

        while (true)
        {
            system("cls");
            cout << "====================================================\n";
            cout << title << "\n";
            cout << "Use UP/DOWN + Enter to Register (ESC to Back)\n";
            cout << "====================================================\n\n";

            for (int i = 0; i < (int)rows.size(); i++)
            {
                if (i == idx)
                {
                    clsStudent::setColor(10);
                    cout << "> " << rows[i] << "\n";
                    clsStudent::setColor(7);
                }
                else
                {
                    cout << "  " << rows[i] << "\n";
                }
            }

            int key = _getch();
            if (key == 224)
            {
                key = _getch();
                if (key == 72) idx = (idx - 1 + (int)rows.size()) % (int)rows.size();
                if (key == 80) idx = (idx + 1) % (int)rows.size();
            }
            else if (key == 13) return idx;
            else if (key == 27) return -1;
        }
    }

    static string _Row(const clsCourse::stCourse& c)
    {

        return c.CourseID + " | " + c.CourseName + " | CH: " + to_string(c.CreditHours);
    }

public:

    static void ShowRegisterScreen()
    {
        ShowScreenHeader("Course Register");


        vector<clsCourse::stCourse> table = clsCourse::_GetDepartmentTable();

        if (table.empty())
        {
            cout << "\nNo courses for your Faculty/Dept/Level.\n";
            system("pause");
            return;
        }

        vector<bool> selected(table.size(), false);
        vector<bool> already(table.size(), false);

        for (int i = 0; i < (int)table.size(); i++)
            already[i] = clsCourse::_AlreadyRegistered(CurrentUser.StudentId, table[i].CourseID);

        int idx = 0;

        while (true)
        {
            system("cls");
            cout << "====================================================\n";
            cout << "Register Courses (MULTI-SELECT)\n";
            cout << "Faculty: " << CurrentUser.Faculty
                << " | Dept: " << CurrentUser.Department
                << " | Level: " << CurrentUser.Level << "\n";
            cout << "----------------------------------------------------\n";
            cout << "UP/DOWN = move | SPACE = select | ENTER = save | ESC = back\n";
            cout << "----------------------------------------------------\n\n";

            for (int i = 0; i < (int)table.size(); i++)
            {
                string mark = selected[i] ? "[X] " : "[ ] ";
                string reg = already[i] ? " (REGISTERED)" : "";

                string line = mark + table[i].CourseID + " | " + table[i].CourseName
                    + " | CH: " + to_string(table[i].CreditHours) + reg;

                if (i == idx)
                {
                    clsStudent::setColor(10);
                    cout << "> " << line << "\n";
                    clsStudent::setColor(7);
                }
                else
                {
                    cout << "  " << line << "\n";
                }
            }

            int countSel = 0;
            for (bool x : selected) if (x) countSel++;
            cout << "\nSelected: " << countSel << " course(s)\n";

            int key = _getch();

            if (key == 224)
            {
                key = _getch();
                if (key == 72) idx = (idx - 1 + (int)table.size()) % (int)table.size(); 
                else if (key == 80) idx = (idx + 1) % (int)table.size(); 
            }
            else if (key == 32) 
            {

                if (already[idx])
                {

                    continue;
                }

               
                selected[idx] = !selected[idx];
            }
            else if (key == 13) 
            {
                bool any = false;
                for (bool x : selected) if (x) { any = true; break; }

                if (!any)
                {
                    cout << "\nNo courses selected.\n";
                    system("pause");
                    continue;
                }

             
                int saved = 0;
                for (int i = 0; i < (int)table.size(); i++)
                {
                    if (selected[i] && !already[i])
                    {
                        clsCourse::_SaveRegistration(CurrentUser.StudentId, table[i].CourseID);
                        already[i] = true;
                        selected[i] = false;
                        saved++;
                    }
                }

                cout << "\nSaved successfully! Added: " << saved << " course(s).\n";
                system("pause");
            }
            else if (key == 27) 
            {
                return;
            }
        }
    }
};