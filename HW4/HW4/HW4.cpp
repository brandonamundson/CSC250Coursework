/******************************************************************************
* Name: Amundson, Brandon
* ID: 7258660
* Section: M001
* Homework 4
*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void commaSeparator(string &inName, string &firstName, string &middleName, string &lastName);
void nameSeparator(string &inName, string &firstName, string &middleName, string &lastName);

int main()
{
    string inName;
    string firstName;
    string middleName;
    string lastName;
    double comma;
    int i = 0;

    cout << "Input Name: ";

    while (getline(cin, inName))
    {
        comma = inName.find(',');

        if (comma != string::npos)
        {
            commaSeparator(inName, firstName, middleName, lastName);
        }

        else
        {
            nameSeparator(inName, firstName, middleName, lastName);
        }

        cout << right << "First name: " << firstName << endl;
        cout << "Middle name: " << middleName << endl;
        cout << "Last name: " << lastName << endl << left;

        cout << "Input Name: ";
    }
    return(0);
}


void commaSeparator(string &inName, string &firstName, string &middleName, string &lastName)
{
    int comma;
    int space1;
    int space2;
    int spacing;
    unsigned int end;
   
    comma = inName.find(',');
    space1 = inName.find(' ') + 1;
    space2 = inName.find(' ', space1+1) + 1;
    end = inName.size();
    spacing = space2 - space1;
    lastName = inName.substr(0, comma);
    firstName = inName.substr(space1, spacing);
    middleName = inName.substr(space2, end);
}


void nameSeparator(string &inName, string &firstName, string &middleName, string &lastName)
{
    int space1;
    int space2;
    int spacing;
    unsigned int end;

    space1 = inName.find(' ') + 1;
    space2 = inName.rfind(' ');
    spacing = space2 - space1;
    end = inName.size();
    firstName = inName.substr(0, space1);
    middleName = inName.substr(space1, spacing);
    space2++;
    lastName = inName.substr(space2, end);
}