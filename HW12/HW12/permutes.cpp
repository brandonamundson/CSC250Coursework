#include <iostream>
using namespace std;

void permute(int *p, int *used, int n, int pos);

int main()
{
    int p[100] = { 0 };
    int used[100] = { 0 };
    int n;
    int pos = 0;
    cout << "Enter n" << endl << ">";
    cin >> n;
    permute(p, used, n, pos);

    return 0;
}

/*****************************************************************************
* Name: Brandon Amundson
* ID: 7258660
* Section: M001
* Homework 12
*****************************************************************************/
void permute(int *p, int *used, int n, int pos)
{
    int i;

    if (pos == n)
    {
        for (i = 0; i < n; i++)
        {
            if (p[i] == 1 && p[i - 1] == 2 || p[i - 1] == 1 && p[i] == 2)
                for (i = 0; i < n; i++)
                    cout << p[i] << " ";
            if (i == n)
                cout << endl;
        }
        return;
    }

    for (i = 0; i<n; i++)
    {
        if (used[i] == 0)
        {
            p[pos] = i;
            used[i] = 1;
            permute(p, used, n, pos + 1);
            used[i] = 0;
        }
    }
}