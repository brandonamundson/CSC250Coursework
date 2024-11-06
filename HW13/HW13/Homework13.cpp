/*****************************************************************************
* Name: Amundson, Brandon
* ID: 7258660
* Section: M001
* Homework 13 
*****************************************************************************/
#include <iostream>
#include <iomanip>

using namespace std;

template <class _TY> _TY minArray(_TY arr[], int count);
template <class _TY> _TY sumArray(_TY arr[], int count);


int main()
{
    int arr1[5] = { 5, 7, 1, 9, 3 };
    int min1=0;
    int sum1=0;

    double arr2[10] = { 8.9, 5.6, 3.4, 4.5, 6.7, 1.2, 7.8, 9.0, 10.1, 2.3 };
    double min2=0.0;
    double sum2=0.0;

    min1 = minArray( arr1, 5 );
    min2 = minArray( arr2, 10);

    cout << "The minumum value in arr1 is: " << min1 << endl;
    cout << "The minumum value in arr2 is: " << min2 << endl;

    sum1 = sumArray( arr1, 5);
    sum2 = sumArray( arr2, 10);

    cout << "The sum of arr1 is: " << sum1 << endl;
    cout << "The sum of arr2 is: " << sum2 << endl;
    return 0;
}


template <class _TY> _TY minArray(_TY arr[], int count)
{
    int i;
    _TY min = arr[0];

    for (i = 1; i < count; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}


template <class _TY> _TY sumArray(_TY arr[], int count)
{
    int i;
    _TY sum = 0;

    for (i = 0; i < count; i++)
    {
        sum += arr[i];
    }
    return sum;
}
