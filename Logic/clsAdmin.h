#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "clsStudent.h"

using namespace std;

class clsAdmin
{
public:

    static const string StudentsFile;
    static const string EnrollmentsFile;
    static const string ScoresFile;
    static const string AdminsFile;
    static const string Sep;

    struct stStudent
    {
        int Id = 0;
        string FullName, Password, Email, Phone, Faculty, Department;
        int Level = 1;
        string RawLine; 
    };

    struct stScore
    {
        int StudentId = 0;
        string CourseId;
        int Quiz = 0, Mid = 0, Practical = 0, Final = 0;
    };

    struct stStats
    {
        int StudentsCount = 0;
        int EnrollmentsCount = 0;
        int ScoresCount = 0;
        string MostRegisteredCourseId = "N/A";
        int MostRegisteredCount = 0;
        int AdminsCount = 0;
    };


    static vector<string> Split(const string& s)
    {
        vector<string> out;
        size_t start = 0;
        while (true)
        {
            size_t pos = s.find(Sep, start);
            if (pos == string::npos) { out.push_back(s.substr(start)); break; }
            out.push_back(s.substr(start, pos - start));
            start = pos + Sep.size();
        }
        return out;
    }

    static string Join(const vector<string>& v)
    {
        string r;
        for (int i = 0; i < (int)v.size(); i++)
        {
            r += v[i];
            if (i != (int)v.size() - 1) r += Sep;
        }
        return r;
    }

    static vector<string> ReadAllLines(const string& file)
    {
        vector<string> lines;
        ifstream in(file);
        string line;
        while (getline(in, line))
            if (!line.empty()) lines.push_back(line);
        return lines;
    }

    static void WriteAllLines(const string& file, const vector<string>& lines)
    {
        ofstream out(file, ios::trunc);
        for (auto& l : lines) out << l << "\n";
    }


    static bool TryParseStudentLine(const string& line, stStudent& s)
    {

        auto p = Split(line);
        if (p.size() < 8) return false;

        try { s.Id = stoi(p[0]); }
        catch (...) { return false; }

        s.FullName = p[1];
        s.Password = p[2];
        s.Email = p[3];
        s.Phone = p[4];
        s.Faculty = p[5];
        s.Department = p[6];
        try { s.Level = stoi(p[7]); }
        catch (...) { s.Level = 1; }

        s.RawLine = line;
        return true;
    }

    static vector<stStudent> GetAllStudents()
    {
        vector<stStudent> students;
        auto lines = ReadAllLines(StudentsFile);
        for (auto& l : lines)
        {
            stStudent s;
            if (TryParseStudentLine(l, s))
                students.push_back(s);
        }
        return students;
    }

    static bool FindStudentById(int id, stStudent& outStudent)
    {
        auto lines = ReadAllLines(StudentsFile);
        for (auto& l : lines)
        {
            stStudent s;
            if (TryParseStudentLine(l, s) && s.Id == id)
            {
                outStudent = s;
                return true;
            }
        }
        return false;
    }

    static bool ResetStudentPassword(int id, const string& newPass)
    {
        auto lines = ReadAllLines(StudentsFile);
        bool updated = false;

        for (auto& l : lines)
        {
            stStudent s;
            if (TryParseStudentLine(l, s) && s.Id == id)
            {
                auto p = Split(l);
                if (p.size() >= 8)
                {
                    p[2] = newPass;         
                    l = Join(p);
                    updated = true;
                }
                break;
            }
        }

        if (updated) WriteAllLines(StudentsFile, lines);
        return updated;
    }

    static bool DeleteStudent(int id)
    {
        auto students = ReadAllLines(StudentsFile);
        int before = (int)students.size();

        vector<string> kept;
        for (auto& l : students)
        {
            stStudent s;
            if (TryParseStudentLine(l, s) && s.Id == id) continue;
            kept.push_back(l);
        }

        if ((int)kept.size() == before) return false;

        auto enr = ReadAllLines(EnrollmentsFile);
        vector<string> enrKept;
        for (auto& l : enr)
        {
            auto p = Split(l);
            if (p.size() < 2) { enrKept.push_back(l); continue; }
            try
            {
                int sid = stoi(p[0]);
                if (sid != id) enrKept.push_back(l);
            }
            catch (...) { enrKept.push_back(l); }
        }

        auto sc = ReadAllLines(ScoresFile);
        vector<string> scKept;
        for (auto& l : sc)
        {
            auto p = Split(l);
            if (p.size() < 6) { scKept.push_back(l); continue; }
            try
            {
                int sid = stoi(p[0]);
                if (sid != id) scKept.push_back(l);
            }
            catch (...) { scKept.push_back(l); }
        }

        WriteAllLines(StudentsFile, kept);
        WriteAllLines(EnrollmentsFile, enrKept);
        WriteAllLines(ScoresFile, scKept);
        return true;
    }

    static vector<string> GetStudentEnrollments(int studentId)
    {
        vector<string> ids;
        auto lines = ReadAllLines(EnrollmentsFile);
        for (auto& l : lines)
        {
            auto p = Split(l);
            if (p.size() < 2) continue;
            try
            {
                int sid = stoi(p[0]);
                if (sid == studentId) ids.push_back(p[1]);
            }
            catch (...) {}
        }
        return ids;
    }

    static bool IsRegistered(int studentId, const string& courseId)
    {
        auto lines = ReadAllLines(EnrollmentsFile);
        for (auto& l : lines)
        {
            auto p = Split(l);
            if (p.size() < 2) continue;
            try
            {
                int sid = stoi(p[0]);
                if (sid == studentId && p[1] == courseId) return true;
            }
            catch (...) {}
        }
        return false;
    }

    static bool ForceRegisterCourse(int studentId, const string& courseId)
    {
        if (IsRegistered(studentId, courseId)) return false;
        ofstream out(EnrollmentsFile, ios::app);
        out << studentId << Sep << courseId << "\n";
        return true;
    }

    static bool UnregisterCourse(int studentId, const string& courseId)
    {
        auto lines = ReadAllLines(EnrollmentsFile);
        int before = (int)lines.size();

        vector<string> kept;
        for (auto& l : lines)
        {
            auto p = Split(l);
            if (p.size() < 2) { kept.push_back(l); continue; }

            bool remove = false;
            try
            {
                int sid = stoi(p[0]);
                if (sid == studentId && p[1] == courseId) remove = true;
            }
            catch (...) {}

            if (!remove) kept.push_back(l);
        }

        if ((int)kept.size() == before) return false;
        WriteAllLines(EnrollmentsFile, kept);
        return true;
    }

    static bool AddOrUpdateScore(const stScore& score)
    {
        string newline = to_string(score.StudentId) + Sep + score.CourseId + Sep
            + to_string(score.Quiz) + Sep + to_string(score.Mid) + Sep
            + to_string(score.Practical) + Sep + to_string(score.Final);

        auto lines = ReadAllLines(ScoresFile);
        bool updated = false;

        for (auto& l : lines)
        {
            auto p = Split(l);
            if (p.size() < 6) continue;

            int sid = 0;
            try { sid = stoi(p[0]); }
            catch (...) { continue; }

            if (sid == score.StudentId && p[1] == score.CourseId)
            {
                l = newline;
                updated = true;
                break;
            }
        }

        if (!updated) lines.push_back(newline);
        WriteAllLines(ScoresFile, lines);
        return true;
    }

    static bool DeleteScore(int studentId, const string& courseId)
    {
        auto lines = ReadAllLines(ScoresFile);
        int before = (int)lines.size();

        vector<string> kept;
        for (auto& l : lines)
        {
            auto p = Split(l);
            if (p.size() < 6) { kept.push_back(l); continue; }

            bool remove = false;
            try
            {
                int sid = stoi(p[0]);
                if (sid == studentId && p[1] == courseId) remove = true;
            }
            catch (...) {}

            if (!remove) kept.push_back(l);
        }

        if ((int)kept.size() == before) return false;
        WriteAllLines(ScoresFile, kept);
        return true;
    }

    static int GetAdminsCount()
    {
        return (int)ReadAllLines(AdminsFile).size();
    }

    static bool CheckAdminLogin(const string& user, const string& pass)
    {
        auto lines = ReadAllLines(AdminsFile);
        for (auto& l : lines)
        {
            auto p = Split(l);
            if (p.size() < 2) continue;
            if (p[0] == user && p[1] == pass) return true;
        }
       
        return (user == "admin" && pass == "1234");
    }

    static bool AddAdmin(const string& user, const string& pass)
    {
        auto lines = ReadAllLines(AdminsFile);
        for (auto& l : lines)
        {
            auto p = Split(l);
            if (p.size() >= 1 && p[0] == user) return false;
        }
        ofstream out(AdminsFile, ios::app);
        out << user << Sep << pass << "\n";
        return true;
    }

    static bool ChangeAdminPassword(const string& user, const string& newPass)
    {
        auto lines = ReadAllLines(AdminsFile);
        bool updated = false;

        for (auto& l : lines)
        {
            auto p = Split(l);
            if (p.size() < 2) continue;
            if (p[0] == user)
            {
                p[1] = newPass;
                l = Join(p);
                updated = true;
                break;
            }
        }

        if (updated) WriteAllLines(AdminsFile, lines);
        return updated;
    }

    static bool RemoveAdmin(const string& user)
    {
        auto lines = ReadAllLines(AdminsFile);
        int before = (int)lines.size();

        vector<string> kept;
        for (auto& l : lines)
        {
            auto p = Split(l);
            if (p.size() < 1) { kept.push_back(l); continue; }
            if (p[0] == user) continue;
            kept.push_back(l);
        }

        if ((int)kept.size() == before) return false;
        WriteAllLines(AdminsFile, kept);
        return true;
    }

    static stStats GetSystemStats()
    {
        stStats s;
        s.StudentsCount = (int)GetAllStudents().size();

        auto enroll = ReadAllLines(EnrollmentsFile);
        s.EnrollmentsCount = (int)enroll.size();

        auto scores = ReadAllLines(ScoresFile);
        s.ScoresCount = (int)scores.size();

        s.AdminsCount = GetAdminsCount();

      
        vector<pair<string, int>> counter;
        for (auto& l : enroll)
        {
            auto p = Split(l);
            if (p.size() < 2) continue;
            string cid = p[1];

            bool found = false;
            for (auto& it : counter)
            {
                if (it.first == cid) { it.second++; found = true; break; }
            }
            if (!found) counter.push_back({ cid, 1 });
        }

        for (auto& it : counter)
        {
            if (it.second > s.MostRegisteredCount)
            {
                s.MostRegisteredCount = it.second;
                s.MostRegisteredCourseId = it.first;
            }
        }

        return s;
    }
};