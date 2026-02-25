#pragma once
#include <iostream>
#include "clsTopScreen.h"
#include "clsInputValidate.h"
#include "clsLoginScreen.h"
#include "clsSignUpScreen.h"
using namespace std;

class clsMainSystemScreen : protected clsTopScreen
{
private:

	enum _enSystem{Login=1,SignUp=2};

	static short _ReadChoiseSystem()
	{
		short log;
		cout << "\n\t\t\t\tChoise [1] Or [2]";
		log = clsInputValidate::ReadshNumberBetween(1, 2);
		return log;
	}

	static void _LoginScreen()
	{
		clsLoginScreen::ShowLoginScreen();
	}

	static void _SignUpScreen()
	{
		clsSignUpScreen::ShowSignUpScreen();
	}

	static  void _GoBackToLoginScreen(string message = "Press Any key to back to main meanue... ")
	{
		cout << message;
		system("pause>0");
		_LoginScreen();
	}

	static void _ChoiseSystem(_enSystem System)
	{
		switch (System)
		{
		case _enSystem::Login:
		{
			system("cls");
			_LoginScreen();
			break;
		}
		case _enSystem::SignUp:
		{
			system("cls");
			_SignUpScreen();
			_GoBackToLoginScreen();
			break;
		}
		}
	}
	

public:

	static void ShowChoiseLoginScreen()
	{
		system("cls");
		ShowScreenHeader("Main System");
		cout << "\n\n\n";

		cout << "\t\t\t\t   ***************\t\t\t***************\n";
		cout << "\t\t\t\t   *    Login    *\t\t\t*   Sign Up   *\n";
		cout << "\t\t\t\t   ******[1]******\t\t\t******[2]******\n";
		cout << "\n\n\t\t\t\t=========================================================";
		_ChoiseSystem((_enSystem)_ReadChoiseSystem());
	}
};

