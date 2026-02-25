#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include "Global.h"
using namespace std;

class clsGrades
{
private:


public:
    struct stCourse
    {
        string CourseID;
        string CourseName;
        int CH;
    };

    struct stScore
    {
        bool Found = false;
        int Quiz = 0;       
        int Mid = 0;        
        int Practical = 0;  
        int Final = 0;     
    };


    static stCourse _GetCourseInfo(const string& id)
    {
       
        if (id == "CS201") return { id, "OOP", 3 };
        if (id == "CS202") return { id, "Data Structures", 3 };
        if (id == "CY201") return { id, "Security Basics", 3 };
        if (id == "CI211") return { id, "Operating Systems", 3 };

   
        return { id, "Unknown Course", 3 };
    }

    static vector<string> _LoadMyCourseIDs()
    {
        vector<string> ids;
        ifstream in("Enrollments.txt");
        if (!in) return ids;

        string line;
        while (getline(in, line))
        {
            size_t p = line.find("~");
            if (p == string::npos) continue;

            string sId = line.substr(0, p);
            string courseId = line.substr(p + 4);

            if (sId.empty() || courseId.empty()) continue;

            int id = 0;
            try { id = stoi(sId); }
            catch (...) { continue; }

            if (id == CurrentUser.StudentId)
                ids.push_back(courseId);
        }

        return ids;
    }

    static stScore _LoadScoreForCourse(int studentId, const string& courseId)
    {
        stScore s;
        ifstream in("Scores.txt");
        if (!in) return s;

        string line;
        while (getline(in, line))
        {
    
            vector<string> parts;
            size_t start = 0;
            while (true)
            {
                size_t pos = line.find("~", start);
                if (pos == string::npos) { parts.push_back(line.substr(start)); break; }
                parts.push_back(line.substr(start, pos - start));
                start = pos + 4;
            }

            if (parts.size() != 6) continue;

            int sid = 0;
            try { sid = stoi(parts[0]); }
            catch (...) { continue; }

            if (sid != studentId) continue;
            if (parts[1] != courseId) continue;

            try {
                s.Quiz = stoi(parts[2]);
                s.Mid = stoi(parts[3]);
                s.Practical = stoi(parts[4]);
                s.Final = stoi(parts[5]);
                s.Found = true;
                return s;
            }
            catch (...) { return stScore{}; }
        }

        return s;
    }

    static int _Total100(const stScore& s)
    {
        return s.Quiz + s.Mid + s.Practical + s.Final;
    }

    static string _Letter(int total)
    {
        if (total >= 90) return "A";
        if (total >= 85) return "A-";
        if (total >= 80) return "B+";
        if (total >= 75) return "B";
        if (total >= 70) return "B-";
        if (total >= 65) return "C+";
        if (total >= 60) return "C";
        if (total >= 55) return "D";
        return "F";
    }

    static double _Points(const string& g)
    {
        if (g == "A")  return 4.0;
        if (g == "A-") return 3.7;
        if (g == "B+") return 3.3;
        if (g == "B")  return 3.0;
        if (g == "B-") return 2.7;
        if (g == "C+") return 2.3;
        if (g == "C")  return 2.0;
        if (g == "D")  return 1.0;
        return 0.0;
    }

};

