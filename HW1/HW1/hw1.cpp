#include <iostream>
#include <float.h>
using namespace std;

int main()
{
	int count = 0;
	double min = 0;
	double max = 0;
	double sum = 0;
	double avg = 0;
	double num = 0;

	while (count <= 10000 && !cin.eof())
	{
		cin >> num;
		count++;
		sum += num;
		avg = sum / count;
		if (num >= max)
		{
			max = num;
		}
		else if (num <= min)
		{
			min = num;
		}

		cout << "Count: " << count << endl;
		cout << "Min: " << min << endl;
		cout << "Max: " << max << endl;
		cout << "Sum: " << sum << endl;
		cout << "Average: " << avg << endl;
	}
	return (0);
}
