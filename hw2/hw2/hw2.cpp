/******************************************************************************
* Name: Amundson, Brandon
* ID: 7258660
* Section: M002
* Homework 2
*****************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;


bool isPrime(long long int number);
void findPrime(long long int &number, long long int k[]);



int main()
{
    long long int number = 1;
    bool yes;
    long long int k[100] = { 0 };
    int l = 0;

    while (number > 0 && !cin.eof())
    {
        cout << "Enter a number: ";
        cin >> number;

        yes = isPrime(number);
        if (yes == true)
            cout << number << " is Prime." << endl;
        else
        {
            cout << number << " is Composite" << endl;
            findPrime(number, k);
        }
    }
    return (0);
}



bool isPrime(long long int number)
{
    int i = 0;
    bool yes = true;

    for (i = 2; i <= (number / 2); i++)
    {
        if ((number % i) == 0)
            yes = false;
    }
    return (yes);
}


void findPrime(long long int &number, long long int k[])
{
    long long int i = 2;
    long long int j = number / 2;
    long long int l = 0;




    while (number % 2 == 0)
    {
        k[l] = i;
        number = number / i;
        l++;
    }
    for (i = 3; i <= j; i += 2)
    {
        while (number % i == 0)
        {
            k[l] = i;
            number = number / i;
            l++;
        }
    }
    
    cout << k[0];
    for (l = 1; k[l] != 0; l++)
    {
        cout << " * " << k[l];
    }
    cout << endl;
    for (l = 0; k[l] != 0; l++)
        k[l] = 0;
}