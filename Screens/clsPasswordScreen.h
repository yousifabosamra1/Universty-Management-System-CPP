#pragma once
#include <iostream>
#include <string>
#include <cctype>   
#include "clsTopScreen.h"
#include "clsStudent.h"
#include "Global.h"
#include "clsInputValidate.h"
using namespace std;

class clsPasswordScreen : protected clsTopScreen
{
private:

    static bool _IsValidPassword(const string& pass)
    {
        if (pass.length() < 8) return false;

        bool hasLetter = false;
        bool hasDigit = false;

        for (char c : pass)
        {
            if (isalpha((unsigned char)c)) hasLetter = true;
            if (isdigit((unsigned char)c)) hasDigit = true;
        }
        return hasLetter && hasDigit;
    }

public:

    static void ShowPasswordScreen()
    {
        ShowScreenHeader("Change Password");

        string currentPass;
        cout << "\nPlease Enter Your Current Password: ";
        currentPass = clsInputValidate::ReadString();

        while (currentPass != CurrentUser.Password)
        {
            cout << "\nThe password is incorrect! Try again.\n";
            cout << "\nPlease Enter Your Current Password: ";
            currentPass = clsInputValidate::ReadString();
        }

        string newPass;
        cout << "\nEnter New Password: ";
        clsStudent::setColor(2);
        cout << "\nMin 8 characters, include letters and numbers\n";
        clsStudent::setColor(7);

        newPass = clsInputValidate::ReadString();

        while (!_IsValidPassword(newPass))
        {
            cout << "\nWeak password! Please follow the rules.\n";
            cout << "\nEnter New Password: ";
            newPass = clsInputValidate::ReadString();
        }

        if (newPass == CurrentUser.Password)
        {
            cout << "\nNew password cannot be the same as old password.\n";
            system("pause");
            return;
        }

        string confirmPass;
        cout << "\nConfirm New Password: ";
        confirmPass = clsInputValidate::ReadString();

        while (confirmPass != newPass)
        {
            cout << "\nPasswords do not match! Try again.\n";
            cout << "\nConfirm New Password: ";
            confirmPass = clsInputValidate::ReadString();
        }

      
        CurrentUser.Password = newPass;

       
        CurrentUser.Update(CurrentUser.StudentId);  
                          

        cout << "\n\nPassword changed successfully!\n";
      
    }
};