#pragma once
#include <iostream>
#include "clsStudent.h"
#include "Global.h"
using namespace std;

class clsTopScreen
{
public:
	static void ShowScreenHeader(string message)
	{
		clsStudent::setColor(11);
		cout << "\t\t\t\t=========================================================";
		cout << "\n\t\t\t\t\t\t\t"  << message<<"\t\t"<<CurrentUser.Email;
		cout << "\n\t\t\t\t=========================================================\n";
		clsStudent::setColor(7);
	}
};

