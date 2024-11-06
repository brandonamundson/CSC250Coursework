/******************************************************************************
* Name: Amundson, Brandon
* ID: 7258660
* Section: M002
* Homework 3
*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;


void commaSeparator(char inName[], char firstName[], char middleName[], char lastName[]);
void nameSeparator(char inName[], char firstName[], char middleName[], char lastName[]);


int main()
{
    char inName[100];
    char firstName[100];
    char middleName[100];
    char lastName[100];
    char *comma;
    int i = 0;

    cout << "Input Name: ";

    while (!cin.eof() && cin.getline(inName, 95))
    {
        comma = strchr(inName, ',');

        if (comma != NULL)
        {
            commaSeparator(inName, firstName, middleName, lastName);
        }

        else
        {
            nameSeparator(inName, firstName, middleName, lastName);
        }

        cout << "First name: " << firstName << endl;
        cout << "Middle name: " << middleName << endl;
        cout << "Last name: " << lastName << endl;

        cout << "Input Name: ";
    }
    return(0);
}



void commaSeparator(char inName[], char firstName[], char middleName[], char lastName[])
{
    int i;
    int j;



    for (i = 0; inName[i] != ','; i++)
    {
        lastName[i] = inName[i];
    }
    
    lastName[i] = '\0';
    i+=2;
    j = i;
    
    for (; inName[i] != ' '; i++)
    {
        firstName[i-j] = inName[i];
    }

    firstName[i-j] = '\0';
    j = i;

    for (; inName[i] != '\0'; i++)
    {
        middleName[i-j] = inName[i];
    }

    middleName[i-j] = '\0';
}



void nameSeparator(char inName[], char firstName[], char middleName[], char lastName[])
{
    int i;

    for (i = 0; inName[i] != ' '; i++)
    {
        firstName[i] = inName[i];
    }

    i++;
    firstName[i] = '\0';

    for (; inName[i] != ' '; i++)
    {
        middleName[i] = inName[i];
    }

    i++;
    middleName[i] = '\0';

    for (; inName[i] != ' '; i++)
    {
        lastName[i] = inName[i];
    }

    i++;
    lastName[i] = '\0';
}
