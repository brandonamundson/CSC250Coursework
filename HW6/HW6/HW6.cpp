/******************************************************************************
* Name: Amundson, Brandon
* ID: 7258660
* Section: M001
* Homework 6
*****************************************************************************/


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


void fileOpen(ifstream &fin, ofstream &fout, ofstream &prime);
bool isPrime(int number);
bool myOrder(int left, int right);


int main()
{
	vector<int> firstVector;
	ifstream fin;
	ofstream fout, prime;
	unsigned long int intToVector;
	int i = 0;
	bool yesPrime;
	int numPrime = 0;


	fileOpen(fin, fout, prime);

	while (fin >> intToVector)
	{
		firstVector.push_back(intToVector);
	}

	sort(firstVector.begin(), firstVector.end(), myOrder);
	

	for (i = 0; i < signed(firstVector.size()); i++)
	{
		yesPrime = isPrime(firstVector[i]);
		if (yesPrime == true)
		{
			while (numPrime < 100)
			{
				prime << (firstVector[i]) << endl;
				numPrime++;
				break;
			}
		}


		fout << firstVector[i] << ' ';
		if ( (i + 1) % 5 == 0 && i != 0)
		{
			fout << endl;
		}
	}

	fin.close();
	fout.close();
	prime.close();

	return(0);
}


void fileOpen(ifstream &fin, ofstream &fout, ofstream &prime)
{
	fin.open("numbers.txt");
	if (!fin)
	{
		cout << "Unable to open numbers.txt. Closing now." << endl;
		exit(1);
	}

	fout.open("desc.txt");
	if (!fout)
	{
		cout << "Unable to open desc.txt. Closing now." << endl;
		exit(1);
	}
	
	prime.open("prime.txt");
	if (!prime)
	{
		cout << "Unable to open prime.txt. Closing now." << endl;
		exit(1);
	}
}


bool isPrime(int number)
{
	int i = 0;
	bool yes = true;

	if (number >= 0)
	{
		for (i = 2; i <= (number / 2); i++)
		{
			if ((number % i) == 0)
				yes = false;
		}
	}
	return (yes);
}


bool myOrder(int left, int right)
{
	return left > right;
}

/*corrected isPrime(int number)
  {
      int i;
      int max;

      if (num < 2)
          return false;
      if (num == 2)
          return true;
      if (num % 2) == 0)
          return false;
      max = sqrt(num) + 1;
      for(i = 3; i < max; i+=2)
          if(num % i == 0)
              return false;

      return false;
  }*/