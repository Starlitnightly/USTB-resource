/*
ÄÃÓ²±Ò
*/

//#include "pch.h"
#include <iostream>
#include "string.h"

using namespace std;

int main()
{
	int n;
	cin >> n;
	if ((n - 2) % 3 == 0 || (n - 1) % 3 == 0)
	{
		cout << 'A';
	}
	else
		cout << 'B';
}

