//#include "pch.h"
#include<iostream>
#include"stdlib.h"
using namespace std;
int func(int *a, int b)
{
	int i, j, k=0,x;
	for (i = 0; i < b; i++)
	{


		for (j = 0; j < b-1-i; j++)
		{


			if (a[j] <= a[j + 1])
			{
				x = a[j]; a[j] = a[j + 1]; a[j + 1] = x;
			}

		}
	}
	for (j = 0; j < b; j++)
	{
		cout << a[j] << " ";
		if (a[j] == 0&&a[j-1]!=0)k=j;
	}
	cout << endl;
	return k;
}

int main()
{
	int *a; int i=0,o;
	int len = 5;
	a = (int*)malloc(sizeof(int*)*len);
		do
		{
			cin>>*(a + i);
			i++;
			if(i>=len)
				a = (int*)realloc(a, sizeof(int*)*(++len));
		} while (cin.get() != '\n');
	o=func(a, i);
	cout << o;
	free(a);
	return 0;
}

