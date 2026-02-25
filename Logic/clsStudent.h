#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsString.h"
#include <Windows.h>
#include <cctype>
using namespace std;

class clsStudent
{
private:
	int _StudentID;
	string _FullName;
	string _Password;
	string _Email;
	string _Phone;

	string _Faculty;
	string _Department;
	short _Level;

	static bool _IsNumber(const string& s)
	{
		if (s.empty()) return false;
		for (char c : s)
			if (!isdigit((unsigned char)c)) return false;
		return true;
	}
	static string _ConvertObjectToLine(clsStudent Std, string S="~")
	{


		string Line;
		Line += to_string(Std._StudentID) + S;
		Line += Std.FullName + S;
		Line += Std.Password + S;
		Line += Std.Email + S;
		Line += Std.Phone + S;
		Line += Std.Faculty + S;
		Line += Std.Department + S;
		Line += to_string(Std.Level);
		return Line;
	}

	static clsStudent _ConvertLineToObject(string S,string Seprator="~")
	{
		vector<string>_vStd = clsString::Split(S, Seprator);

		if (_vStd.size() < 8) 
		{
			return clsStudent();
		}

		if (!_IsNumber(_vStd[0]) || !_IsNumber(_vStd[7]))
			return clsStudent();
		return clsStudent(stoi(_vStd[0]), _vStd[1], _vStd[2], _vStd[3], _vStd[4], _vStd[5], _vStd[6], stoi(_vStd[7]));

	}

	static vector<clsStudent>_LoadDataFromFile()
	{
		vector<clsStudent>_vStd;
		fstream myfile;
		myfile.open("Student.txt", ios::in);

		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsStudent S = _ConvertLineToObject(line);
				_vStd.push_back(S);
			}
			myfile.close();
		}
		return _vStd;

	}

	static void _AddNew(string Line)
	{
		fstream myfile;
		myfile.open("Student.txt", ios::out | ios::app);

		if (myfile.is_open())
		{
			myfile << Line << endl;

			myfile.close();
		}
	}
	static clsStudent _GetEmpty()
	{
		return clsStudent(0, "", "", "", "", "", "", 0);
	}

	static void _SaveStudentDateToFile(vector<clsStudent>vStd)
	{
		fstream myfile;
		myfile.open("Student.txt", ios::out);
		string dataline;
		if (myfile.is_open())
		{
			for (clsStudent S : vStd)
			{
				dataline = _ConvertObjectToLine(S);
				myfile << dataline << endl;
			}
			myfile.close();
		}
	}
public:

	

	clsStudent(int studentid, string fullname, string password, string email, string phone,
		string faculty, string department, short level)
	{
		_StudentID = studentid;
		_FullName = fullname;
		_Password = password;
		_Email = email;
		_Phone = phone;
		_Faculty = faculty;
		_Department = department;
		_Level = level;
	}
	clsStudent()
	{
		_StudentID = 0;
		_FullName = "";
		_Password = "";
		_Email = "";
		_Phone = "";
		_Faculty = "";
		_Department = "";
		_Level = 0;
	}

	bool IsEmpty() 
	{
		return _StudentID == 0;
	}

	void setStudentId(int id)
	{
		_StudentID = id;
	}
	int getStudentId()
	{
		return _StudentID;
	}
	__declspec(property(get = getStudentId, put = setStudentId))int StudentId;

	void setFullName(string fullname)
	{
		_FullName = fullname;
	}
	string getFullName()
	{
		return _FullName;
	}
	__declspec(property(get = getFullName, put = setFullName))string FullName;

	void setPassword(string password)
	{
		_Password = password;
	}
	string getPassword()
	{
		return _Password;
	}
	__declspec(property(get = getPassword, put = setPassword))string Password;

	void setEmail(string email)
	{
		_Email = email;
	}
	string getEmail()
	{
		return _Email;
	}
	__declspec(property(get = getEmail, put = setEmail))string Email;

	void setPhone(string phone)
	{
		_Phone = phone;
	}
	string getPhone()
	{
		return _Phone;
	}
	__declspec(property(get = getPhone, put = setPhone))string Phone;

	void setFaculty(string faculty)
	{
		_Faculty = faculty;
	}
	string getFaculty()
	{
		return _Faculty;
	}
	__declspec(property(get = getFaculty, put = setFaculty))string Faculty;

	void setDepartment(string department)
	{
		_Department = department;
	}
	string getDepartment()
	{
		return _Department;
	}
	__declspec(property(get = getDepartment, put = setDepartment))string Department;

	void setLevel(short level)
	{
		_Level = level;
	}
	short getLevel()
	{
		return _Level;
	}
	__declspec(property(get = getLevel, put = setLevel))short Level;

	 void AddNewStudent()
	{
		_AddNew(_ConvertObjectToLine(*this));
	}
	static void setColor(int color) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	static clsStudent Find(int id)
	{
		fstream Myfile;
		Myfile.open("Student.txt", ios::in);
		if (Myfile.is_open())
		{
			string Line;
			while (getline(Myfile, Line))
			{
				clsStudent Std = _ConvertLineToObject(Line);
				if (Std.StudentId == id)
				{
					Myfile.close();
					return Std;
				}

			}
			Myfile.close();
		}
		return _GetEmpty();
	}
	static clsStudent Find(int id, string password)
	{
		fstream Myfile;
		Myfile.open("Student.txt", ios::in);
		if (Myfile.is_open())
		{
			string Line;
			while (getline(Myfile, Line))
			{
				clsStudent Std = _ConvertLineToObject(Line);
				if (Std.StudentId == id && Std.Password == password)
				{
					Myfile.close();
					return Std;
				}

			}
			Myfile.close();
		}
		return _GetEmpty();
	}

	static bool IsStudentExit(int id)
	{
		clsStudent Std = clsStudent::Find(id);
		return !Std.IsEmpty();
	}

	static int GetNextStudentID()
	{
		vector<clsStudent> vStd = _LoadDataFromFile();

		int maxId = 200200;

		for (clsStudent& s : vStd)
		{
			if (s.getStudentId() > maxId)
				maxId = s.getStudentId();
		}

		return maxId + 1;
	}

	static vector<string> _GetDepartmentsByFaculty(const string& faculty)
	{
		if (faculty == "Commerce")
			return { "Accounting", "Business", "Economics", "MIS" };

		if (faculty == "Art")
			return { "Graphic Design", "Interior Design", "Fashion Design", "Animation & Multimedia", "Fine Arts" };

		if (faculty == "Pharmacy")
			return { "Pharmaceutics", "Pharmacology", "Clinical Pharmacy", "Medicinal Chemistry" };

		if (faculty == "Engineer")
			return { "Civil", "Architecture", "Electrical", "Mechanical", "Computer" };

		if (faculty == "Computer&Infomation" || faculty == "Computer&Information")
			return { "CS", "IT", "IS", "AI", "Cyber Security" };

		return { "General" };
	}

	void Update(int id)
	{
		vector<clsStudent> vStd = _LoadDataFromFile();

		for (clsStudent& s : vStd)
		{
			if (s.StudentId == id)
			{
				s = *this;
				break;
			}
		}
		_SaveStudentDateToFile(vStd);
	}
	void Update(string pass)
	{
		vector<clsStudent> vStd = _LoadDataFromFile();

		for (clsStudent& s : vStd)
		{
			if (s.Password == pass)
			{
				s = *this;
				break;
			}
		}
		_SaveStudentDateToFile(vStd);
	}

	static string CheckPassowrd()
	{
		string pass;

		while (true)
		{
			cout << "\nEnter Password: ";
			clsStudent::setColor(2);
			cout << "\nMin 8 characters, include letters and numbers\n";
			clsStudent::setColor(7);

			pass = clsInputValidate::ReadString();

			if (pass.length() < 8)
			{
				cout << "\n Password must be at least 8 characters.\n";
				continue;
			}

			bool hasLetter = false, hasDigit = false;
			for (char c : pass)
			{
				if (isalpha((unsigned char)c)) hasLetter = true;
				if (isdigit((unsigned char)c)) hasDigit = true;
			}

			if (!hasLetter || !hasDigit)
			{
				cout << "\n Password must contain letters and numbers.\n";
				continue;
			}

			return pass;
		}

		
	}
};