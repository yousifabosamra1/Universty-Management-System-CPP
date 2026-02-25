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

using namespace std;

class clsCourse
{


public:

        struct stCourseInfo
        {
            string CourseID;
            string CourseName;
            int CreditHours;
        };

        static string _Trim(string s)
        {
            while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' ' || s.back() == '\t'))
                s.pop_back();
            size_t i = 0;
            while (i < s.size() && (s[i] == ' ' || s[i] == '\t'))
                i++;
            return s.substr(i);
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

                string sId = _Trim(line.substr(0, p));
                string courseId = _Trim(line.substr(p + 1)); 

                if (sId.empty() || courseId.empty()) continue;

                int id = 0;
                try { id = stoi(sId); }
                catch (...) { continue; }

                if (id == CurrentUser.StudentId)
                    ids.push_back(courseId);
            }
            return ids;
        }
        struct stCourse
        {
            string CourseID;
            string CourseName;
            string Faculty;
            string Department;
            int Level;
            int CreditHours;
        };

    static vector<stCourse> _AllCourses()
    {

        return {

            {"CI101","Intro to Programming","Computer&Information","Common",1,3},
            {"CI102","Discrete Math","Computer&Information","Common",1,3},
            {"CI103","Computer Fundamentals","Computer&Information","Common",1,2},
            {"CI104","English 1","Computer&Information","Common",1,2},
            {"CI105","Critical Thinking","Computer&Information","Common",1,2},
            {"CI106","Intro to Cyber","Computer&Information","Common",1,2},
            {"CI107","Basics of Networks","Computer&Information","Common",1,2},

            {"CS201","OOP","Computer&Information","CS",2,3},
            {"CS202","Data Structures","Computer&Information","CS",2,3},
            {"CS203","Problem Solving","Computer&Information","CS",2,2},
            {"CS204","Computer Organization","Computer&Information","CS",2,3},
            {"CS205","C++ Projects","Computer&Information","CS",2,2},
            {"CS206","Git & Version Control","Computer&Information","CS",2,2},
            {"CS207","Intro to Algorithms","Computer&Information","CS",2,3},

            {"IS201","Database 1","Computer&Information","IS",2,3},
            {"IS202","SQL Lab","Computer&Information","IS",2,2},
            {"IS203","Data Modeling","Computer&Information","IS",2,2},
            {"IS204","Business Basics","Computer&Information","IS",2,2},
            {"IS205","Web Fundamentals","Computer&Information","IS",2,2},
            {"IS206","Excel for Data","Computer&Information","IS",2,2},
            {"IS207","Intro to Systems","Computer&Information","IS",2,3},

            {"IT201","Network Fundamentals","Computer&Information","IT",2,3},
            {"IT202","Routing Basics","Computer&Information","IT",2,3},
            {"IT203","Switching Basics","Computer&Information","IT",2,3},
            {"IT204","Windows Admin 1","Computer&Information","IT",2,2},
            {"IT205","Linux Basics","Computer&Information","IT",2,2},
            {"IT206","Virtualization","Computer&Information","IT",2,2},
            {"IT207","Troubleshooting","Computer&Information","IT",2,2},

            {"AI201","Math for AI","Computer&Information","AI",2,3},
            {"AI202","Python Basics","Computer&Information","AI",2,3},
            {"AI203","Data Analysis 1","Computer&Information","AI",2,2},
            {"AI204","Probability","Computer&Information","AI",2,3},
            {"AI205","Linear Algebra","Computer&Information","AI",2,3},
            {"AI206","Intro to ML","Computer&Information","AI",2,3},
            {"AI207","ML Lab 1","Computer&Information","AI",2,2},

            {"CY201","Security Basics","Computer&Information","Cyber Security",2,3},
            {"CY202","Linux for Security","Computer&Information","Cyber Security",2,2},
            {"CY203","Networking for Security","Computer&Information","Cyber Security",2,3},
            {"CY204","Web Basics","Computer&Information","Cyber Security",2,2},
            {"CY205","Ethical Hacking Intro","Computer&Information","Cyber Security",2,2},
            {"CY206","Cryptography Intro","Computer&Information","Cyber Security",2,2},
            {"CY207","Security Lab 1","Computer&Information","Cyber Security",2,2},

            {"CI211","Operating Systems","Computer&Information","Common",2,3},
            {"CI212","Communication Skills","Computer&Information","Common",2,2},

            {"CS301","Algorithms","Computer&Information","CS",3,3},
            {"CS302","Software Engineering","Computer&Information","CS",3,3},
            {"CS303","OOP Advanced","Computer&Information","CS",3,3},
            {"CS304","Database Concepts","Computer&Information","CS",3,2},
            {"CS305","Design Patterns","Computer&Information","CS",3,3},
            {"CS306","Testing & Debugging","Computer&Information","CS",3,2},
            {"CS307","C++ Advanced Lab","Computer&Information","CS",3,2},

            {"IS301","Database 2","Computer&Information","IS",3,3},
            {"IS302","Systems Analysis","Computer&Information","IS",3,3},
            {"IS303","BI Basics","Computer&Information","IS",3,2},
            {"IS304","ERP Basics","Computer&Information","IS",3,2},
            {"IS305","Data Visualization","Computer&Information","IS",3,2},
            {"IS306","SQL Advanced","Computer&Information","IS",3,2},
            {"IS307","IS Project 1","Computer&Information","IS",3,3},

            {"IT301","Routing Advanced","Computer&Information","IT",3,3},
            {"IT302","Switching Advanced","Computer&Information","IT",3,3},
            {"IT303","Windows Server","Computer&Information","IT",3,3},
            {"IT304","Linux Admin","Computer&Information","IT",3,3},
            {"IT305","Firewalls Basics","Computer&Information","IT",3,2},
            {"IT306","Cloud Basics","Computer&Information","IT",3,2},
            {"IT307","IT Project 1","Computer&Information","IT",3,3},

            {"AI301","Machine Learning 1","Computer&Information","AI",3,3},
            {"AI302","Data Mining","Computer&Information","AI",3,3},
            {"AI303","NLP Basics","Computer&Information","AI",3,2},
            {"AI304","ML Math","Computer&Information","AI",3,2},
            {"AI305","ML Lab 2","Computer&Information","AI",3,2},
            {"AI306","Feature Engineering","Computer&Information","AI",3,2},
            {"AI307","AI Project 1","Computer&Information","AI",3,3},

            {"CY301","Web Security","Computer&Information","Cyber Security",3,3},
            {"CY302","Network Security","Computer&Information","Cyber Security",3,3},
            {"CY303","Windows Attacks","Computer&Information","Cyber Security",3,2},
            {"CY304","Linux Attacks","Computer&Information","Cyber Security",3,2},
            {"CY305","Burp Suite Basics","Computer&Information","Cyber Security",3,2},
            {"CY306","OWASP Top 10","Computer&Information","Cyber Security",3,2},
            {"CY307","Security Lab 2","Computer&Information","Cyber Security",3,2},

            {"CI311","Project Management","Computer&Information","Common",3,2},

            {"CS401","Compiler Design","Computer&Information","CS",4,3},
            {"CS402","Advanced C++","Computer&Information","CS",4,3},
            {"CS403","Distributed Systems","Computer&Information","CS",4,3},
            {"CS404","Performance & Optimization","Computer&Information","CS",4,2},
            {"CS405","System Design","Computer&Information","CS",4,2},
            {"CS406","CS Project 2","Computer&Information","CS",4,3},
            {"CS499","Graduation Project","Computer&Information","Common",4,6},

            {"IS401","Data Warehouse","Computer&Information","IS",4,3},
            {"IS402","Big Data Basics","Computer&Information","IS",4,2},
            {"IS403","ETL & Pipelines","Computer&Information","IS",4,2},
            {"IS404","BI Project 2","Computer&Information","IS",4,3},
            {"IS405","Advanced SQL","Computer&Information","IS",4,2},
            {"IS406","IS Security","Computer&Information","IS",4,2},
            {"IS499","Graduation Project","Computer&Information","Common",4,6},

            {"IT401","Cloud Admin","Computer&Information","IT",4,3},
            {"IT402","DevOps Basics","Computer&Information","IT",4,2},
            {"IT403","Containerization","Computer&Information","IT",4,2},
            {"IT404","Network Design","Computer&Information","IT",4,3},
            {"IT405","Security Operations","Computer&Information","IT",4,2},
            {"IT406","IT Project 2","Computer&Information","IT",4,3},
            {"IT499","Graduation Project","Computer&Information","Common",4,6},

            {"AI401","Deep Learning","Computer&Information","AI",4,3},
            {"AI402","Computer Vision","Computer&Information","AI",4,3},
            {"AI403","NLP Advanced","Computer&Information","AI",4,2},
            {"AI404","MLOps Basics","Computer&Information","AI",4,2},
            {"AI405","AI Project 2","Computer&Information","AI",4,3},
            {"AI406","Ethics in AI","Computer&Information","AI",4,2},
            {"AI499","Graduation Project","Computer&Information","Common",4,6},

            {"CY401","Penetration Testing","Computer&Information","Cyber Security",4,3},
            {"CY402","Active Directory Attacks","Computer&Information","Cyber Security",4,2},
            {"CY403","Incident Response","Computer&Information","Cyber Security",4,2},
            {"CY404","Malware Basics","Computer&Information","Cyber Security",4,2},
            {"CY405","Red Team Lab","Computer&Information","Cyber Security",4,3},
            {"CY406","Blue Team Lab","Computer&Information","Cyber Security",4,3},
            {"CY499","Graduation Project","Computer&Information","Common",4,6},
        };
    }

    static bool _IsAllowed(const stCourse& c)
    {
        if (c.Faculty != CurrentUser.Faculty) return false;
        if (c.Level != CurrentUser.Level) return false;

        if (c.Department == "Common") return true;
        return (c.Department == CurrentUser.Department);
    }

    static vector<stCourse> _GetDepartmentTable()
    {
        vector<stCourse> all = _AllCourses();
        vector<stCourse> res;

        for (auto& c : all)
            if (_IsAllowed(c))
                res.push_back(c);

        return res;
    }

    static bool _AlreadyRegistered(int studentId, const string& courseId)
    {
        ifstream in("Enrollments.txt");
        if (!in) return false;

        string line;
        while (getline(in, line))
        {
            size_t p = line.find("~");
            if (p == string::npos) continue;

            string sId = _Trim(line.substr(0, p));
            string sCourse = _Trim(line.substr(p + 1)); 

            if (sId.empty() || sCourse.empty()) continue;

            int id = 0;
            try { id = stoi(sId); }
            catch (...) { continue; }

            if (id == studentId && sCourse == courseId)
                return true;
        }
        return false;
    }

    static void _SaveRegistration(int studentId, const string& courseId)
    {
        ofstream out("Enrollments.txt", ios::app);
        out << studentId << "~" << courseId << "\n";
    }
   
   

};

