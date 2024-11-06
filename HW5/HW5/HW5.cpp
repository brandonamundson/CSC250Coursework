/******************************************************************************
* Name: Amundson, Brandon
* ID: 7258660
* Section: M001
* Homework 5
*****************************************************************************/

#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
using namespace std;

void fileOpen(ifstream &fin, ofstream &fout);

int main()
{
    ifstream fin;
    ofstream fout;
    int count;
    double *ptr;


	fileOpen(fin, fout);

    fin.clear();

    fin.seekg(0, ios::end);

    count = (int)fin.tellg() / sizeof(double);
    ptr = new (nothrow) double[count];
    if (ptr == nullptr)
    {
        cout << "Memory Allocation Error" << endl;
        return(2);
    }


    fin.seekg(0, ios::beg);
    fin.clear();

    fin.read((char *) ptr, sizeof(double) * count);

    sort(ptr, ptr + count);
    
    fout.write((char *) ptr, sizeof(double) * count);

    fout.close();
    fin.close();

    delete [] ptr;
    return (0);
}

void fileOpen(ifstream &fin, ofstream &fout)
{
    fin.open("doubles.bin", ios::in | ios::binary);
    if (!fin)
    {
        cout << "Unable to open doubles.bin. Closing now" << endl;
		exit(1);
    }

    fout.open("results.bin", ios::out | ios::trunc | ios::binary);
    if (!fout)
    {
        cout << "Unable to open results.bin. Closing now" << endl;
		exit(1);
    }
}