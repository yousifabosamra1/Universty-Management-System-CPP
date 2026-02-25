#pragma once
#include <iostream>
#include "clsTopScreen.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsStudent.h"
#include <conio.h>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

class clsSignUpScreen :protected clsTopScreen
{
private:

	enum enfuclty { Commerce = 1, Art = 2, Pharmacy = 3, Engneer = 4, ComputerInfomation = 5 };

	static string SelectFaculty()
	{
		vector<string> faculties =
		{
			"Commerce",
			"Art",
			"Pharmacy",
			"Engineer",
			"Computer&Information"
		};

		int index = 0;

		while (true)
		{
			system("cls");
			cout << "\n===============================================";
			cout << "\nSuccsess! Please Complete  your College Info:  ";
			cout << "\n===============================================\n";
			cout << "\nChoose Faculty:\n\n";

			for (int i = 0; i < faculties.size(); i++)
			{
				if (i == index)
				{
					clsStudent::setColor(10); 
					cout << "[ " << faculties[i] << " ]  ";
					clsStudent::setColor(7);
				}
				else
				{
					cout << faculties[i] << "  ";
				}
			}

			int key = _getch();

			if (key == 224) 
			{
				key = _getch();

				if (key == 75) 
					index = (index - 1 + faculties.size()) % faculties.size();

				else if (key == 77) 
					index = (index + 1) % faculties.size();
			}
			else if (key == 13) 
			{
				return faculties[index];
			}
		}
	}

	static string _SelectHorizontal(const string& title, const vector<string>& options)
	{
		if (options.empty()) return "";

		int idx = 0;

		while (true)
		{
			system("cls");
			cout << "\n===============================================";
			cout << "\nSuccsess! Please Complete  your College Info:  ";
			cout << "\n===============================================\n";
			cout << title << "\n\n";
		
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

			int key = _getch();

			if (key == 224) 
			{
				key = _getch();
				if (key == 75) idx = (idx - 1 + (int)options.size()) % (int)options.size(); 
				if (key == 77) idx = (idx + 1) % (int)options.size(); 
			}
			else if (key == 13) 
			{
				return options[idx];
			}
			else if (key == 27) 
			{
				return "";
			}
		}
	}
	
	static void _ReadInfo(clsStudent& S)
	{
		cout << "********* Please enter your information carefully.All fields are required.\n\n";

		cout << "\nEnter FullName: ";
		clsStudent::setColor(2);
		cout << "\nLetters only, min 3 characters\n";
		clsStudent::setColor(7);
		S.FullName = clsInputValidate::ReadString();

		//clsStudent::CheckPassowrd();




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

			bool hasLetter = false;
			bool hasDigit = false;

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

			break;
		}

		S.Password = pass;




		cout << "\nEnter Email: ";
		clsStudent::setColor(2);
		cout << "\nexample@student.edu\n";
		clsStudent::setColor(7);
		S.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		clsStudent::setColor(2);
		cout << "\n11 digits\n";
		clsStudent::setColor(7);
		S.Phone = clsInputValidate::ReadString();
		system("cls");
		

		cout << "\nFucelty Of :";
		vector<string> faculties = { "Commerce", "Art", "Pharmacy", "Engineer", "Computer&Information" };
		S.Faculty = _SelectHorizontal("Choose Faculty:", faculties);

		cout << "\nEnter Department: ";
		vector<string> depts = clsStudent::_GetDepartmentsByFaculty(S.Faculty);
		S.Department = _SelectHorizontal("Choose Department (" + S.Faculty + "):", depts);

		system("cls");
		cout << "\n===============================================";
		cout << "\nSuccsess! Please Complete  your College Info:  ";
		cout << "\n===============================================\n";
		cout << "\n\nEnter Level? [1:4] ";
		S.Level = clsInputValidate::ReadshNumberBetween(1, 4);
		cout << endl;

	}

public:
	
	static void ShowSignUpScreen()
	{
		ShowScreenHeader("Creat Account");
		clsStudent S;

		int newID = clsStudent::GetNextStudentID();
		S.setStudentId(newID);

		cout << "\n==================\n";
		cout << "|  ID = " << newID << "  |";
		cout << "\n==================\n\n";


		_ReadInfo(S);
		S.AddNewStudent();

		

	}

};

